#pragma once
#include <string>
namespace FengML
{
    class Configuration
    {
    public:
        Configuration() = default;
        virtual bool Load(const std::string& filePath);
        virtual bool Save(const std::string& filePath);

        size_t train_epoch;
        float learning_rate;
        int category_number;
        int feature_number;
    };
}
