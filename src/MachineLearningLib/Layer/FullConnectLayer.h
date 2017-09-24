#pragma once
#include "Layer.h"
#include "..\Common\Matrix.h"
#include "..\Common\Vector.h"
#include "Tensor1DLayer.h"
#include <iostream>
namespace FengML
{
    class FullConnectLayer : public Tensor1DLayer
    {
    public:
        FullConnectLayer(size_t dim) :
            Tensor1DLayer(dim)
        {
        }

        virtual void Initialize();
        virtual void forward();
        virtual void backward();
    protected:
        Matrix<float> weight;
        Vector<float> bias;
    };

    void FullConnectLayer::Initialize()
    {
        Tensor1DLayer::Initialize(dim);
    }

    void FullConnectLayer::forward()
    {
        PrintDim();
        // to do
    }

    void FullConnectLayer::backward()
    {
        PrintDim();
        // to do
    }
}
