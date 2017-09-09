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

    void LRModel::Update()
    {
        db.Div((float)m_config.batchSize);
        dW.Div((float)m_config.batchSize);
        b.Sub(m_config.learning_rate, db);
        W.Sub(m_config.learning_rate, dW);
    }

    void LRModel::ComputeGradient(const Vector<float>& x, const OneHotVector& y)
    {
        // Calculate db, dW
        size_t pred = Eval(x);
        (y_diff = y_hat).Sub(y);
        db.Add(y_diff);
        dW.AddMul(y_diff, x);
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

                if (j % m_config.batchSize == 0)
                {
                    db = 0;
                    dW = 0;
                }

                ComputeGradient(trainingSet.GetData(j), trainingSet.GetTarget(j));

                if (j % m_config.batchSize == m_config.batchSize - 1 ||
                    j == trainingSet.Size() - 1)
                {
                    Update();
                }
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