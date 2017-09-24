#pragma once
#include "Layer.h"
#include "Tensor1DLayer.h"
#include <cassert>
namespace FengML
{
    class FlattenLayer : public Tensor1DLayer
    {
    public:
        FlattenLayer() {}
        virtual void Initialize();
        virtual void forward();
        virtual void backward();
        void SetSourceLayer(Layer<Tensor3> * _sourceLayer)
        {
            sourceLayer = _sourceLayer;
        }

        virtual LayerBase* Previous()
        {
            return sourceLayer;
        }

    private:
         Layer<Tensor3>* sourceLayer;
    };

    void FlattenLayer::Initialize()
    {
        assert(sourceLayer != nullptr);
        auto length = sourceLayer->Length();
        Tensor1DLayer::Initialize(length);
    }
    
    void FlattenLayer::forward()
    {
        PrintDim();
        //assert(sourceLayer != nullptr);
        //auto& sd = sourceLayer->GetData3D();
        //assert(sd.size() > 0);
        //size_t len = sd[0].Row() * sd[0].Col();
        //auto dst = data.Data();
        //for (auto & mat : sd)
        //{
        //    auto p = mat.Data();
        //    std::copy(p, p + len, dst);
        //    dst += len;
        //}
    }

    void FlattenLayer::backward()
    {
        PrintDim();
        //assert(sourceLayer != nullptr);
        //auto& sd = sourceLayer->GetData3D();
        //assert(sd.size() > 0);
        //auto dim = sourceLayer->Dim3();
        //size_t len = std::get<1>(dim) * std::get<2>(dim);
        //auto _g = gradient.Data();
        //for (auto& mat : sd)
        //{
        //    std::copy(_g, _g + len, mat.Data());
        //    _g += len;
        //}
    }
}