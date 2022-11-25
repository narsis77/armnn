//
// Copyright © 2022 Arm Ltd and Contributors. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include "TosaOperatorUtils.hpp"

#include <Layer.hpp>

#include <tosa_serialization_handler.h>

using namespace armnn;
using namespace tosa;

TosaSerializationBasicBlock* ConvertConstantToTosaOperator(const Layer* layer,
                                                           const std::vector<const TensorInfo*>& outputs);

