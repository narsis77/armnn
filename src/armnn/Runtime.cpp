﻿//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//
#include "Runtime.hpp"

#include <armnn/Version.hpp>
#include <armnn/BackendRegistry.hpp>
#include <armnn/Logging.hpp>

#include <armnn/backends/IBackendContext.hpp>
#include <backendsCommon/DynamicBackendUtils.hpp>

#include <ProfilingService.hpp>

#include <iostream>

#include <boost/polymorphic_cast.hpp>
#include <backends/BackendProfiling.hpp>

using namespace armnn;
using namespace std;

namespace armnn
{

IRuntime* IRuntime::CreateRaw(const CreationOptions& options)
{
    return new Runtime(options);
}

IRuntimePtr IRuntime::Create(const CreationOptions& options)
{
    return IRuntimePtr(CreateRaw(options), &IRuntime::Destroy);
}

void IRuntime::Destroy(IRuntime* runtime)
{
    delete boost::polymorphic_downcast<Runtime*>(runtime);
}

int Runtime::GenerateNetworkId()
{
    return m_NetworkIdCounter++;
}

Status Runtime::LoadNetwork(NetworkId& networkIdOut, IOptimizedNetworkPtr inNetwork)
{
    std::string ignoredErrorMessage;
    return LoadNetwork(networkIdOut, std::move(inNetwork), ignoredErrorMessage);
}

Status Runtime::LoadNetwork(NetworkId& networkIdOut,
                            IOptimizedNetworkPtr inNetwork,
                            std::string& errorMessage)
{
    INetworkProperties networkProperties;
    return LoadNetwork(networkIdOut, std::move(inNetwork), errorMessage, networkProperties);
}

Status Runtime::LoadNetwork(NetworkId& networkIdOut,
                            IOptimizedNetworkPtr inNetwork,
                            std::string& errorMessage,
                            const INetworkProperties& networkProperties)
{
    IOptimizedNetwork* rawNetwork = inNetwork.release();

    networkIdOut = GenerateNetworkId();

    for (auto&& context : m_BackendContexts)
    {
        context.second->BeforeLoadNetwork(networkIdOut);
    }

    unique_ptr<LoadedNetwork> loadedNetwork = LoadedNetwork::MakeLoadedNetwork(
        std::unique_ptr<OptimizedNetwork>(boost::polymorphic_downcast<OptimizedNetwork*>(rawNetwork)),
        errorMessage,
        networkProperties);

    if (!loadedNetwork)
    {
        return Status::Failure;
    }

    {
        std::lock_guard<std::mutex> lockGuard(m_Mutex);

        // Stores the network
        m_LoadedNetworks[networkIdOut] = std::move(loadedNetwork);
    }

    for (auto&& context : m_BackendContexts)
    {
        context.second->AfterLoadNetwork(networkIdOut);
    }

    if (profiling::ProfilingService::Instance().IsProfilingEnabled())
    {
        profiling::ProfilingService::Instance().IncrementCounterValue(armnn::profiling::NETWORK_LOADS);
    }

    return Status::Success;
}

Status Runtime::UnloadNetwork(NetworkId networkId)
{
    bool unloadOk = true;
    for (auto&& context : m_BackendContexts)
    {
        unloadOk &= context.second->BeforeUnloadNetwork(networkId);
    }

    if (!unloadOk)
    {
        ARMNN_LOG(warning) << "Runtime::UnloadNetwork(): failed to unload "
                              "network with ID:" << networkId << " because BeforeUnloadNetwork failed";
        return Status::Failure;
    }

    {
        std::lock_guard<std::mutex> lockGuard(m_Mutex);

        if (m_LoadedNetworks.erase(networkId) == 0)
        {
            ARMNN_LOG(warning) << "WARNING: Runtime::UnloadNetwork(): " << networkId << " not found!";
            return Status::Failure;
        }
        if (profiling::ProfilingService::Instance().IsProfilingEnabled())
        {
            profiling::ProfilingService::Instance().IncrementCounterValue(armnn::profiling::NETWORK_UNLOADS);
        }
    }

    for (auto&& context : m_BackendContexts)
    {
        context.second->AfterUnloadNetwork(networkId);
    }

    ARMNN_LOG(debug) << "Runtime::UnloadNetwork(): Unloaded network with ID: " << networkId;
    return Status::Success;
}

const std::shared_ptr<IProfiler> Runtime::GetProfiler(NetworkId networkId) const
{
    auto it = m_LoadedNetworks.find(networkId);
    if (it != m_LoadedNetworks.end())
    {
        auto& loadedNetwork = it->second;
        return loadedNetwork->GetProfiler();
    }

    return nullptr;
}

Runtime::Runtime(const CreationOptions& options)
    : m_NetworkIdCounter(0)
{
    ARMNN_LOG(info) << "ArmNN v" << ARMNN_VERSION << "\n";

    // pass configuration info to the profiling service
    armnn::profiling::ProfilingService::Instance().ConfigureProfilingService(options.m_ProfilingOptions);

    // Load any available/compatible dynamic backend before the runtime
    // goes through the backend registry
    LoadDynamicBackends(options.m_DynamicBackendsPath);

    BackendIdSet supportedBackends;
    for (const auto& id : BackendRegistryInstance().GetBackendIds())
    {
        // Store backend contexts for the supported ones
        try {
            auto factoryFun = BackendRegistryInstance().GetFactory(id);
            auto backend = factoryFun();
            BOOST_ASSERT(backend.get() != nullptr);

            auto context = backend->CreateBackendContext(options);

            // backends are allowed to return nullptrs if they
            // don't wish to create a backend specific context
            if (context)
            {
                m_BackendContexts.emplace(std::make_pair(id, std::move(context)));
            }
            supportedBackends.emplace(id);

            unique_ptr<armnn::profiling::IBackendProfiling> profilingIface =
                std::make_unique<armnn::profiling::BackendProfiling>(armnn::profiling::BackendProfiling(
                    options, armnn::profiling::ProfilingService::Instance(), id));

            // Backends may also provide a profiling context. Ask for it now.
            auto profilingContext = backend->CreateBackendProfilingContext(options, profilingIface);
            // Backends that don't support profiling will return a null profiling context.
            if (profilingContext)
            {
                // Enable profiling on the backend and assert that it returns true
                if(profilingContext->EnableProfiling(true))
                {
                    // Pass the context onto the profiling service.
                    armnn::profiling::ProfilingService::Instance().AddBackendProfilingContext(id, profilingContext);
                }
                else
                {
                    throw BackendProfilingException("Unable to enable profiling on Backend Id: " + id.Get());
                }
            }
        }
        catch (const BackendUnavailableException&)
        {
            // Ignore backends which are unavailable
        }

    }
    m_DeviceSpec.AddSupportedBackends(supportedBackends);
}

Runtime::~Runtime()
{
    std::vector<int> networkIDs;
    try
    {
        // Coverity fix: The following code may throw an exception of type std::length_error.
        std::transform(m_LoadedNetworks.begin(), m_LoadedNetworks.end(),
                       std::back_inserter(networkIDs),
                       [](const auto &pair) { return pair.first; });
    }
    catch (const std::exception& e)
    {
        // Coverity fix: BOOST_LOG_TRIVIAL (typically used to report errors) may throw an
        // exception of type std::length_error.
        // Using stderr instead in this context as there is no point in nesting try-catch blocks here.
        std::cerr << "WARNING: An error has occurred when getting the IDs of the networks to unload: " << e.what()
                  << "\nSome of the loaded networks may not be unloaded" << std::endl;
    }
    // We then proceed to unload all the networks which IDs have been appended to the list
    // up to the point the exception was thrown (if any).

    for (auto networkID : networkIDs)
    {
        try
        {
            // Coverity fix: UnloadNetwork() may throw an exception of type std::length_error,
            // boost::log::v2s_mt_posix::odr_violation or boost::log::v2s_mt_posix::system_error
            UnloadNetwork(networkID);
        }
        catch (const std::exception& e)
        {
            // Coverity fix: BOOST_LOG_TRIVIAL (typically used to report errors) may throw an
            // exception of type std::length_error.
            // Using stderr instead in this context as there is no point in nesting try-catch blocks here.
            std::cerr << "WARNING: An error has occurred when unloading network " << networkID << ": " << e.what()
                      << std::endl;
        }
    }


    // Clear all dynamic backends.
    DynamicBackendUtils::DeregisterDynamicBackends(m_DeviceSpec.GetDynamicBackends());
    m_DeviceSpec.ClearDynamicBackends();
    m_BackendContexts.clear();
}

LoadedNetwork* Runtime::GetLoadedNetworkPtr(NetworkId networkId) const
{
    std::lock_guard<std::mutex> lockGuard(m_Mutex);
    return m_LoadedNetworks.at(networkId).get();
}

TensorInfo Runtime::GetInputTensorInfo(NetworkId networkId, LayerBindingId layerId) const
{
    return GetLoadedNetworkPtr(networkId)->GetInputTensorInfo(layerId);
}

TensorInfo Runtime::GetOutputTensorInfo(NetworkId networkId, LayerBindingId layerId) const
{
    return GetLoadedNetworkPtr(networkId)->GetOutputTensorInfo(layerId);
}


Status Runtime::EnqueueWorkload(NetworkId networkId,
                                const InputTensors& inputTensors,
                                const OutputTensors& outputTensors)
{
    LoadedNetwork* loadedNetwork = GetLoadedNetworkPtr(networkId);

    static thread_local NetworkId lastId = networkId;
    if (lastId != networkId)
    {
        LoadedNetworkFuncSafe(lastId, [](LoadedNetwork* network)
            {
                network->FreeWorkingMemory();
            });
    }
    lastId=networkId;

    return loadedNetwork->EnqueueWorkload(inputTensors, outputTensors);
}

void Runtime::RegisterDebugCallback(NetworkId networkId, const DebugCallbackFunction& func)
{
    LoadedNetwork* loadedNetwork = GetLoadedNetworkPtr(networkId);
    loadedNetwork->RegisterDebugCallback(func);
}

void Runtime::LoadDynamicBackends(const std::string& overrideBackendPath)
{
    // Get the paths where to load the dynamic backends from
    std::vector<std::string> backendPaths = DynamicBackendUtils::GetBackendPaths(overrideBackendPath);

    // Get the shared objects to try to load as dynamic backends
    std::vector<std::string> sharedObjects = DynamicBackendUtils::GetSharedObjects(backendPaths);

    // Create a list of dynamic backends
    m_DynamicBackends = DynamicBackendUtils::CreateDynamicBackends(sharedObjects);

    // Register the dynamic backends in the backend registry
    BackendIdSet registeredBackendIds = DynamicBackendUtils::RegisterDynamicBackends(m_DynamicBackends);

    // Add the registered dynamic backend ids to the list of supported backends
    m_DeviceSpec.AddSupportedBackends(registeredBackendIds, true);
}

} // namespace armnn
