#pragma once
#include "Vector.h"
#include "Matrix.h"
namespace FengML
{
    template<class T>
    class Matrix;

    template<class T>
    class OneHotVector : public Vector<T>
    {
    public:
        OneHotVector(size_t index, size_t len);
        ~OneHotVector() override;
        Vector<T> LeftMultiply(const Matrix<T>& W) const override;

    private:
        size_t m_index;
    };

    template<class T>
    OneHotVector<T>::OneHotVector(size_t index, size_t len): Vector(),
        m_index(index)
    {
        this->m_Len = len;
    }
    
    template<class T>
    OneHotVector<T>::~OneHotVector()
    {
    }

    template<class T>
    Vector<T> OneHotVector<T>::LeftMultiply(const Matrix<T>& W) const
    {
        assert(m_Len == W.Col());
        size_t res_len = W.Row();
        Vector<T> res(res_len);
        T* res_data = res.m_data;
        T* W_data = W.m_data + m_index;
        for (int i = 0; i < res_len; i++, W_data += m_Len)
        {
            res_data[i] = *W_data;
        }

        return res;
    }
}
