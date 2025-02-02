//
// Copyright © 2017-2023 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#include <backendsCommon/test/EndToEndTestImpl.hpp>

#include <backendsCommon/test/ActivationEndToEndTestImpl.hpp>
#include <backendsCommon/test/AdditionEndToEndTestImpl.hpp>
#include <backendsCommon/test/ArgMinMaxEndToEndTestImpl.hpp>
#include <backendsCommon/test/BatchMatMulEndToEndTestImpl.hpp>
#include <backendsCommon/test/ComparisonEndToEndTestImpl.hpp>
#include <backendsCommon/test/ConcatEndToEndTestImpl.hpp>
#include <backendsCommon/test/DepthToSpaceEndToEndTestImpl.hpp>
#include <backendsCommon/test/DequantizeEndToEndTestImpl.hpp>
#include <backendsCommon/test/ElementwiseBinaryEndToEndTestImpl.hpp>
#include <backendsCommon/test/ElementwiseUnaryEndToEndTestImpl.hpp>
#include <backendsCommon/test/FillEndToEndTestImpl.hpp>
#include <backendsCommon/test/InstanceNormalizationEndToEndTestImpl.hpp>
#include <backendsCommon/test/PreluEndToEndTestImpl.hpp>
#include <backendsCommon/test/QLstmEndToEndTestImpl.hpp>
#include <backendsCommon/test/QuantizedLstmEndToEndTestImpl.hpp>
#include <backendsCommon/test/ReduceEndToEndTestImpl.hpp>
#include <backendsCommon/test/ReshapeEndToEndTestImpl.hpp>
#include <backendsCommon/test/ReverseV2EndToEndTestImpl.hpp>
#include <backendsCommon/test/SliceEndToEndTestImpl.hpp>
#include <backendsCommon/test/SpaceToDepthEndToEndTestImpl.hpp>
#include <backendsCommon/test/SplitterEndToEndTestImpl.hpp>
#include <backendsCommon/test/SubgraphUtilsTest.hpp>
#include <backendsCommon/test/TileEndToEndTestImpl.hpp>
#include <backendsCommon/test/TransposeConvolution2dEndToEndTestImpl.hpp>
#include <backendsCommon/test/TransposeEndToEndTestImpl.hpp>

#include <doctest/doctest.h>

