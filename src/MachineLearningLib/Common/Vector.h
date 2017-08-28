#pragma once
#include <vector>
#include "Matrix.h"
#include <cassert>
namespace FengML
{
    template<class T>
    class Matrix;

    template<class T>
    class Vector
    {
    public:
        Vector();
        Vector(size_t len);
        Vector(const std::vector<T>& _data);
        Vector(const Vector<T>& other);
        Vector(Vector<T>&& other);        
        virtual ~Vector();
        virtual Vector<T> LeftMultiply(const Matrix<T>& W) const;
        Vector& operator = (const Vector<T>& other);
        Vector& operator = (Vector<T>&& other);

        size_t Size() const
        {
            return m_Len;            
        }

        T operator[] (size_t index) const
        {
            assert(index < m_Len);
            return m_data[index];
        }

        T & operator[] (size_t index)
        {
            assert(index < m_Len);
            return m_data[index];
        }

        template<class U>
        friend class OneHotVector;

        friend Vector<T> operator * (const Matrix<T>& W, const Vector<T>& x);

    protected:
        T *m_data;
        size_t m_Len;
    };

    template<class T>
    Vector<T>::Vector() : m_data(nullptr), m_Len(0)
    {
    }

    template<class  T>
    Vector<T>::~Vector()
    {
        if (m_data != nullptr)
        {
            delete[] m_data;
        }
    }

    template<class T>
    Vector<T>::Vector(size_t len) : m_Len(len)
    {
        m_data = new T[len];        
        memset(m_data, 0, sizeof(T) * m_Len);
    }

    template<class T>
    Vector<T>::Vector(const std::vector<T>& _data)
    {
        m_Len = _data.size();
        m_data = nullptr;
        if (m_Len > 0)
        {
            m_data = new T[m_Len];
            std::copy(_data.begin(), _data.end(), m_data);
        }
    }

    template<class T>
    Vector<T>::Vector(const Vector<T>& other)
    {
        m_Len = other.m_Len;
        m_data = new T[m_Len];
        std::copy(other.m_data, other.m_data + m_Len, m_data);
    }

    template<class T>
    Vector<T>::Vector(Vector<T>&& other)
    {
        m_Len = other.m_Len;
        m_data = other.m_data;
        other.m_data = nullptr;
    }

    template<class T>
    Vector<T>& Vector<T>::operator = (const Vector<T>& other)
    {
        if (m_Len != other.m_Len)
        {
            delete[]m_data;
            m_data = new T[other.m_Len];
            m_Len = other.m_Len;
        }

        std::copy(other.m_data, other.m_data + m_Len, m_data);
    }

    template<class T>
    Vector<T>& Vector<T>::operator = (Vector<T>&& other)
    {        
        std::swap(m_Len, other.m_Len);
        std::swap(m_data, other.m_data);
    }

    // return y = Wx
    template<class T>
    Vector<T> operator *(const Matrix<T>& W, const Vector<T>& x)
    {       
        return x.LeftMultiply(W);
    }

    // return Wx
    template<class T>
    Vector<T> Vector<T>::LeftMultiply(const Matrix<T>& W) const
    {        
        assert(m_Len == W.Col());
        size_t res_len = W.Row();
        Vector<T> res(res_len);
        T* res_data = res.m_data;
        T* W_data = W.m_data;
        T* v_data = m_data;
        for (int i = 0; i < res_len; i++, W_data += m_Len)
        {
            for (int j = 0; j < m_Len; j++)
            {
                res_data[i] += W_data[j] * v_data[j];
            }
        }

        return res;
    }
}
