#include "..\MachineLearningLib\Data\SeqDataSet.h"
#include "..\MachineLearningLib\Model\RNNModel.h"
#include "..\MachineLearningLib\Config\RNNConfiguration.h"
#include <string>
using namespace FengML;
using namespace std;

int main(int argc, char** argv)
{
    RNNConfiguration config;
    config.batchSize = 128;
    config.category_number = 0;
    config.feature_number = 0;
    config.learning_rate = 0.01f;
    config.train_epoch = 200;

    RNNModel model(config);
    return 0;
}