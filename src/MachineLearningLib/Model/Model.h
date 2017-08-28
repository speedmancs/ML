#pragma once
#include <string>
#include "..\Data\InputData.h"
namespace FengML
{
    class Model
    {
        virtual void Fit(const std::vector<InputData<float>>) = 0;
        virtual int Eval(const InputData<float>& data) = 0;
        virtual bool Load(const std::string& filePath) = 0;
        virtual bool Save(const std::string& filePath) = 0;
    };
}