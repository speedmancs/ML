#include "LayerBase.h"
#include <iostream>
namespace FengML
{    
    static LayerBase dummyLayer;
    static typename Tensor1::DataType dummy1d;
    static typename Tensor3::DataType dummy3d;
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

    LayerBase& LayerBase::Flatten()
    {
        return dummyLayer;
    }

    std::shared_ptr<LayerBase> LayerBase::Next()
    {
        return nextLayer;
    }

    void LayerBase::PrintDim()
    {
        std::cout << "dummpy layer, no dimension" << std::endl;
    }
}