#pragma once
#include "Layer.h"
#include "FlattenLayer.h"
#include <iostream>
namespace FengML
{
    class Tensor3DLayer: public Layer<Tensor3>
    {
    public:
        Tensor3DLayer(): flattenLayer(nullptr)
        {
        }
        Tensor3DLayer(typename Tensor3::DT dim) :Layer<Tensor3>(dim),
            flattenLayer(nullptr)
        {

        }
        virtual std::shared_ptr<LayerBase> Next()
        {
            if (nextLayer == nullptr)
            {
                return flattenLayer;
            }

            return nextLayer;
        }

        virtual LayerBase& Flatten();

        virtual typename Tensor3::DT Dim3()
        {
            return dim;
        }

        virtual typename Tensor3::DataType& GetData3D()
        {
            return data;
        }

        virtual typename Tensor3::DataType& GetGradient3D()
        {
            return gradient;
        }

        virtual void PrintDim();
    protected:
        std::shared_ptr<FlattenLayer> flattenLayer;
    };

    LayerBase& Tensor3DLayer::Flatten()
    {
        auto flatten = std::shared_ptr<FlattenLayer>(new FlattenLayer());
        this->flattenLayer = flatten;
        flatten->SetSourceLayer(this);
        flatten->Initialize();
        return *flatten;
    }

    void Tensor3DLayer::PrintDim()
    {
        auto d0 = std::get<0>(dim);
        auto d1 = std::get<1>(dim);
        auto d2 = std::get<2>(dim);
        std::cout << "dim3: [" << d0 << "," << d1 << ","
            << d2 << "]" << std::endl;
    }
}
