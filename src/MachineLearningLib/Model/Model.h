#pragma once
#include <string>
#include "..\Data\DataSet.h"
#include "..\Config\Configuration.h"
namespace FengML
{
    class Model
    {
        virtual float Test(const DataSet& dataSet, float& loss) = 0;
        virtual void Fit(const DataSet& trainingSet, const DataSet& validateSet) = 0;
        virtual size_t Eval(const Vector<float>& data) = 0;
        virtual bool Load(const std::string& filePath) = 0;
        virtual bool Save(const std::string& filePath) = 0;
    };
}