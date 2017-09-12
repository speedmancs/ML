#include "..\tinyxml2\tinyxml2.h"
#include "Configuration.h"
#include <cassert>
#include <algorithm>
#include <vector>
#include <iostream>
#include "..\Model\LRModel.h"
#include "VanillaNNConfiguration.h"
#include "..\Common\Utility.h"
namespace FengML
{
    std::string Configuration::GetStringAttribute(tinyxml2::XMLElement* element, const std::string& subElement,
        const std::string& attrName)
    {
        auto pValue = element->FirstChildElement(subElement.c_str())->Attribute(attrName.c_str());
        assert(pValue != NULL);
        return std::string(pValue);
    }

    std::string Configuration::GetStringAttribute(tinyxml2::XMLElement* element, const std::string& attrName)
    {
        auto pValue = element->Attribute(attrName.c_str());
        assert(pValue != NULL);
        return std::string(pValue);
    }

    float Configuration::GetFloatValue(tinyxml2::XMLElement* element, const std::string& subElement)
    {
        float value;
        auto res = element->FirstChildElement(subElement.c_str())->QueryFloatText(&value);
        assert(res == tinyxml2::XML_SUCCESS);
        return value;
    }

    int Configuration::GetIntValue(tinyxml2::XMLElement* element, const std::string& subElement)
    {
        int value;
        auto res = element->FirstChildElement(subElement.c_str())->QueryIntText(&value);
        assert(res == tinyxml2::XML_SUCCESS);
        return value;
    }

    int Configuration::GetIntAttribute(tinyxml2::XMLElement* element, const std::string& attrName)
    {
        int value;
        auto res = element->QueryIntAttribute(attrName.c_str(), &value);
        assert(res == tinyxml2::XML_SUCCESS);
        return value;
    }

    std::vector<tinyxml2::XMLElement*> Configuration::GetAllChildren(tinyxml2::XMLElement* element, const std::string& subElement)
    {
        std::vector<tinyxml2::XMLElement*> children;
        auto child = element->FirstChildElement(subElement.c_str());
        while (child != NULL)
        {
            children.push_back(child);
            child = child->NextSiblingElement(subElement.c_str());
        }

        return children;
    }

    bool Configuration::GetBooleanValue(tinyxml2::XMLElement* element, const std::string& subElement)
    {
        bool value;
        auto res = element->FirstChildElement(subElement.c_str())->QueryBoolText(&value);
        assert(res == tinyxml2::XML_SUCCESS);
        return value;
    }

    bool Configuration::Load(const std::string& filePath)
    {
        tinyxml2::XMLDocument doc;
        doc.LoadFile(filePath.c_str());

        auto dataSetting = doc.FirstChildElement("Configuration")->FirstChildElement("DataSetting");
        auto modelSetting = doc.FirstChildElement("Configuration")->FirstChildElement("ModelSetting");
        
        this->trainingDataPath = GetStringAttribute(dataSetting, "TrainingData", "path");
        this->trainingLabelPath = GetStringAttribute(dataSetting, "TrainingData", "labelFile");
        this->validateDataPath = GetStringAttribute(dataSetting, "ValidateData", "path");
        this->validateLabelPath = GetStringAttribute(dataSetting, "ValidateData", "labelFile");
        this->feature_number = GetIntValue(dataSetting, "FeatureNumber");
        this->category_number = GetIntValue(dataSetting, "CategoryNumber");

        this->batchSize = GetIntValue(modelSetting, "BatchSize");
        this->learning_rate = GetFloatValue(modelSetting, "LearningRate");
        this->train_epoch = GetIntValue(modelSetting, "TrainEpoch");
        auto value = GetStringAttribute(modelSetting, "type");
        Utility::ToLower(value);
        if (value == "lr")
        {
            type = ModelType_LR;
        }
        else if (value == "vanillann")
        {
            type = ModelType_VanillaNN;
        }
        else
        {
            std::cout << type << " is not supported" << std::endl;
            return false;
        }

        this->modelSavePath = GetStringAttribute(modelSetting, "savePath");
        return true;
    }

    bool Configuration::Save(const std::string& filePath)
    {
        return true;
    }

    std::unique_ptr<Model> Configuration::CreateModel()
    {
        return std::unique_ptr<Model>(new LRModel(*this));
    }

    std::unique_ptr<Configuration> Configuration::CreateConfiguration(
        const std::string& filePath)
    {
        Configuration basicConfig;
        basicConfig.Load(filePath);
        std::unique_ptr<Configuration> config = NULL;
        if (basicConfig.type == ModelType_LR)
        {
            config = std::unique_ptr<Configuration>(new Configuration());
        }
        else if (basicConfig.type == ModelType_VanillaNN)
        {
            config = std::unique_ptr<Configuration>(new VanillaNNConfiguration());
        }
        
        assert(config != NULL);
        config->Load(filePath);
        return config;
    }
}