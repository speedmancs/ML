#pragma once
#include "Layer.h"
#include "Tensor3DLayer.h"
#include <iostream>
namespace FengML
{
    class InputLayer : public Tensor3DLayer
    {
    public:
        InputLayer(Dim3Type dim) : Tensor3DLayer(dim) {}
    };
}
