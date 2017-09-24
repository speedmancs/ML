#pragma once
#include "Layer.h"
#include <iostream>
namespace FengML
{
    class Tensor1DLayer : public Layer<Tensor1>
    {
    public:
        Tensor1DLayer()
        {
        }
        Tensor1DLayer(size_t dim) :Layer<Tensor1>(dim)
        {

        }

        virtual size_t Dim1()
        {
            return dim;
        }

        virtual typename Tensor1::DataType& GetData1D()
        {
            return data;
        }

        virtual typename Tensor1::DataType& GetGradient1D()
        {
            return gradient;
        }

        virtual void PrintDim();
    };

    void Tensor1DLayer::PrintDim()
    {
        std::cout << "dim:" << dim << std::endl;
    }
}
