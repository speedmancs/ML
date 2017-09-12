#include "VanillaNNConfiguration.h"
#include "..\Model\VanillaNNModel.h"
#include <cassert>
namespace FengML
{
    bool VanillaNNConfiguration::Load(const std::string& filePath)
    {
        Configuration::Load(filePath);
        
        tinyxml2::XMLDocument doc;
        doc.LoadFile(filePath.c_str());
        
        auto modelSetting = doc.FirstChildElement("Configuration")->FirstChildElement("ModelSetting");
        std::vector<tinyxml2::XMLElement*> hiddenLayers = this->GetAllChildren(modelSetting, "hiddenLayer");

        assert(hiddenLayers.size() > 0);
        this->LayerNumber = 1 + (int)hiddenLayers.size();
        for each (auto p in hiddenLayers)
        {
            int layerSize = this->GetIntAttribute(p, "size");
            this->hiddenLayerSizes.push_back(layerSize);
        }
        return true;
    }

    bool VanillaNNConfiguration::Save(const std::string& filePath)
    {
        return true;
    }

    std::unique_ptr<Model> VanillaNNConfiguration::CreateModel()
    {
        return std::unique_ptr<Model>(new VanillaNNModel(*this));
    }
}