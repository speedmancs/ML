#pragma once
#include "Layer.h"
#include "Tensor3DLayer.h"
#include "Tensor1DLayer.h"
#include <iostream>
namespace FengML
{
    //enum ActivationType
    //{
    //    ReLu = 0,
    //    Sigmod = 1,
    //    Tanh = 2
    //};

    class Sigmod
    {
    public:
        float operator ()(float x)
        {
            return 1.0f / (1.0f + exp(-x));
        }

        float d(float x)
        {
            float v = (*this)(x);
            return v * (1 - v);
        }
    };

    class ReLu
    {
    public:
        float operator ()(float x)
        {
            if (x > 0) return x;
            return 0;
        }

        float d(float x)
        {
            if (x > 0) return 1;
            return 0;
        }
    };

    class Tanh
    {
    public:
        float operator ()(float x)
        {
            float v1 = exp(x);
            float v2 = exp(-x);
            return (v1 - v2) / (v1 + v2);
        }

        float d(float x)
        {
            float v = (*this)(x);
            return 1 - v * v;
        }
    };
    template<typename T, typename U>
    class ActivationLayer;

    template<typename U>
    class ActivationLayer<Tensor1, U> : public Tensor1DLayer
    {
    public:
        ActivationLayer() {}
        virtual void forward();
        virtual void backward();
    };


    template<typename U>
    class ActivationLayer<Tensor3, U> : public Tensor3DLayer
    {
    public:
        ActivationLayer() {}
        virtual void forward();
        virtual void backward();
    };

    template<typename U>
    void ActivationLayer<Tensor1, U>::forward()
    {
        auto src = previousLayer->GetData1D().Data();
        auto dst = data.Data();
        U func;
        for (size_t i = 0; i < Length(); i++)
        {
            *dst = func(*src);
            src++; dst++;
        }
    }

    template<typename U>
    void ActivationLayer<Tensor3, U>::forward()
    {
        U func;
        auto channel = std::get<0>(dim);
        size_t len = std::get<1>(dim) * std::get<2>(dim);
        for (size_t i = 0; i < channel; i++)
        {
            auto src = previousLayer->GetData3D()[i].Data();
            auto dst = data[i].Data();
            for (size_t j = 0; j < len; j++)
            {
                *dst = func(*src);
                src++; dst++;
            }
        }
    }

    template<typename U>
    void ActivationLayer<Tensor1, U>::backward()
    {
        auto _g = gradient.Data();
        auto dst_data = previousLayer->GetData1D().Data();
        auto dst_g = previousLayer->GetGradient1D().Data();
        U func;
        for (size_t i = 0; i < Length(); i++)
        {
            *dst_g = func.d(*dst_data) * (*_g);
            dst_g++; dst_data++; _g++;
        }
    }

    template<typename U>
    void ActivationLayer<Tensor3, U>::backward()
    {
        U func;
        auto channel = std::get<0>(dim);
        size_t len = std::get<1>(dim) * std::get<2>(dim);
        for (size_t i = 0; i < channel; i++)
        {
            auto dst_data = previousLayer->GetData3D()[i].Data();
            auto dst_g = previousLayer->GetGradient3D()[i].Data();
            auto _g = gradient[i].Data();
            for (size_t j = 0; j < len; j++)
            {
                *dst_g = func.d(*dst_data) * (*_g);
                _g++; dst_data++; dst_g++;
            }
        }
    }
}
