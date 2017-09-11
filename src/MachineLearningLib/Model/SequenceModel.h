#pragma once
#include "..\Config\RNNConfiguration.h"
#include "..\Data\SeqDataSet.h"
namespace FengML
{
    class SequenceModel
    {
    public:
        SequenceModel(const Configuration& _config) : m_config(_config) {}
        void Fit(const SeqDataSet& trainingSet, const SeqDataSet& validateSet);
        float Test(const SeqDataSet& dataSet, float& loss);
        float Loss(const SeqData& y);
        virtual void Eval(const SeqData& x, std::vector<size_t>& results) = 0;
        virtual bool Load(const std::string& filePath) = 0;
        virtual bool Save(const std::string& filePath) = 0;
        virtual void Update() = 0;        
        virtual void ClearGradient() = 0;
        virtual void ComputeGradient(const SeqData& x, const SeqData& y) = 0;
    protected:
        const Configuration& m_config;
        std::vector<Vector<float>> y_hat;
    };
}

