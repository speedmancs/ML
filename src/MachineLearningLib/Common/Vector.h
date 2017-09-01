#pragma once
#include <vector>
#include "Matrix.h"
#include "OneHotVector.h"
#include "VectorOpComponent.h"
#include <cassert>
namespace FengML
{
    template<class T>
    class Matrix;

    template<class T>
    class Vector : public VectorOpComponent<T>
    {
    public:
        Vector();
        Vector(size_t len);
        Vector(const std::vector<T>& _data);
        Vector(const Vector<T>& other);
        Vector(Vector<T>&& other);
        virtual ~Vector();
        Vector& operator = (const Vector<T>& other);
        Vector& operator = (Vector<T>&& other);

        void Resize(size_t len);
        Vector<T>& Add(T scale, const Vector<T>& other);
        Vector<T>& AssignMul(const Matrix<T>& W, const Vector<T>& v);
        Vector<T>& operator += (const Vector<T>& other);
        Vector<T>& operator -= (const Vector<T>& other);
        Vector<T>& operator += (const OneHotVector<T>& other);
        Vector<T>& operator -= (const OneHotVector<T>& other);
        Vector<T>& operator = (const OneHotVector<T>& other);
        Vector<T>& operator *= (T val);
        Vector<T>& SoftMax();
        Vector<T>& Sigmod();
        Vector<T>& Tanh();
        Vector<T>& Relu();

        void Eval(Vector<T>& output) override;
        void EvalAddTo(Vector<T>& output) override;
        size_t Dim() override
        {
            return this->m_Len;
        }

        std::pair<T, size_t> Max() const;
        T * Data()
        {
            return m_data;
        }

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

    protected:
        T *m_data;
        size_t m_Len;
    };

    template<class T>
    void Vector<T>::Eval(Vector<T>& output)
    {
        output = *this;
    }

    template<class T>
    void Vector<T>::EvalCombine(Vector<T>& output)
    {
        output += *this;
    }

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
        return *this;
    }

    template<class T>
    Vector<T>& Vector<T>::operator -= (const OneHotVector<T>& other)
    {
        if (m_Len != other.m_Len)
        {
            delete[]m_data;
            m_data = new T[other.m_Len];
            m_Len = other.m_Len;
        }

        memset(m_data, 0, sizeof(T) * m_Len);
        m_data[other.m_index] = 1;
        return *this;
    }

    template<class T>
    Vector<T>& Vector<T>::operator = (Vector<T>&& other)
    {        
        std::swap(m_Len, other.m_Len);
        std::swap(m_data, other.m_data);
        return *this;
    }

    template<class T>
    void Vector<T>::Resize(size_t len)
    {
        if (m_Len != len)
        {
            m_Len = len;
            delete[]m_data;
            m_data = new T[m_Len];
        }
    }

    template<class T>
    Vector<T>& Vector<T>::Add(T scale, const Vector<T>& other)
    {
        for (size_t i = 0; i < m_Len; i++)
        {
            m_data[i] += scale * other.m_data[i];
        }

        return *this;
    }

    template<class T>
    Vector<T>& Vector<T>::AssignMul(const Matrix<T>& W, const Vector<T>& v)
    {
        Resize(W.Row());
        for (size_t i = 0; i < m_Len; i++)
        {
            T sum = 0;
            for (size_t j = 0; j < W.Col(); j++)
            {
                sum += W(i, j) * v[j];
            }
            m_data[i] = sum;
        }
        return *this;
    }

    template<class T>
    Vector<T>& Vector<T>::operator += (const Vector<T>& other)
    {
        for (size_t i = 0; i < m_Len; i++)
        {
            m_data[i] += other[i];
        }

        return *this;
    }

    template<class T>
    Vector<T>& Vector<T>::operator -= (const Vector<T>& other)
    {
        for (size_t i = 0; i < m_Len; i++)
        {
            m_data[i] -= other[i];
        }

        return *this;
    }

    template<class T>
    Vector<T>& Vector<T>::operator *= (T val)
    {
        for (size_t i = 0; i < m_Len; i++)
        {
            m_data[i] *= val;
        }

        return *this;
    }

    template<class T>
    Vector<T>& Vector<T>::operator += (const OneHotVector<T>& other)
    {
        this->m_data[other.m_index] ++;
        return *this;
    }

    template<class T>
    Vector<T>& Vector<T>::operator -= (const OneHotVector<T>& other)
    {
        this->m_data[other.m_index] --;
        return *this;
    }

    template<class T>
    Vector<T>& Vector<T>::SoftMax()
    {
        T minValue = *std::min(m_data, m_data + m_Len);
        float sum = 0;
        for (size_t i = 0; i < m_Len; i++)
        {
            m_data[i] = exp(m_data[i] - minValue);
            sum += m_data[i];
        }

        for (size_t i = 0; i < m_Len; i++)
        {
            m_data[i] /= sum;
        }

        return *this;
    }

    template<class T>
    Vector<T>& Vector<T>::Sigmod()
    {
        for (size_t i = 0; i < m_Len; i++)
        {
            m_data[i] = static_cast<T>(1.0 / 1 + exp(-m_data[i]));
        }

        return *this;
    }

    template<class T>
    Vector<T>& Vector<T>::Tanh()
    {
        for (size_t i = 0; i < m_Len; i++)
        {
            float value1 = exp(m_data[i]);
            float value2 = exp(-m_data[i]);
            m_data[i] = static_cast<T>((value1 - value2) / (value1 + value2));
        }

        return *this;
    }

    template<class T>
    Vector<T>& Vector<T>::Relu()
    {
        for (size_t i = 0; i < m_Len; i++)
        {
            if (m_data[i] < 0)
            {
                m_data[i] = 0;
            }
        }

        return *this;
    }

    template<class T>
    std::pair<T, size_t> Vector<T>::Max() const
    {
        auto res = std::make_pair<T, size_t>(0, -1);
        if (m_Len > 0)
        {
            T* p = std::max_element(m_data, m_data + m_Len);
            res.first = *p;
            res.second = p - m_data;
        }

        return res;
    }
}
