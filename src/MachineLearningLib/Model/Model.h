#pragma once
#include <string>
#include "..\Data\DataSet.h"
#include "..\Config\Configuration.h"
namespace FengML
{
    class Model
    {
    public:
        Model(const Configuration& _config) : m_config(_config) {}
        void Fit(const DataSet& trainingSet, const DataSet& validateSet);
        float Test(const DataSet& dataSet, float& loss);
        virtual size_t Eval(const Vector<float>& data) = 0;
        virtual bool Load(const std::string& filePath) = 0;
        virtual bool Save(const std::string& filePath) = 0;
        virtual void Update() = 0;
        virtual float Loss(const OneHotVector& y) = 0;
        virtual void ClearGradient() = 0;
        virtual void ComputeGradient(const Vector<float>& x, const OneHotVector& y) = 0;
    protected:
        const Configuration& m_config;
    };
}