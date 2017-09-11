#include "RNNModel.h"
namespace FengML
{
    RNNModel::RNNModel(const RNNConfiguration& config) :SequenceModel(config),
        m_config(config)
    {
        int H = m_config.hidden;
        int F = m_config.feature_number;
        int C = m_config.category_number;
        U = Matrix<float>(H, F);
        W = Matrix<float>(H, H);
        V = Matrix<float>(C, H);
        bw = Vector<float>(H);
        bv = Vector<float>(C);
        Setup();
    }

    void RNNModel::Setup()
    {
        dW = W;
        dU = U;
        dV = V;
        dbw = bw;
        dbv = bv;
        int H = m_config.hidden;
        previousHiddenLayer.Resize(H);
        previousHiddenLayer = 0;
    }

    void RNNModel::ComputeGradient(const SeqData& x, const SeqData& y)
    {
        size_t T = x.size();
        for (size_t i = 0; i < T; i++)
        {
            (y_diff[i] = y_hat[i]).Sub(y[i]);
        }

        for (size_t i = 0; i < T; i++)
        {
            dbv.Add(y_diff[i]);
            dV.AddMul(y_diff[i], h[i]);
        }
        
        for (int i = 0; i < T; i++)
        {
            delta[i][i].AssignMulTMat(V, y_diff[i])
                .MulScalarVec2Sub(1.0f, h[i]);

            for (int j = i - 1; j >= 0; j--)
            {
                delta[i][j].AssignMulTMat(W, delta[i][j + 1])
                    .MulScalarVec2Sub(1.0f, h[j]);
            }
        }

        for (size_t i = 0; i < T; i++)
        {
            for (size_t j = 0; j <= i; j++)
            {
                dbw.Add(delta[i][j]);
                dW.AddMul(delta[i][j], j > 0 ? h[j - 1] : previousHiddenLayer);
                dU.AddMul(delta[i][j], x[j]);
            }
        }
    }

    void RNNModel::Update()
    {
        dbw.Div((float)m_config.batchSize);
        dbv.Div((float)m_config.batchSize);
        dW.Div((float)m_config.batchSize);
        dU.Div((float)m_config.batchSize);
        dV.Div((float)m_config.batchSize);        
        bw.Sub(m_config.learning_rate, dbw);
        bv.Sub(m_config.learning_rate, dbv);
        W.Sub(m_config.learning_rate, dW);
        U.Sub(m_config.learning_rate, dU);
        V.Sub(m_config.learning_rate, dV);    
    }

    void RNNModel::PreAllocate(size_t T)
    {
        if (h.size() >= T)
            return;

        int H = m_config.hidden;
        int C = m_config.category_number;
        int gap = (int)(T - h.size());
        while (gap--)
        {
            h.emplace_back(H);
            s.emplace_back(H);
            y_hat.emplace_back(C);
            y_diff.emplace_back(C);

            if (delta.size() == 0)
            {
                delta.push_back(std::vector<Vector<float>>());                
            }
            else
            {
                delta.push_back(delta.back());
            }
            delta.back().emplace_back(H);
        }
    }

    void RNNModel::Eval(const SeqData& x, std::vector<size_t>& results)
    {
        size_t T = x.size();
        results.resize(T);
        PreAllocate(T);
        for (size_t i = 0; i < T; i++)
        {
            s[i].AssignMul(U, x[i])
                .AddMul(W, i == 0 ? previousHiddenLayer : h[i - 1])
                .Add(bw);
            (h[i] = s[i]).Tanh();
            y_hat[i].AssignMul(V, h[i]).Add(bv).SoftMax();
            results[i] = y_hat[i].Max().second;
        }
    }

    void RNNModel::ClearGradient()
    {
        W = 0;
        V = 0;
        U = 0;
        bw = 0;
        bv = 0;
    }

    bool RNNModel::Load(const std::string& filePath)
    {
        std::ifstream fin(filePath.c_str());
        std::string description;
        fin >> description;
        fin >> bw >> bv >> W >> U >> V;
        Setup();
        return true;
    }

    bool RNNModel::Save(const std::string& filePath)
    {
        std::ofstream fout(filePath.c_str());
        fout << "RNNModel" << std::endl;
        fout << bw << bv << W << U << V;
        return true;
    }
}