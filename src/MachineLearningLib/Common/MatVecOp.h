#pragma once
#include "VectorOpComponent.h"
#include <cassert>
namespace FengML
{
    template<class T>
    class MatVecOp : public VectorOpComponent<T>
    {
    public:
        ScalarVecOp(const VectorOpComponent& _left, const VectorOpComponent& _right) :
            left(_left), right(_right)
        {

        }

        void Eval(Vector<T>& output) override;
        void EvalAddTo(Vector<T>& output) override;
        size_t Dim() override;
    private:
        T value;
        VectorOpComponent& component;
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
