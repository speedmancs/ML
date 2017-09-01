#pragma once
#include "VectorOpComponent.h"
namespace FengML
{
    template<class T>
    class OneHotVector : public VectorOpComponent<T>
    {
    public:
        OneHotVector(size_t index, size_t len) : m_Len(len), m_index(index) {}
        virtual ~OneHotVector() {}
        void Eval(Vector<T>& output) override;
        void EvalAddTo(Vector<T>& output) override;
        size_t Dim() override
        {
            return this->m_Len;
        }

        template<class U>
        class Vector;
    private:
        size_t m_index;
        size_t m_Len;
    };

    template<class T>
    void OneHotVector<T>::Eval(Vector<T>& output)
    {
        output = *this;
    }

    template<class T>
    void OneHotVector<T>::EvalAddTo(Vector<T>& output)
    {
        output += *this;
    }
}
