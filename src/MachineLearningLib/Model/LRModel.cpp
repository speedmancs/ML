#include "LRModel.h"
#include "boost/random/uniform_01.hpp"
namespace FengML
{
    LRModel::LRModel(const Configuration& config):m_config(config)
    {
        b = Vector<float>(m_config.category_number); // initilized to all 0
        W = Matrix<float>(config.feature_number, m_config.category_number);
        db = Vector<float>(b.Size());
        dW = Matrix<float>(W.Row(), W.Col());
    }

    void LRModel::Fit(const Vector<float>& x, const OneHotVector& y)
    {
        // Calculate db, dW
        size_t pred = Eval(x);
        (db = y_hat).Sub(y);
        dW.AssignMul(db, x);
        b.Add(-m_config.learning_rate, db);
        W.Add(-m_config.learning_rate, dW);
    }

    // Use SGD
    //
    void LRModel::Fit(const DataSet& trainingSet)
    {
        for (int i = 0; i < m_config.train_epoch; i++)
        {
            for (size_t j = 0; j < trainingSet.Size(); j++)
            {
                Fit(trainingSet.GetData(j), trainingSet.GetTarget(j));
            }
        }
    }

    size_t LRModel::Eval(const Vector<float>& data)
    {
        // y_hat = softmax(Wx + b);
        y_hat.AssignMul(W, data).Add(b).SoftMax();     
        return y_hat.Max().second;
        return 0;
    }

    bool LRModel::Load(const std::string& filePath)
    {
        return true;
    }

    bool LRModel::Save(const std::string& filePath)
    {
        return true;
    }

}