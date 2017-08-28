#pragma once
#include <string>
#include <vector>
#include "InputData.h"
#include "..\Common\OneHotVector.h"
#include "..\Common\CommonDef.h"
namespace FengML
{
    class DataSet
    {
    public:
        DataSet() = default;
        DataSet(const std::string& filePath);
        virtual bool Load(const std::string& filePath);
        Vector<float>& GetData(size_t index);
        OneHotVector<float> GetTarget(size_t index);
        static int TotalCategory;
    private:
        std::vector<InputData<float>> m_allData;
    };
}