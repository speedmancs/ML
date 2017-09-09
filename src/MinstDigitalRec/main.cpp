#include "..\MachineLearningLib\Data\MnistDataSet.h"
#include "..\MachineLearningLib\Model\LRModel.h"
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
    MnistDataSet trainSet(10);
    trainSet.Load(trainFile, trainLabelFile);
    MnistDataSet testSet(10);
    testSet.Load(testFile, testLabelFile);

    Configuration config;
    config.category_number = 10;
    config.feature_number = 28 * 28;
    config.learning_rate = 0.01f;
    config.train_epoch = 200;
    LRModel model(config);
    model.Fit(trainSet, testSet);
    //float loss;
    //float accuracy = model.Test(testSet, loss);
    //cout << "in test set: accuracy:" << accuracy << " with loss:" << loss << endl;
}