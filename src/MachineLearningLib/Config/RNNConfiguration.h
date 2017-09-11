#pragma once
#include "Configuration.h"
#include <vector>
namespace FengML
{
    class RNNConfiguration : public Configuration
    {
    public:
        RNNConfiguration() = default;
        virtual bool Load(const std::string& filePath);
        virtual bool Save(const std::string& filePath);

        int hidden; // hidden layer size
        int bptt;
        float clipValue;
    };
}
