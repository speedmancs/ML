#pragma once
#include "Configuration.h"
#include <vector>
namespace FengML
{
    class VanillaNNConfiguration : public Configuration
    {
    public:
        VanillaNNConfiguration() = default;
        virtual bool Load(const std::string& filePath);
        virtual bool Save(const std::string& filePath);
        
        int LayerNumber;
        std::vector<int> hiddenLayerSizes;
    };
}
