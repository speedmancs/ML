#pragma once
#include "DataSet.h"
namespace FengML
{
    class MnistDataSet : public DataSet
    {
    public:
        MnistDataSet() = default;
        MnistDataSet(int _category) : DataSet(_category) {}

        bool Dump(const std::string& filePath);
        virtual bool Load(const std::string& dataFile, const std::string& labelFile) override;
    protected:
        bool LoadData(const std::string& dataFile);
        bool LoadLabels(const std::string& labelFile);
        int row;
        int col;
    };
}
