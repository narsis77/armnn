//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include <armnn/backends/Workload.hpp>
#include <armnn/backends/WorkloadData.hpp>

namespace armnn
{

class RefDetectionPostProcessWorkload : public BaseWorkload<DetectionPostProcessQueueDescriptor>
{
public:
    explicit RefDetectionPostProcessWorkload(const DetectionPostProcessQueueDescriptor& descriptor,
                                             const WorkloadInfo& info);
    void Execute() const override;
    void ExecuteAsync(WorkingMemDescriptor& workingMemDescriptor)  override;

private:
    void Execute(std::vector<ITensorHandle*> inputs, std::vector<ITensorHandle*> outputs) const;
    std::unique_ptr<ScopedTensorHandle> m_Anchors;
};

} //namespace armnn
