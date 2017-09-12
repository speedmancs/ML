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
        void ComputeGradient(const Vector<float>& x, const OneHotVector& y) override;
        void Update() override;
        void Setup();
        size_t Eval(const Vector<float>& data) override;
        void ClearGradient() override;
        bool Load(const std::string& filePath) override;
        bool Save() override;
    private:
        Matrix<float> W;
        Vector<float> b;
        Matrix<float> dW;
        Vector<float> db;
        Vector<float> y_diff;
    };
}