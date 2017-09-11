#include "SequenceModel.h"
#include "..\Common\Vector.h"
namespace FengML
{
    void SequenceModel::Fit(const SeqDataSet& trainingSet, const SeqDataSet& validateSet)
    {
        float loss;
        std::vector<size_t> results;
        for (int i = 0; i < m_config.train_epoch; i++)
        {
            std::cout << "Epoch:" << i << std::endl;
            for (size_t j = 0; j < trainingSet.Size(); j++)
            {
                const SeqData& x = trainingSet.GetSeqData(j);
                const SeqData& y = trainingSet.GetSeqTarget(j);
                if (j % 100 == 0)
                {
                    std::cout << "\r" << j << " samples scanned";
                }

                if (j % m_config.batchSize == 0)
                {
                    ClearGradient();
                }

                
                Eval(x, results);
                ComputeGradient(x, y);
                if (j % m_config.batchSize == m_config.batchSize - 1 ||
                    j == trainingSet.Size() - 1)
                {
                    Update();
                }
            }

            float accuracy = Test(trainingSet, loss);
            std::cout << std::endl << "In training set, accuracy : " << accuracy << " loss: " << loss << std::endl;
            accuracy = Test(validateSet, loss);
            std::cout << "In validate set, accuracy : " << accuracy << " loss: " << loss << std::endl << std::endl;
        }
    }

    float SequenceModel::Test(const SeqDataSet& dataSet, float& loss)
    {
        size_t total = dataSet.Size();
        loss = 0;
        size_t totalLabels = 0;
        size_t correct = 0;
        std::vector<size_t> results;
        for (int i = 0; i < total; i++)
        {
            Eval(dataSet.GetSeqData(i), results);
            totalLabels += results.size();
            for (int j = 0; j < results.size(); j++)
            {
                if (results[i] == dataSet.GetSeqTarget(i)[j].HotIndex())
                {
                    correct++;
                }
            }

            loss += Loss(dataSet.GetSeqTarget(i));
        }

        return correct / (float)totalLabels;
    }

    float SequenceModel::Loss(const SeqData& y)
    {
        size_t T = y.size();
        float loss = 0;
        for (size_t i = 0; i < T; i++)
        {
            loss += y_hat[i].CrossEntropyError(y[i]);
        }
        return loss;
    }

}