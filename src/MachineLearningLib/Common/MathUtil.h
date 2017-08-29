#pragma once
#include "Vector.h"
#include <cmath>
#include <algorithm>
namespace FengML
{
    template<class T>
    class MathUtil
    {
    public:
        static void SoftMax(const Vector<T>& a, Vector<T>& result);
        static void Sigmod(const Vector<T>& a, Vector<T>& result);
        static void Tanh(const Vector<T>& a, Vector<T>& result);
        static void Relu(const Vector<T>& a, Vector<T>& result);
    };

    template<class T>
    void MathUtil<T>::SoftMax(const Vector<T>& a, Vector<T>& result)
    {
        result = a;
        result.SoftMax();
    }

    template<class T>
    void MathUtil<T>::Sigmod(const Vector<T>& a, Vector<T>& result)
    {
        result = a;
        result.Sigmod();
    }

    template<class T>
    void MathUtil<T>::Tanh(const Vector<T>& a, Vector<T>& result)
    {
        result = a;
        result.Tanh();
    }

    template<class T>
    void MathUtil<T>::Relu(const Vector<T>& a, Vector<T>& result)
    {
        result = a;
        result.Relu();
    }
}
