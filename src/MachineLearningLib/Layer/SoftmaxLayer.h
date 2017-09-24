#pragma once
#include "Layer.h"
#include "Tensor1DLayer.h"
#include <cassert>
namespace FengML
{
    class SoftmaxLayer : public Tensor1DLayer
    {
    public:
        SoftmaxLayer() {}
        void SetTarget(const OneHotVector& _t)
        {
            target = _t;
        }

        virtual void forward();
        virtual void backward();
    protected:
        OneHotVector target;
    };

    void SoftmaxLayer::forward()
    {
        PrintDim();
        //assert(previousLayer != nullptr);
        //auto& sd = previousLayer->GetData1D();
        //this->data = sd;
        //this->data.SoftMax();
    }

    void SoftmaxLayer::backward()
    {
        PrintDim();
        //assert(previousLayer != nullptr);
        //auto& g = previousLayer->GetGradient1D();
        //g = this->data;
        //g.Sub(target);
    }
}