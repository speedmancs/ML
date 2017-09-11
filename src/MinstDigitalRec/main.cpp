#include "..\MachineLearningLib\Data\MnistDataSet.h"
#include "..\MachineLearningLib\Model\LRModel.h"
#include "..\MachineLearningLib\Model\VanillaNNModel.h"
#include <string>
using namespace FengML;
using namespace std;
int main(int argc, char** argv)
{
    std::string trainFile = "C:\\workspace\\github\\mnist\\train-images.idx3-ubyte";
    std::string trainLabelFile = "C:\\workspace\\github\\mnist\\train-labels.idx1-ubyte";
    std::string testFile = "C:\\workspace\\github\\mnist\\t10k-images.idx3-ubyte";
    std::string testLabelFile = "C:\\workspace\\github\\mnist\\t10k-labels.idx1-ubyte";
    std::string dumpTrainFile = "C:\\workspace\\github\\mnist\\train_dump.txt";
    std::string dumpTestFile = "C:\\workspace\\github\\mnist\\test_dump.txt";
    std::string rootFolder = "C:\\workspace\\github\\mnist\\";
    MnistDataSet trainSet(10);
    trainSet.Load(trainFile, trainLabelFile);
    MnistDataSet testSet(10);
    testSet.Load(testFile, testLabelFile);

    string modelType = argv[1];
    if (modelType == "lr")
    {
        Configuration config;
        config.batchSize = 128;
        config.category_number = 10;
        config.feature_number = 28 * 28;
        config.learning_rate = 0.1f;
        config.train_epoch = 200;
        LRModel model(config);
        MnistDataSet subset(trainSet, 1000);
        model.Fit(subset, testSet);
    }
    else if (modelType == "nn")
    {
        //nn rate batchsize hidden epoch 0
        // rate batchsize hidden epoch
        // 0.001 128       50      100
        // 0.001 10        50      100
        // .\MinstDigitalRec.exe nn 0.001 10 50 27 1 no
        // .\MinstDigitalRec.exe nn 0.001 10 50 1 1 vnnModel_start.txt
        VanillaNNConfiguration config;
        config.batchSize = atoi(argv[3]);
        config.category_number = 200;
        config.feature_number = 28 * 28;
        config.learning_rate = (float)atof(argv[2]);
        config.train_epoch = atoi(argv[5]);
        config.LayerNumber = 2;
        config.hiddenLayerSizes = { atoi(argv[4]) };
        VanillaNNModel model(config);
        MnistDataSet subset(trainSet, 1000);
        std::string previousModel = argv[7];
        if (previousModel != "no")
        {
            model.Load(previousModel);
        }
        if (atoi(argv[6]))
        {
            model.Fit(subset, testSet);
        }
        else
        {
            model.Fit(trainSet, testSet);
        }

        model.Save(rootFolder + "vnnModel.txt");
    }
}