#pragma once
#include "SequenceModel.h"
#include "..\Common\OneHotVector.h"
#include "..\Common\Matrix.h"
#include "..\Common\Vector.h"
#include "..\Config\RNNConfiguration.h"
#include <string>
namespace FengML
{
    class RNNModel : public SequenceModel
    {
    public:
        RNNModel() = default;
        RNNModel(const RNNConfiguration& config);
        void Setup();
        void ComputeGradient(const SeqData& x, const SeqData& y) override;
        void Update() override;
        void Eval(const SeqData& x, std::vector<size_t>& results) override;
        void ClearGradient() override;
        bool Load(const std::string& filePath) override;
        bool Save(const std::string& filePath) override;
    private:
        void PreAllocate(size_t T);
        const RNNConfiguration& m_config;
        Matrix<float> U;
        Matrix<float> V;
        Matrix<float> W;
        Vector<float> bw;
        Vector<float> bv;

        Matrix<float> dU;
        Matrix<float> dV;
        Matrix<float> dW;
        Vector<float> dbw;
        Vector<float> dbv;
        std::vector<Vector<float>> h; // activated hidden layer
        std::vector<Vector<float>> s; // hidden layer
        std::vector<std::vector<Vector<float>>> delta; // gradient of hidden layer
        std::vector<Vector<float>> y_diff; // diff between y_hat and y
        Vector<float> previousHiddenLayer; // the previous hidden layer
    };
}