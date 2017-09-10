#pragma once
#include "Model.h"
#include "..\Common\OneHotVector.h"
#include "..\Config\VanillaNNConfiguration.h"
#include <string>
namespace FengML
{
    class VanillaNNModel : public Model
    {
    public:
        VanillaNNModel() = default;
        VanillaNNModel(const VanillaNNConfiguration& config);
        void ComputeGradient(const Vector<float>& x, const OneHotVector& y) override;
        void Update() override;
        size_t Eval(const Vector<float>& data) override;
        float Loss(const OneHotVector& y) override;
        void ClearGradient() override;
        bool Load(const std::string& filePath) override;
        bool Save(const std::string& filePath) override;
    private:
        const VanillaNNConfiguration& m_config;
        std::vector<Vector<float>> biases;
        std::vector<Matrix<float>> weights;
        std::vector<Vector<float>> d_biases;
        std::vector<Matrix<float>> d_weights;

        std::vector<Vector<float>> layers;
        std::vector<Vector<float>> activate_layers;
        std::vector<Vector<float>> gradient_layers;
    };
}