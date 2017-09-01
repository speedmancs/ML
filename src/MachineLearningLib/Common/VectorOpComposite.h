#pragma once
#include "VectorOpComponent.h"
#include <cassert>
namespace FengML
{
    enum VectorOp
    {
        VectorAdd = 0,
        VectorSub
    };

    template<class T, VectorOp Op>
    class VectorOpComposite : public VectorOpComponent<T>
    {
    public:
        VectorOpComposite(const VectorOpComponent<T>& _left, const VectorOpComponent<T>& _right) :
            left(_left), right(_right)
        {

        }

        void Eval(Vector<T>& output) override;
        void EvalAdd(Vector<T>& output) override;
        void EvalSub(Vector<T>& output) override;
        size_t Dim() override;
    private:
        VectorOpComponent<T>& left;
        VectorOpComponent<T>& right;
    };

    template<class T, VectorOp Op>
    void VectorOpComposite<T, Op>::Dim()
    {
        size_t dim = left.Dim();
        size_t dim2 = right.Dim();
        assert(dim == dim2);
        return dim;
    }

    template<class T>
    void VectorOpComposite<T, VectorOp::VectorAdd>::Eval(Vector<T>& output)
    {
        left.Eval(output);
        right.EvalAddTo(output);
    }

    template<class T>
    void VectorOpComposite<T>::EvalAddTo(Vector<T>& output)
    {
        left.EvalAddTo(output);
        right.EvalAddTo(output);
    }
}
