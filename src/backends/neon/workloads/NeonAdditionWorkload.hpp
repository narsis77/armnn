//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include <armnn/backends/Workload.hpp>

#include <arm_compute/core/Error.h>
#include <arm_compute/core/Types.h>
#include <arm_compute/runtime/IFunction.h>

namespace armnn
{

arm_compute::Status NeonAdditionWorkloadValidate(const TensorInfo& input0,
                                                 const TensorInfo& input1,
                                                 const TensorInfo& output,
                                                 const ActivationDescriptor* activationDescriptor = nullptr);

class NeonAdditionWorkload : public BaseWorkload<AdditionQueueDescriptor>
{
public:
    NeonAdditionWorkload(const AdditionQueueDescriptor& descriptor, const WorkloadInfo& info);
    virtual void Execute() const override;

private:
    std::unique_ptr<arm_compute::IFunction> m_AddLayer;
};

} //namespace armnn