TEST_SUITE("ClEndToEnd")
{
std::vector<armnn::BackendId> clDefaultBackends = {armnn::Compute::GpuAcc};

// ElementwiseUnary
// Abs
TEST_CASE("ClAbsEndToEndTestFloat32")
{
    ElementwiseUnarySimpleEndToEnd<armnn::DataType::Float32>(clDefaultBackends,
                                                             UnaryOperation::Abs);
}
// Rsqrt
TEST_CASE("ClRsqrtEndToEndTestFloat32")
{
    ElementwiseUnarySimpleEndToEnd<armnn::DataType::Float32>(clDefaultBackends,
                                                             UnaryOperation::Rsqrt);
}

// ElementwiseBinary
// Addition
TEST_CASE("ClAdditionEndToEndFloat32Test")
{
    AdditionEndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClAdditionEndToEndUint8Test")
{
    AdditionEndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

// Power
TEST_CASE("ClPowerEndToEndTestFloat32")
{
    ElementwiseBinarySimpleEndToEnd<armnn::DataType::Float32>(clDefaultBackends, BinaryOperation::Power);
}

// SqDiff
TEST_CASE("ClSquaredDifferenceEndToEndTestFloat32")
{
    ElementwiseBinarySimpleEndToEnd<armnn::DataType::Float32>(clDefaultBackends, BinaryOperation::SqDiff);
}

TEST_CASE("ClSquaredDifferenceEndToEndTestUint8")
{
    ElementwiseBinarySimpleEndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends, BinaryOperation::SqDiff);
}

// Batch Mat Mul
TEST_CASE("ClBatchMatMulEndToEndFloat32Test")
{
    BatchMatMulEndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClBatchMatMulEndToEndInt8Test")
{
    BatchMatMulEndToEnd<armnn::DataType::QAsymmS8>(clDefaultBackends);
}

// Constant
TEST_CASE("ConstantUsage_Cl_Float32")
{
    ConstantUsageFloat32Test(clDefaultBackends);
}

TEST_CASE("ClConcatEndToEndDim0Test")
{
    ConcatDim0EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClConcatEndToEndDim0Uint8Test")
{
    ConcatDim0EndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClConcatEndToEndDim1Test")
{
    ConcatDim1EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClConcatEndToEndDim1Uint8Test")
{
    ConcatDim1EndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClConcatEndToEndDim3Test")
{
    ConcatDim3EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClConcatEndToEndDim3Uint8Test")
{
    ConcatDim3EndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

// DepthToSpace
TEST_CASE("DephtToSpaceEndToEndNchwFloat32")
{
    DepthToSpaceEndToEnd<armnn::DataType::Float32>(clDefaultBackends, armnn::DataLayout::NCHW);
}

TEST_CASE("DephtToSpaceEndToEndNchwFloat16")
{
    DepthToSpaceEndToEnd<armnn::DataType::Float16>(clDefaultBackends, armnn::DataLayout::NCHW);
}

TEST_CASE("DephtToSpaceEndToEndNchwUint8")
{
    DepthToSpaceEndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends, armnn::DataLayout::NCHW);
}

TEST_CASE("DephtToSpaceEndToEndNchwInt16")
{
    DepthToSpaceEndToEnd<armnn::DataType::QSymmS16>(clDefaultBackends, armnn::DataLayout::NCHW);
}

TEST_CASE("DephtToSpaceEndToEndNhwcFloat32")
{
    DepthToSpaceEndToEnd<armnn::DataType::Float32>(clDefaultBackends, armnn::DataLayout::NHWC);
}

TEST_CASE("DephtToSpaceEndToEndNhwcFloat16")
{
    DepthToSpaceEndToEnd<armnn::DataType::Float16>(clDefaultBackends, armnn::DataLayout::NHWC);
}

TEST_CASE("DephtToSpaceEndToEndNhwcUint8")
{
    DepthToSpaceEndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends, armnn::DataLayout::NHWC);
}

TEST_CASE("DephtToSpaceEndToEndNhwcInt16")
{
    DepthToSpaceEndToEnd<armnn::DataType::QSymmS16>(clDefaultBackends, armnn::DataLayout::NHWC);
}

// Dequantize
TEST_CASE("DequantizeEndToEndSimpleTest")
{
    DequantizeEndToEndSimple<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("DequantizeEndToEndOffsetTest")
{
    DequantizeEndToEndOffset<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

// Slice
TEST_CASE("ClSliceEndtoEndTestFloat32")
{
    SliceEndToEnd<DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClSliceEndtoEndTestInt32")
{
    SliceEndToEnd<DataType::Signed32>(clDefaultBackends);
}

TEST_CASE("ClSliceEndtoEndTestFloat16")
{
    SliceEndToEndFloat16<DataType::Float16>(clDefaultBackends);
}

TEST_CASE("ClStridedSliceInvalidSliceEndToEndTest")
{
    StridedSliceInvalidSliceEndToEndTest(clDefaultBackends);
}

TEST_CASE("ClEluEndToEndTestFloat32")
{
    EluEndToEndTest<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClEluEndToEndTestFloat16")
{
    EluEndToEndTest<armnn::DataType::Float16>(clDefaultBackends);
}

TEST_CASE("ClGreaterSimpleEndToEndTest")
{
    const std::vector<uint8_t> expectedOutput({ 0, 0, 0, 0,  1, 1, 1, 1,
                                                0, 0, 0, 0,  0, 0, 0, 0 });

    ComparisonSimpleEndToEnd<armnn::DataType::Float32>(clDefaultBackends,
                                                       ComparisonOperation::Greater,
                                                       expectedOutput);
}

TEST_CASE("ClGreaterSimpleEndToEndUint8Test")
{
    const std::vector<uint8_t> expectedOutput({ 0, 0, 0, 0,  1, 1, 1, 1,
                                                0, 0, 0, 0,  0, 0, 0, 0 });

    ComparisonSimpleEndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends,
                                                               ComparisonOperation::Greater,
                                                               expectedOutput);
}

TEST_CASE("ClGreaterBroadcastEndToEndTest")
{
    const std::vector<uint8_t> expectedOutput({ 0, 1, 0, 0, 0, 1,
                                                1, 1, 1, 1, 1, 1 });

    ComparisonBroadcastEndToEnd<armnn::DataType::Float32>(clDefaultBackends,
                                                          ComparisonOperation::Greater,
                                                          expectedOutput);
}

TEST_CASE("ClGreaterBroadcastEndToEndUint8Test")
{
    const std::vector<uint8_t> expectedOutput({ 0, 1, 0, 0, 0, 1,
                                                1, 1, 1, 1, 1, 1 });

    ComparisonBroadcastEndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends,
                                                                  ComparisonOperation::Greater,
                                                                  expectedOutput);
}

// HardSwish
TEST_CASE("ClHardSwishEndToEndTestFloat32")
{
    HardSwishEndToEndTest<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClHardSwishEndToEndTestFloat16")
{
    HardSwishEndToEndTest<armnn::DataType::Float16>(clDefaultBackends);
}

TEST_CASE("ClHardSwishEndToEndTestQAsymmS8")
{
    HardSwishEndToEndTest<armnn::DataType::QAsymmS8>(clDefaultBackends);
}

TEST_CASE("ClHardSwishEndToEndTestQAsymmU8")
{
    HardSwishEndToEndTest<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClHardSwishEndToEndTestQSymmS16")
{
    HardSwishEndToEndTest<armnn::DataType::QSymmS16>(clDefaultBackends);
}

// InstanceNormalization
TEST_CASE("ClInstanceNormalizationNhwcEndToEndTest1")
{
    InstanceNormalizationNhwcEndToEndTest1(clDefaultBackends);
}

TEST_CASE("ClInstanceNormalizationNchwEndToEndTest1")
{
    InstanceNormalizationNchwEndToEndTest1(clDefaultBackends);
}

TEST_CASE("ClInstanceNormalizationNhwcEndToEndTest2")
{
    InstanceNormalizationNhwcEndToEndTest2(clDefaultBackends);
}

TEST_CASE("ClInstanceNormalizationNchwEndToEndTest2")
{
    InstanceNormalizationNchwEndToEndTest2(clDefaultBackends);
}

// Fill
TEST_CASE("ClFillEndToEndTest")
{
    FillEndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("RefFillEndToEndTestFloat16")
{
    FillEndToEnd<armnn::DataType::Float16>(clDefaultBackends);
}

TEST_CASE("ClFillEndToEndTestInt32")
{
    FillEndToEnd<armnn::DataType::Signed32>(clDefaultBackends);
}

// Prelu
TEST_CASE("ClPreluEndToEndFloat32Test")
{
    PreluEndToEndNegativeTest<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClPreluEndToEndTestUint8")
{
    PreluEndToEndPositiveTest<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

// Reduce
TEST_CASE("ClReduceEndToEndTest")
{
    ReduceEndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClReduceEndToEndTestFloat16")
{
    ReduceEndToEnd<armnn::DataType::Float16>(clDefaultBackends);
}

// Reshape
TEST_CASE("ClReshapeEndToEndTest")
{
    ReshapeEndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClReshapeEndToEndTestFloat16")
{
    ReshapeEndToEndFloat16<armnn::DataType::Float16>(clDefaultBackends);
}

// ReverseV2
TEST_CASE("ClReverseV2EndToEndTest")
{
    ReverseV2EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

// Space to depth
TEST_CASE("ClSpaceToDepthNhwcEndToEndTest1")
{
    SpaceToDepthNhwcEndToEndTest1(clDefaultBackends);
}

TEST_CASE("ClSpaceToDepthNchwEndToEndTest1")
{
    SpaceToDepthNchwEndToEndTest1(clDefaultBackends);
}

TEST_CASE("ClSpaceToDepthNhwcEndToEndTest2")
{
    SpaceToDepthNhwcEndToEndTest2(clDefaultBackends);
}

TEST_CASE("ClSpaceToDepthNchwEndToEndTest2")
{
    SpaceToDepthNchwEndToEndTest2(clDefaultBackends);
}

// Split
TEST_CASE("ClSplitter1dEndToEndTest")
{
    Splitter1dEndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClSplitter1dEndToEndUint8Test")
{
    Splitter1dEndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClSplitter2dDim0EndToEndTest")
{
    Splitter2dDim0EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClSplitter2dDim1EndToEndTest")
{
    Splitter2dDim1EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClSplitter2dDim0EndToEndUint8Test")
{
    Splitter2dDim0EndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClSplitter2dDim1EndToEndUint8Test")
{
    Splitter2dDim1EndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClSplitter3dDim0EndToEndTest")
{
    Splitter3dDim0EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClSplitter3dDim1EndToEndTest")
{
    Splitter3dDim1EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClSplitter3dDim2EndToEndTest")
{
    Splitter3dDim2EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClSplitter3dDim0EndToEndUint8Test")
{
    Splitter3dDim0EndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClSplitter3dDim1EndToEndUint8Test")
{
    Splitter3dDim1EndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClSplitter3dDim2EndToEndUint8Test")
{
    Splitter3dDim2EndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClSplitter4dDim0EndToEndTest")
{
    Splitter4dDim0EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClSplitter4dDim1EndToEndTest")
{
    Splitter4dDim1EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClSplitter4dDim2EndToEndTest")
{
    Splitter4dDim2EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClSplitter4dDim3EndToEndTest")
{
    Splitter4dDim3EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClSplitter4dDim0EndToEndUint8Test")
{
    Splitter4dDim0EndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClSplitter4dDim1EndToEndUint8Test")
{
    Splitter4dDim1EndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClSplitter4dDim2EndToEndUint8Test")
{
    Splitter4dDim2EndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClSplitter4dDim3EndToEndUint8Test")
{
    Splitter4dDim3EndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

// Tile
TEST_CASE("ClTileEndToEndFloat32")
{
    TileEndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClTileEndToEndFloat16")
{
    TileEndToEnd<armnn::DataType::Float16>(clDefaultBackends);
}

TEST_CASE("ClTileEndToEndQAsymmS8")
{
    TileEndToEnd<armnn::DataType::QAsymmS8>(clDefaultBackends);
}

TEST_CASE("ClTileEndToEndQAsymmU8")
{
    TileEndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClTileEndToEndQSymmS8")
{
    TileEndToEnd<armnn::DataType::QSymmS8>(clDefaultBackends);
}

TEST_CASE("ClTileEndToEndQSymmS16")
{
    TileEndToEnd<armnn::DataType::QSymmS16>(clDefaultBackends);
}

TEST_CASE("ClTileEndToEndSigned32")
{
    TileEndToEnd<armnn::DataType::Signed32>(clDefaultBackends);
}

// TransposeConvolution2d
TEST_CASE("ClTransposeConvolution2dEndToEndFloatNchwTest")
{
    TransposeConvolution2dEndToEnd<armnn::DataType::Float32, armnn::DataType::Float32>(
        clDefaultBackends, armnn::DataLayout::NCHW);
}

TEST_CASE("ClTransposeConvolution2dEndToEndUint8NchwTest")
{
    TransposeConvolution2dEndToEnd<armnn::DataType::QAsymmU8, armnn::DataType::Signed32>(
        clDefaultBackends, armnn::DataLayout::NCHW);
}

TEST_CASE("ClTransposeConvolution2dEndToEndFloatNhwcTest")
{
    TransposeConvolution2dEndToEnd<armnn::DataType::Float32, armnn::DataType::Float32>(
        clDefaultBackends, armnn::DataLayout::NHWC);
}

TEST_CASE("ClTransposeConvolution2dEndToEndUint8NhwcTest")
{
    TransposeConvolution2dEndToEnd<armnn::DataType::QAsymmU8, armnn::DataType::Signed32>(
        clDefaultBackends, armnn::DataLayout::NHWC);
}

// Transpose
TEST_CASE("ClTransposeEndToEndTest")
{
TransposeEndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClQuantizedLstmEndToEndTest")
{
    QuantizedLstmEndToEnd(clDefaultBackends);
}

// ArgMinMax
TEST_CASE("ClArgMaxSimpleTest")
{
    ArgMaxEndToEndSimple<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClArgMinSimpleTest")
{
    ArgMinEndToEndSimple<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClArgMaxAxis0Test")
{
    ArgMaxAxis0EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClArgMinAxis0Test")
{
    ArgMinAxis0EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClArgMaxAxis1Test")
{
    ArgMaxAxis1EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClArgMinAxis1Test")
{
    ArgMinAxis1EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClArgMaxAxis2Test")
{
    ArgMaxAxis2EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClArgMinAxis2Test")
{
    ArgMinAxis2EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClArgMaxAxis3Test")
{
    ArgMaxAxis3EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClArgMinAxis3Test")
{
    ArgMinAxis3EndToEnd<armnn::DataType::Float32>(clDefaultBackends);
}

TEST_CASE("ClArgMaxSimpleTestQAsymmU8")
{
    ArgMaxEndToEndSimple<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClArgMinSimpleTestQAsymmU8")
{
    ArgMinEndToEndSimple<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClArgMaxAxis0TestQAsymmU8")
{
    ArgMaxAxis0EndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClArgMinAxis0TestQAsymmU8")
{
    ArgMinAxis0EndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClArgMaxAxis1TestQAsymmU8")
{
    ArgMaxAxis1EndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClArgMinAxis1TestQAsymmU8")
{
    ArgMinAxis1EndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClArgMaxAxis2TestQAsymmU8")
{
    ArgMaxAxis2EndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClArgMinAxis2TestQAsymmU8")
{
    ArgMinAxis2EndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClArgMaxAxis3TestQAsymmU8")
{
    ArgMaxAxis3EndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClArgMinAxis3TestQAsymmU8")
{
    ArgMinAxis3EndToEnd<armnn::DataType::QAsymmU8>(clDefaultBackends);
}

TEST_CASE("ClQLstmEndToEndTest")
{
    QLstmEndToEnd(clDefaultBackends);
}

TEST_CASE("ClForceImportWithMisalignedInputBuffersEndToEndTest"
          // Currently, the CL workload for activation does not support tensor handle replacement so this test case
          // will always fail.
          * doctest::skip(true))
{
    ForceImportWithMisalignedInputBuffersEndToEndTest(clDefaultBackends);
}

TEST_CASE("ClForceImportWithMisalignedOutputBuffersEndToEndTest"
          // Currently, the CL workload for activation does not support tensor handle replacement so this test case
          // will always fail.
          * doctest::skip(true))
{
    ForceImportWithMisalignedOutputBuffersEndToEndTest(clDefaultBackends);
}

TEST_CASE("ClForceImportWithMisalignedInputAndOutputBuffersEndToEndTest")
{
    ForceImportWithMisalignedInputAndOutputBuffersEndToEndTest(clDefaultBackends);
}

}
