#pragma once
#include "Model.h"
#include "..\Common\OneHotVector.h"
#include <string>
namespace FengML
{
    class LRModel: public Model
    {
    public:
        LRModel() = default;
        LRModel(const Configuration& config);
        void Fit(const DataSet& trainingSet) override;
        void Fit(const Vector<float>& x, const OneHotVector& y);
        size_t Eval(const Vector<float>& data) override;
        bool Load(const std::string& filePath) override;
        bool Save(const std::string& filePath) override;
    private:
        Configuration m_config;
        Matrix<float> W;
        Vector<float> b;
        Matrix<float> dW;
        Vector<float> db;
        Vector<float> y_hat;
    };
}