#include "..\MachineLearningLib\Data\MnistDataSet.h"
#include "..\MachineLearningLib\Model\LRModel.h"
#include "..\MachineLearningLib\Model\VanillaNNModel.h"
#include "..\MachineLearningLib\Layer\ActivationLayer.h"
#include "..\MachineLearningLib\Layer\ConvLayer.h"
#include "..\MachineLearningLib\Layer\PoolingLayer.h"
#include "..\MachineLearningLib\Layer\InputLayer.h"
#include "..\MachineLearningLib\Layer\FlattenLayer.h"
#include "..\MachineLearningLib\Layer\FullConnectLayer.h"
#include "..\MachineLearningLib\Layer\Tensor3DLayer.h"
#include "..\MachineLearningLib\Layer\LayerBase.h"
#include "..\MachineLearningLib\Layer\SoftmaxLayer.h"
#include <string>
#include <memory>
#include <chrono>
#include <iostream>

using namespace FengML;
using namespace std;
typedef shared_ptr<Layer<Tensor3>> Layer3;
typedef shared_ptr<Layer<Tensor1>> Layer1;
typedef shared_ptr<FlattenLayer> FtLayer;
typedef shared_ptr<InputLayer> InLayer;
typedef shared_ptr<SoftmaxLayer> SmLayer;
typedef ActivationLayer<Tensor3, ReLu> ReLu3;
typedef ActivationLayer<Tensor1, ReLu> ReLu1;

void forward(shared_ptr<LayerBase> layer)
{
    while (layer != nullptr)
    {
        layer->forward();
        layer = layer->Next();
    }
}

void backward(LayerBase* layer)
{
    while (layer != nullptr)
    {
        layer->backward();
        layer = layer->Previous();
    }
}
void TestLayer()
{
    auto input = InLayer(new InputLayer(Dim3Type(1, 28, 28)));
    auto softmaxLayer = SmLayer(new SoftmaxLayer());

    input->Add(Layer3(new ConvLayer(6, 5)))
        .Add(Layer3(new ReLu3()))
        .Add(Layer3(new PoolingLayer(2)))
        .Add(Layer3(new ConvLayer(16, 5)))
        .Add(Layer3(new ReLu3()))
        .Add(Layer3(new PoolingLayer(2)))
        .Flatten()
        ->Add(Layer1(new FullConnectLayer(50)))
        .Add(Layer1(new ReLu1()))
        .Add(Layer1(new FullConnectLayer(10)))
        .Add(Layer1(softmaxLayer));

    Matrix<float> m1 = vector<vector<float>>({ { 1, 2 },{ 3, 4 } });
    Matrix<float> m2 = vector<vector<float>>({ { 1, 2 },{ 3, 4 } });
    typename Tensor3::DataType data = { m1, m2 };
    input->SetData(data);
    OneHotVector v;
    softmaxLayer->SetTarget(v);

    forward(input);
    backward(softmaxLayer.get());
}

int main(int argc, char** argv)
{
    TestLayer();
    return 0;
    if (argc < 2)
    {
        cout << "MinstDigitalRec.exe <config file path>" << endl;
        return 0;
    }

    string configPath = argv[1];
    auto pConfig = Configuration::CreateConfiguration(configPath);

    MnistDataSet trainSet(pConfig->category_number);
    trainSet.Load(pConfig->trainingDataPath, pConfig->trainingLabelPath);
    MnistDataSet testSet(pConfig->category_number);
    testSet.Load(pConfig->validateDataPath, pConfig->validateLabelPath);

    auto t1 = std::chrono::high_resolution_clock::now();
    auto pModel = pConfig->CreateModel();
    pModel->Fit(trainSet, testSet);
    pModel->Save();

    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "It took "
        << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() / 1000.0
        << " seconds\n";
}