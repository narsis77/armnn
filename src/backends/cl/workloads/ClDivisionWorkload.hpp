//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include <armnn/backends/Workload.hpp>

#include <arm_compute/runtime/CL/functions/CLElementwiseOperations.h>

namespace armnn
{

arm_compute::Status ClDivisionWorkloadValidate(const TensorInfo& input0,
                                               const TensorInfo& input1,
                                               const TensorInfo& output,
                                               const ActivationDescriptor* activationDescriptor = nullptr);

class ClDivisionWorkload : public BaseWorkload<DivisionQueueDescriptor>
{
public:
    ClDivisionWorkload(const DivisionQueueDescriptor& descriptor,
                       const WorkloadInfo& info,
                       const arm_compute::CLCompileContext& clCompileContext);

    using BaseWorkload<DivisionQueueDescriptor>::BaseWorkload;
    void Execute() const override;

private:
    mutable arm_compute::CLArithmeticDivision m_ArithmeticDivision;
};

} //namespace armnn
