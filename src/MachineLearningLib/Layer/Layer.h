#pragma once
#include "..\Common\Vector.h"
#include "..\Common\Matrix.h"
#include "LayerBase.h"
#include <vector>
#include <memory>
namespace FengML
{
    template<typename T>
    class Layer : public LayerBase
    {
    public:
        Layer(){}
        Layer(typename T::DT dimension){}
        void Initialize(typename T::DT dim);
        virtual void Initialize();
        size_t Length();
        void SetData(const typename T::DataType& _d);
    protected:
        typename T::DT dim;
        typename T::DataType data;
        typename T::DataType gradient;
    };

    template<typename T>
    void Layer<T>::SetData(const typename T::DataType& _d)
    {
        data = _d;
    }

    template<>
    Layer<Tensor1>::Layer(size_t dimension) : dim(dimension)
    {
        Initialize(dimension);
    }

    template<>
    void Layer<Tensor1>::Initialize()
    {
        assert(previousLayer != nullptr);
        auto _dim = previousLayer->Dim1();
        Initialize(_dim);
    }

    template<>
    void Layer<Tensor1>::Initialize(size_t _dim)
    {
        dim = _dim;
        data.Resize(dim);
        gradient.Resize(dim);
    }

    template<>
    size_t Layer<Tensor1>::Length()
    {
        return dim;
    }

    template<>
    Layer<Tensor3>::Layer(typename Tensor3::DT dimension) :
        dim(dimension)
    {
        Initialize(dimension);
    }

    template<>
    void Layer<Tensor3>::Initialize()
    {
        assert(previousLayer != nullptr);
        auto _dim = previousLayer->Dim3();
        Initialize(_dim);
    }

    template<>
    void Layer<Tensor3>::Initialize(typename Tensor3::DT dimension)
    {
        dim = dimension;
        size_t channel = std::get<0>(dimension);
        size_t height = std::get<1>(dimension);
        size_t width = std::get<2>(dimension);
        data.resize(channel);
        gradient.resize(channel);

        for (auto & item : data)
        {
            item.Resize(height, width);
        }

        for (auto & item : gradient)
        {
            item.Resize(height, width);
        }
    }

    template<>
    size_t Layer<Tensor3>::Length()
    {
        size_t channel = std::get<0>(dim);
        size_t height = std::get<1>(dim);
        size_t width = std::get<2>(dim);
        return channel * height * width;
    }
}