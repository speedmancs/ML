#include "VanillaNNModel.h"
namespace FengML
{
    VanillaNNModel::VanillaNNModel(const VanillaNNConfiguration& config)
        :Model(config), m_config(config)
    {
        int L = m_config.LayerNumber;
        biases.resize(L);
        weights.resize(L);
        d_biases.resize(L);
        d_weights.resize(L);
        for (int i = 0; i < L - 1; i++)
        {
            int hidden = m_config.hiddenLayerSizes[i];
            biases[i] = Vector<float>(hidden);
            d_biases[i] = biases[i];
            if (i == 0)
            {
                weights[i] = Matrix<float>(hidden, m_config.feature_number);
            }
            else
            {
                weights[i] = Matrix<float>(hidden, m_config.hiddenLayerSizes[i-1]);
            }
            d_weights[i] = weights[i];
        }

        biases[L - 1] = Vector<float>(m_config.category_number);
        d_biases[L - 1] = biases[L - 1];
        weights[L - 1] = Matrix<float>(m_config.category_number, m_config.hiddenLayerSizes.back());
        d_weights[L - 1] = weights[L - 1];

        boost::random::mt19937 generator(123456789);
        for (int i = 0; i < L; i++)
        {
            weights[i].FanInFanOutRandomize(generator);
        }

        layers.resize(L);
        activate_layers.resize(L);
        gradient_layers.resize(L);
        for (int i = 0; i < L; i++)
        {
            layers[i] = biases[i];
            activate_layers[i] = biases[i];
            gradient_layers[i] = biases[i];
        }
    }

    void VanillaNNModel::ComputeGradient(const Vector<float>& x, const OneHotVector& y)
    {
        int L = m_config.LayerNumber;
        Vector<float>& y_hat = activate_layers[L - 1];
        (gradient_layers[L - 1] = y_hat).Sub(y);
        for (int i = L - 2; i >= 0; i--)
        {
            gradient_layers[i].AssignMulTMat(weights[i + 1], gradient_layers[i + 1]);
            gradient_layers[i].Mul(activate_layers[i])
                .MulScalarVecSub(1.0f, activate_layers[i]);
        }

        for (int i = 0; i < L; i++)
        {
            d_biases[i] = gradient_layers[i];
            if (i > 0)
            {
                d_weights[i].AssignMul(gradient_layers[i], activate_layers[i - 1]);
            }
            else
            {
                d_weights[i].AssignMul(gradient_layers[i], x);
            }
        }
    }

    void VanillaNNModel::Update()
    {
        int L = m_config.LayerNumber;
        for (int i = 0; i < L; i++)
        {
            d_biases[i].Div((float)m_config.batchSize);
            d_weights[i].Div((float)m_config.batchSize);
            biases[i].Sub(m_config.learning_rate, d_biases[i]);
            weights[i].Sub(m_config.learning_rate, d_weights[i]);
        }
    }

    size_t VanillaNNModel::Eval(const Vector<float>& data)
    {
        int L = m_config.LayerNumber;
        Vector<float>& y_hat = activate_layers[L - 1];
        for (int i = 0; i < L; i++)
        {
            if (i == 0)
            {
                layers[i].AssignMul(weights[i], data).Add(biases[i]);
            }
            else
            {
                layers[i].AssignMul(weights[i], activate_layers[i - 1]).Add(biases[i]);
            }
            
            if (i != L - 1)
            {
                (activate_layers[i] = layers[i]).Sigmod();
            }
            else
            {
                (activate_layers[i] = layers[i]).SoftMax();
            }
        }

        return y_hat.Max().second;
    }

    float VanillaNNModel::Loss(const OneHotVector& y)
    {
        int L = m_config.LayerNumber;
        Vector<float>& y_hat = activate_layers[L - 1];
        return y_hat.CrossEntropyError(y);
    }

    void VanillaNNModel::ClearGradient()
    {
        for (int i = 0; i < m_config.LayerNumber; i++)
        {
            d_biases[i] = 0;
            d_weights[i] = 0;
        }
    }

    bool VanillaNNModel::Load(const std::string& filePath)
    {
        return true;
    }

    bool VanillaNNModel::Save(const std::string& filePath)
    {
        return true;
    }
}