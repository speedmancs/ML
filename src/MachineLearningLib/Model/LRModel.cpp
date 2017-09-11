#include "LRModel.h"
#include "boost/random/uniform_01.hpp"
#include <fstream>
namespace FengML
{
    LRModel::LRModel(const Configuration& config): Model(config)
    {
        boost::random::mt19937 generator(123456789);
        b = Vector<float>(m_config.category_number); // initilized to all 0
        W = Matrix<float>(m_config.category_number, config.feature_number);
        W.FanInFanOutRandomize(generator);
        Setup();
    }

    void LRModel::ClearGradient()
    {
        db = 0;
        dW = 0;
    }

    void LRModel::Update()
    {
        db.Div((float)m_config.batchSize);
        dW.Div((float)m_config.batchSize);
        b.Sub(m_config.learning_rate, db);
        W.Sub(m_config.learning_rate, dW);
    }

    void LRModel::ComputeGradient(const Vector<float>& x, const OneHotVector& y)
    {
        (y_diff = y_hat).Sub(y);
        db.Add(y_diff);
        dW.AddMul(y_diff, x);
    }

    size_t LRModel::Eval(const Vector<float>& x)
    {
        // y_hat = softmax(Wx + b);
        y_hat.AssignMul(W, x).Add(b).SoftMax();
        return y_hat.Max().second;
    }

    void LRModel::Setup()
    {
        db = Vector<float>(b.Size());
        dW = Matrix<float>(W.Row(), W.Col());
    }

    bool LRModel::Load(const std::string& filePath)
    {
        std::ifstream fin(filePath.c_str());
        std::string description;
        fin >> description;
        fin >> b >> W;
        Setup();
        return true;
    }

    bool LRModel::Save(const std::string& filePath)
    {
        std::ofstream fout(filePath.c_str());
        fout << "LRModel" << std::endl;
        fout << b << W;
        return true;
    }
}