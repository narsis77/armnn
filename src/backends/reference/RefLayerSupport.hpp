//
// Copyright © 2017-2023 Arm Ltd and Contributors. All rights reserved.
// SPDX-License-Identifier: MIT
//
#pragma once

#include <backendsCommon/LayerSupportBase.hpp>

namespace armnn
{

class RefLayerSupport : public LayerSupportBase
{
public:
    bool IsLayerSupported(const LayerType& type,
                          const std::vector<TensorInfo>& infos,
                          const BaseDescriptor& descriptor,
                          const Optional<LstmInputParamsInfo>& lstmParamsInfo,
                          const Optional<QuantizedLstmInputParamsInfo>&,
                          Optional<std::string&> reasonIfUnsupported) const override;

    bool IsActivationSupported(const TensorInfo& input,
                               const TensorInfo& output,
                               const ActivationDescriptor& descriptor,
                               Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsAdditionSupported(const TensorInfo& input0,
                             const TensorInfo& input1,
                             const TensorInfo& output,
                             Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsArgMinMaxSupported(const TensorInfo& input,
                              const TensorInfo& output,
                              const ArgMinMaxDescriptor& descriptor,
                              Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsBatchMatMulSupported(const TensorInfo& inputX,
                                const TensorInfo& inputY,
                                const TensorInfo& output,
                                const BatchMatMulDescriptor& descriptor,
                                Optional<std::string &> reasonIfUnsupported = EmptyOptional()) const;

    bool IsBatchNormalizationSupported(const TensorInfo& input,
                                       const TensorInfo& output,
                                       const TensorInfo& mean,
                                       const TensorInfo& var,
                                       const TensorInfo& beta,
                                       const TensorInfo& gamma,
                                       const BatchNormalizationDescriptor& descriptor,
                                       Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsBatchToSpaceNdSupported(const TensorInfo& input,
                                   const TensorInfo& output,
                                   const BatchToSpaceNdDescriptor& descriptor,
                                   Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsBroadcastToSupported(const TensorInfo& input,
                                const TensorInfo& output,
                                const BroadcastToDescriptor& descriptor,
                                Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsCastSupported(const TensorInfo& input,
                         const TensorInfo& output,
                         Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsChannelShuffleSupported(const TensorInfo& input,
                                   const TensorInfo& output,
                                   const ChannelShuffleDescriptor& descriptor,
                                   Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsComparisonSupported(const TensorInfo& input0,
                               const TensorInfo& input1,
                               const TensorInfo& output,
                               const ComparisonDescriptor& descriptor,
                               Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsConcatSupported(const std::vector<const TensorInfo*> inputs,
                           const TensorInfo& output,
                           const OriginsDescriptor& descriptor,
                           Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsConstantSupported(const TensorInfo& output,
                             Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsConvertFp16ToFp32Supported(const TensorInfo& input,
                                      const TensorInfo& output,
                                      Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;


    bool IsConvertFp32ToFp16Supported(const TensorInfo& input,
                                      const TensorInfo& output,
                                      Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsConvolution2dSupported(const TensorInfo& input,
                                  const TensorInfo& output,
                                  const Convolution2dDescriptor& descriptor,
                                  const TensorInfo& weights,
                                  const Optional<TensorInfo>& biases,
                                  Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsConvolution3dSupported(const TensorInfo& input,
                                  const TensorInfo& output,
                                  const Convolution3dDescriptor& descriptor,
                                  const TensorInfo& weights,
                                  const Optional<TensorInfo>& biases,
                                  Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsDebugSupported(const TensorInfo& input,
                          const TensorInfo& output,
                          Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsDepthToSpaceSupported(const TensorInfo& input,
                                 const TensorInfo& output,
                                 const DepthToSpaceDescriptor& descriptor,
                                 Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsDepthwiseConvolutionSupported(const TensorInfo& input,
                                         const TensorInfo& output,
                                         const DepthwiseConvolution2dDescriptor& descriptor,
                                         const TensorInfo& weights,
                                         const Optional<TensorInfo>& biases,
                                         Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsDequantizeSupported(const TensorInfo& input,
                               const TensorInfo& output,
                               Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsDetectionPostProcessSupported(const TensorInfo& boxEncodings,
                                         const TensorInfo& scores,
                                         const TensorInfo& anchors,
                                         const TensorInfo& detectionBoxes,
                                         const TensorInfo& detectionClasses,
                                         const TensorInfo& detectionScores,
                                         const TensorInfo& numDetections,
                                         const DetectionPostProcessDescriptor& descriptor,
                                         Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsDilatedDepthwiseConvolutionSupported(const TensorInfo& input,
                                                const TensorInfo& output,
                                                const DepthwiseConvolution2dDescriptor& descriptor,
                                                const TensorInfo& weights,
                                                const Optional<TensorInfo>& biases,
                                                Optional<std::string&> reasonIfUnsupported =
                                                    EmptyOptional()) const;

    bool IsDivisionSupported(const TensorInfo& input0,
                             const TensorInfo& input1,
                             const TensorInfo& output,
                             Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsElementwiseUnarySupported(const TensorInfo& input,
                                     const TensorInfo& output,
                                     const ElementwiseUnaryDescriptor& descriptor,
                                     Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsFakeQuantizationSupported(const TensorInfo& input,
                                     const FakeQuantizationDescriptor& descriptor,
                                     Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsFillSupported(const TensorInfo& input,
                         const TensorInfo& output,
                         const FillDescriptor& descriptor,
                         Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsFloorSupported(const TensorInfo& input,
                          const TensorInfo& output,
                          Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsFullyConnectedSupported(const TensorInfo& input,
                                   const TensorInfo& output,
                                   const TensorInfo& weights,
                                   const TensorInfo& biases,
                                   const FullyConnectedDescriptor& descriptor,
                                   Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsGatherNdSupported(const TensorInfo& input0,
                             const TensorInfo& input1,
                             const TensorInfo& output,
                             Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsGatherSupported(const TensorInfo& input0,
                           const TensorInfo& input1,
                           const TensorInfo& output,
                           const GatherDescriptor& descriptor,
                           Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsInputSupported(const TensorInfo& input,
                          Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsInstanceNormalizationSupported(const TensorInfo& input,
                                          const TensorInfo& output,
                                          const InstanceNormalizationDescriptor& descriptor,
                                          Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsL2NormalizationSupported(const TensorInfo& input,
                                    const TensorInfo& output,
                                    const L2NormalizationDescriptor& descriptor,
                                    Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsLogicalBinarySupported(const TensorInfo& input0,
                                  const TensorInfo& input1,
                                  const TensorInfo& output,
                                  const LogicalBinaryDescriptor& descriptor,
                                  Optional<std::string&> reasonIfUnsupported) const;

    bool IsLogSoftmaxSupported(const TensorInfo& input,
                               const TensorInfo& output,
                               const LogSoftmaxDescriptor& descriptor,
                               Optional<std::string&> reasonIfUnsupported) const;

    bool IsLstmSupported(const TensorInfo& input,
                         const TensorInfo& outputStateIn,
                         const TensorInfo& cellStateIn,
                         const TensorInfo& scratchBuffer,
                         const TensorInfo& outputStateOut,
                         const TensorInfo& cellStateOut,
                         const TensorInfo& output,
                         const LstmDescriptor& descriptor,
                         const LstmInputParamsInfo& paramsInfo,
                         Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsMaximumSupported(const TensorInfo& input0,
                            const TensorInfo& input1,
                            const TensorInfo& output,
                            Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsMeanSupported(const TensorInfo& input,
                         const TensorInfo& output,
                         const MeanDescriptor& descriptor,
                         Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsMemCopySupported(const TensorInfo& input,
                            const TensorInfo& output,
                            Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsMinimumSupported(const TensorInfo& input0,
                            const TensorInfo& input1,
                            const TensorInfo& output,
                            Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsMultiplicationSupported(const TensorInfo& input0,
                                   const TensorInfo& input1,
                                   const TensorInfo& output,
                                   Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsNormalizationSupported(const TensorInfo& input,
                                  const TensorInfo& output,
                                  const NormalizationDescriptor& descriptor,
                                  Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsOutputSupported(const TensorInfo& output,
                           Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsPadSupported(const TensorInfo& input,
                        const TensorInfo& output,
                        const PadDescriptor& descriptor,
                        Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsPermuteSupported(const TensorInfo& input,
                            const TensorInfo& output,
                            const PermuteDescriptor& descriptor,
                            Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsPooling2dSupported(const TensorInfo& input,
                              const TensorInfo& output,
                              const Pooling2dDescriptor& descriptor,
                              Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsPooling3dSupported(const TensorInfo& input,
                              const TensorInfo& output,
                              const Pooling3dDescriptor& descriptor,
                              Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsQuantizeSupported(const TensorInfo& input,
                             const TensorInfo& output,
                             Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsQLstmSupported(const TensorInfo& input,
                          const TensorInfo& previousOutputIn,
                          const TensorInfo& previousCellStateIn,
                          const TensorInfo& outputStateOut,
                          const TensorInfo& cellStateOut,
                          const TensorInfo& output,
                          const QLstmDescriptor& descriptor,
                          const LstmInputParamsInfo& paramsInfo,
                          Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsRankSupported(const TensorInfo& input,
                         const TensorInfo& output,
                         Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsReduceSupported(const TensorInfo& input,
                           const TensorInfo& output,
                           const ReduceDescriptor& descriptor,
                           Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsReshapeSupported(const TensorInfo& input,
                            const TensorInfo& output,
                            const ReshapeDescriptor& descriptor,
                            Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsResizeSupported(const TensorInfo& input,
                           const TensorInfo& output,
                           const ResizeDescriptor& descriptor,
                           Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsReverseV2Supported(const TensorInfo& input0,
                              const TensorInfo& input1,
                              const TensorInfo& output,
                              Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsShapeSupported(const TensorInfo& input,
                          const TensorInfo& output,
                          Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsSliceSupported(const TensorInfo& input,
                          const TensorInfo& output,
                          const SliceDescriptor& descriptor,
                          Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsSoftmaxSupported(const TensorInfo& input,
                            const TensorInfo& output,
                            const SoftmaxDescriptor& descriptor,
                            Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsSpaceToBatchNdSupported(const TensorInfo& input,
                                   const TensorInfo& output,
                                   const SpaceToBatchNdDescriptor& descriptor,
                                   Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsSpaceToDepthSupported(const TensorInfo& input,
                                 const TensorInfo& output,
                                 const SpaceToDepthDescriptor& descriptor,
                                 Optional<std::string&> reasonIfUnsupported = EmptyOptional())
                                 const;

    bool IsSplitterSupported(const TensorInfo& input,
                             const std::vector<std::reference_wrapper<TensorInfo>>& outputs,
                             const ViewsDescriptor& descriptor,
                             Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsStackSupported(const std::vector<const TensorInfo*>& inputs,
                          const TensorInfo& output,
                          const StackDescriptor& descriptor,
                          Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsStridedSliceSupported(const TensorInfo& input,
                                 const TensorInfo& output,
                                 const StridedSliceDescriptor& descriptor,
                                 Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsSubtractionSupported(const TensorInfo& input0,
                                const TensorInfo& input1,
                                const TensorInfo& output,
                                Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsPreluSupported(const TensorInfo& input,
                          const TensorInfo& alpha,
                          const TensorInfo& output,
                          Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsTileSupported(const TensorInfo& input,
                         const TensorInfo& output,
                         const TileDescriptor& descriptor,
                         Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsTransposeConvolution2dSupported(
        const TensorInfo& input,
        const TensorInfo& output,
        const TransposeConvolution2dDescriptor& descriptor,
        const TensorInfo& weights,
        const Optional<TensorInfo>& biases,
        Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsTransposeSupported(const TensorInfo& input,
                              const TensorInfo& output,
                              const TransposeDescriptor& descriptor,
                              Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;

    bool IsUnidirectionalSequenceLstmSupported(
        const TensorInfo& input,
        const TensorInfo& outputStateIn,
        const TensorInfo& cellStateIn,
        const TensorInfo& outputStateOut,
        const TensorInfo& cellStateOut,
        const TensorInfo& output,
        const UnidirectionalSequenceLstmDescriptor& descriptor,
        const LstmInputParamsInfo& paramsInfo,
        Optional<std::string&> reasonIfUnsupported = EmptyOptional()) const;
};

} // namespace armnn
