#pragma once
#include "Layer.h"
#include "Tensor3DLayer.h"
#include "..\Common\Matrix.h"
#include "..\Common\Vector.h"
#include <iostream>
namespace FengML
{
    class ConvLayer : public Tensor3DLayer 
    {
    public:
        ConvLayer(size_t outputChannels, size_t kernelSize,
            size_t _stride = 1):
            K(outputChannels), stride(_stride), F(kernelSize)
        {
        }

        virtual void Initialize();
        virtual void forward();
        virtual void backward();
    private:
        size_t width;
        size_t height;
        size_t K; // output channels
        size_t stride;
        size_t F; // filter size
        std::vector<std::vector<Matrix<float>>> W;
        std::vector<std::vector<float>> bias;
    };

    void ConvLayer::Initialize()
    {
        assert(previousLayer != nullptr);
        auto inputDim = previousLayer->Dim3();
        auto C = std::get<0>(inputDim);
        auto H = std::get<1>(inputDim);
        auto W = std::get<2>(inputDim);
        width = int((W - F) / stride) + 1;
        height = int((H - F) / stride) + 1;
        Dim3Type dim = { K, height, width };
        Tensor3DLayer::Initialize(dim);
    }

    void ConvLayer::forward()
    {
        // to do
    }

    void ConvLayer::backward()
    {
        // to do
    }
}
