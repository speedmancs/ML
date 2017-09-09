#include "LRModel.h"
#include "boost/random/uniform_01.hpp"
namespace FengML
{
    LRModel::LRModel(const Configuration& config):m_config(config)
    {
        b = Vector<float>(m_config.category_number); // initilized to all 0
        W = Matrix<float>(m_config.category_number, config.feature_number);
        W.FanInFanOutRandomize();
        db = Vector<float>(b.Size());
        dW = Matrix<float>(W.Row(), W.Col());
    }

    float LRModel::Test(const DataSet& dataSet, float& loss)
    {
        size_t total = dataSet.Size();
        size_t correct = 0;
        loss = 0;
        for (int i = 0; i < total; i++)
        {
            auto predicted = Eval(dataSet.GetData(i));            
            if (predicted == dataSet.GetTarget(i).HotIndex())
            {
                correct++;
            }

            loss += y_hat.CrossEntropyError(dataSet.GetTarget(i));
        }

        return correct / (float)total;
    }

    void LRModel::Fit(const Vector<float>& x, const OneHotVector& y)
    {
        // Calculate db, dW
        size_t pred = Eval(x);
        (db = y_hat).Sub(y);
        dW.AssignMul(db, x);
        b.Sub(m_config.learning_rate, db);
        W.Sub(m_config.learning_rate, dW);
    }

    // Use SGD
    //
    void LRModel::Fit(const DataSet& trainingSet, const DataSet& validateSet)
    {
        float loss;
        for (int i = 0; i < m_config.train_epoch; i++)
        {
            std::cout << "Epoch:" << i << std::endl;
            for (size_t j = 0; j < trainingSet.Size(); j++)
            {
                if (j % 100 == 0)
                {
                    std::cout <<"\r" << j << " samples scanned";
                }
                Fit(trainingSet.GetData(j), trainingSet.GetTarget(j));
            }
            float accuracy = Test(trainingSet, loss);
            std::cout << std::endl << "In training set, accuracy : " << accuracy << " loss: " << loss << std::endl;
            accuracy = Test(validateSet, loss);
            std::cout << std::endl << "In validate set, accuracy : " << accuracy << " loss: " << loss << std::endl;
        }
    }

    size_t LRModel::Eval(const Vector<float>& x)
    {
        // y_hat = softmax(Wx + b);
        y_hat.AssignMul(W, x).Add(b).SoftMax();     
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