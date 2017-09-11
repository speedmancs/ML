#include "Model.h"
namespace FengML
{
    float Model::Loss(const OneHotVector& y)
    {
        return y_hat.CrossEntropyError(y);
    }

    // Use SGD
    //
    void Model::Fit(const DataSet& trainingSet, const DataSet& validateSet)
    {
        float loss;
        for (int i = 0; i < m_config.train_epoch; i++)
        {
            std::cout << "Epoch:" << i << std::endl;
            for (size_t j = 0; j < trainingSet.Size(); j++)
            {
                if (j % 100 == 0)
                {
                    std::cout << "\r" << j << " samples scanned";
                }

                if (j % m_config.batchSize == 0)
                {
                    ClearGradient();
                }

                size_t pred = Eval(trainingSet.GetData(j));
                ComputeGradient(trainingSet.GetData(j), trainingSet.GetTarget(j));
                if (j % m_config.batchSize == m_config.batchSize - 1 ||
                    j == trainingSet.Size() - 1)
                {
                    Update();
                    //Save("temp.txt");
                }
            }
            float accuracy = Test(trainingSet, loss);
            std::cout << std::endl << "In training set, accuracy : " << accuracy << " loss: " << loss << std::endl;
            accuracy = Test(validateSet, loss);
            std::cout << "In validate set, accuracy : " << accuracy << " loss: " << loss << std::endl << std::endl;
        }
    }

    float Model::Test(const DataSet& dataSet, float& loss)
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

            loss += Loss(dataSet.GetTarget(i));
        }

        return correct / (float)total;
    }
}
