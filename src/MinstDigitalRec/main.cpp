#include "..\MachineLearningLib\Data\MnistDataSet.h"
#include "..\MachineLearningLib\Model\LRModel.h"
#include "..\MachineLearningLib\Model\VanillaNNModel.h"
#include <string>
#include <memory>
#include <iostream>
using namespace FengML;
using namespace std;
int main(int argc, char** argv)
{
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
    auto pModel = pConfig->CreateModel();
    pModel->Fit(trainSet, testSet);
    pModel->Save();
}