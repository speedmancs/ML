#pragma once
#include "..\tinyxml2\tinyxml2.h"
#include <string>
#include <vector>
#include <memory>
namespace FengML
{
    enum ModelType
    {
        ModelType_LR,
        ModelType_VanillaNN
    };
    class Model;
    class Configuration
    {
    public:
        Configuration() = default;
        static std::unique_ptr<Configuration> CreateConfiguration(const std::string& filePath);
        virtual bool Load(const std::string& filePath);
        virtual bool Save(const std::string& filePath);
        virtual std::unique_ptr<Model> CreateModel();
        size_t train_epoch;
        float learning_rate;
        int category_number;
        int feature_number;
        int batchSize;

        std::string trainingDataPath;
        std::string trainingLabelPath;
        std::string validateDataPath;
        std::string validateLabelPath;
        std::string modelSavePath;
        ModelType type;

    protected:
        static int GetIntAttribute(tinyxml2::XMLElement* element, const std::string& attrName);
        static std::string GetStringAttribute(tinyxml2::XMLElement* element, const std::string& attrName);
        static std::string GetStringAttribute(tinyxml2::XMLElement* element, const std::string& subElement,
            const std::string& attrName);
        static float GetFloatValue(tinyxml2::XMLElement* element, const std::string& subElement);
        static int GetIntValue(tinyxml2::XMLElement* element, const std::string& subElement);
        static bool GetBooleanValue(tinyxml2::XMLElement* element, const std::string& subElement);
        static std::vector<tinyxml2::XMLElement*> GetAllChildren(tinyxml2::XMLElement* element, const std::string& subElement);
    };
}
