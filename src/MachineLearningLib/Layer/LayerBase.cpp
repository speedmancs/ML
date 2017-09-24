#include "LayerBase.h"
namespace FengML
{
    typename Tensor1::DataType LayerBase::dummy1d;
    typename Tensor3::DataType LayerBase::dummy3d;

    LayerBase& LayerBase::Add(std::shared_ptr<LayerBase> _nextLayer)
    {
        nextLayer = _nextLayer;
        nextLayer->previousLayer = this;
        nextLayer->Initialize();
        return *nextLayer;
    }

    size_t LayerBase::Dim1()
    {
        return 0;
    }

    Dim3Type LayerBase::Dim3()
    {
        Dim3Type dim = { 0, 0, 0 };
        return dim;
    }

    typename Tensor1::DataType& LayerBase::GetData1D()
    {
        return dummy1d;
    }

    typename Tensor1::DataType& LayerBase::GetGradient1D()
    {
        return dummy1d;
    }

    typename Tensor3::DataType& LayerBase::GetData3D()
    {
        return dummy3d;
    }

    typename Tensor3::DataType& LayerBase::GetGradient3D()
    {
        return dummy3d;
    }

    LayerBase* LayerBase::Previous()
    {
        return previousLayer;
    }

    std::shared_ptr<FlattenLayer> LayerBase::Flatten()
    {
        return std::shared_ptr<FlattenLayer>();
    }

    std::shared_ptr<LayerBase> LayerBase::Next()
    {
        return nextLayer;
    }
}