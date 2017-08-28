#pragma once
#include "..\Common\Vector.h"
#include "..\Common\CommonDef.h"
#include "boost\smart_ptr\shared_ptr.hpp"
#include <vector>
namespace FengML
{
    template<class T>
    class InputData
    {
    public:
        InputData(VecPointer& _data, int _target);
        VecPointer data;
        int target;
    };

    template<class T>
    InputData<T>::InputData(VecPointer& _data, int _target):
        data(_data), target(_target)
    {
    }
}