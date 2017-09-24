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

    typedef typename Tensor3::DT Dim3Type;

    class LayerBase
    {
    public:
        LayerBase() : previousLayer(nullptr), nextLayer(nullptr){}
        virtual void forward() 
        {
            PrintDim();
        }
        virtual void backward() 
        {
            PrintDim();
        }
        virtual LayerBase* Previous();
        virtual std::shared_ptr<FlattenLayer> Flatten();
        virtual std::shared_ptr<LayerBase> Next();
        virtual void Initialize() {}
        LayerBase& Add(std::shared_ptr<LayerBase> _nextLayer);
        virtual size_t Dim1();
        virtual Dim3Type Dim3();
        virtual void PrintDim() = 0;
        virtual typename Tensor1::DataType& GetData1D();
        virtual typename Tensor1::DataType& GetGradient1D();
        virtual typename Tensor3::DataType& GetData3D();
        virtual typename Tensor3::DataType& GetGradient3D();
    protected:
        static typename Tensor1::DataType dummy1d;
        static typename Tensor3::DataType dummy3d;
        LayerBase* previousLayer;
        std::shared_ptr<LayerBase> nextLayer;
    };
}
