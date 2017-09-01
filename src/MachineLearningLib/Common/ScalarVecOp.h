#pragma once
#include "VectorOpComponent.h"
#include <cassert>
namespace FengML
{
    template<class T>
    class ScalarVecOp : public VectorOpComponent<T>
    {
    public:
        ScalarVecOp(T _value, const Vector<T>& _vec) :
            value(_value), vec(_vec)
        {

        }

        void Eval(Vector<T>& output) override;
        void EvalCombine(Vector<T>& output) override;
        size_t Dim() override;
    private:
        T value;
        const Vector<T>& vec;
    };

    template<class T>
    void ScalarVecOp<T>::Dim()
    {
        return component.Dim();
    }

    template<class T>
    void ScalarVecOp<T>::Eval(Vector<T>& output)
    {
        component.Eval(output);
        output *= val;
    }

    template<class T>
    void ScalarVecOp<T>::EvalAddTo(Vector<T>& output)
    {
        output.Add(value, component);
    }
}
