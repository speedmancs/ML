#pragma once
#include "Layer.h"
#include "Tensor3DLayer.h"
#include <iostream>
namespace FengML
{
    class PoolingLayer : public Tensor3DLayer
    {
    public:
        PoolingLayer(size_t _pooling_size):
            pooling_size(_pooling_size){}
        virtual void forward();
        virtual void backward();
        virtual void Initialize();
    private:
        size_t pooling_size;
    };

    void PoolingLayer::Initialize()
    {
        assert(previousLayer != nullptr);
        auto _dim = previousLayer->Dim3();
        auto newDim = Dim3Type(std::get<0>(_dim), 
            std::get<1>(_dim) / pooling_size,
            std::get<2>(_dim) / pooling_size);
        Tensor3DLayer::Initialize(newDim);
    }

    void PoolingLayer::forward()
    {
        // to do
        PrintDim();
    }

    void PoolingLayer::backward()
    {
        // to do
        PrintDim();
    }
}

