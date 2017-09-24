#pragma once
#include <memory>
#include <tuple>
#include "..\Common\Vector.h"
#include "..\Common\Matrix.h"
namespace FengML
{
    class FlattenLayer;
    class Tensor1
    {
    public:
        typedef size_t DT;
        typedef Vector<float> DataType;
    };

    class Tensor3
    {
    public:
        typedef std::tuple<size_t, size_t, size_t> DT;
        typedef std::vector<Matrix<float>> DataType;
    };

    class LayerBase
    {
    public:
        LayerBase() : previousLayer(nullptr), nextLayer(nullptr){}
        virtual void forward() {};
        virtual void backward() {};
        virtual LayerBase* Previous() {
            return previousLayer;
        }

        virtual std::shared_ptr<FlattenLayer> Flatten()
        {
            return std::shared_ptr<FlattenLayer>();
        }

        virtual std::shared_ptr<LayerBase> Next()
        {
            return nextLayer;
        }
        virtual size_t Dim1()
        {
            return 0;
        }

        virtual void Initialize(){}

        LayerBase& Add(std::shared_ptr<LayerBase> _nextLayer)
        {
            nextLayer = _nextLayer;
            nextLayer->previousLayer = this;
            nextLayer->Initialize();
            return *nextLayer;
        }

        virtual typename Tensor3::DT Dim3()
        {
            typename Tensor3::DT dim = { 0, 0, 0 };
            return dim;
        }

        virtual typename Tensor1::DataType& GetData1D()
        {
            return dummy1d;
        }
        virtual typename Tensor1::DataType& GetGradient1D()
        {
            return dummy1d;
        }
        virtual typename Tensor3::DataType& GetData3D()
        {
            return dummy3d;
        }
        virtual typename Tensor3::DataType& GetGradient3D()
        {
            return dummy3d;
        }
    protected:
        typename Tensor1::DataType dummy1d;
        typename Tensor3::DataType dummy3d;

        LayerBase* previousLayer;
        std::shared_ptr<LayerBase> nextLayer;
    };
}
