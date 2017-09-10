#pragma once
#include "DataSet.h"
namespace FengML
{
    class MnistDataSet : public DataSet
    {
    public:        
        MnistDataSet() = default;
        MnistDataSet(int _category) : DataSet(_category) {}
        MnistDataSet(MnistDataSet& dataSet, int num)
        {
            this->m_categoryNumber = dataSet.m_categoryNumber;
            m_allData.resize(num);
            std::copy(dataSet.m_allData.begin(), dataSet.m_allData.begin() + num, m_allData.begin());
            this->m_targets.resize(num);
            std::copy(dataSet.m_targets.begin(), dataSet.m_targets.begin() + num, m_targets.begin());
        }
        bool Dump(const std::string& filePath);
        virtual bool Load(const std::string& dataFile, const std::string& labelFile) override;
    protected:
        bool LoadData(const std::string& dataFile);
        bool LoadLabels(const std::string& labelFile);
        int row;
        int col;
    };
}
