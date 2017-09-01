#pragma once
namespace FengML
{
    template<class T>
    class Vector;

    template<class T>
    class VectorOpComponent
    {
    public:
        VectorOpComponent() = default;
        virtual void Eval(Vector<T>& output) = 0;
        virtual void EvalCombine(Vector<T>& output) = 0;
        virtual size_t Dim() = 0;
    };
}
