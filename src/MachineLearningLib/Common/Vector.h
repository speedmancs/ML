#pragma once
#include <vector>
#include <fstream>
#include <algorithm>
#include "Matrix.h"
#include "OneHotVector.h"
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
 
        template<class U>
        Vector(U* data, size_t len)
        {
            m_Len = len;
            m_data = new T[m_Len];
            for (int i = 0; i < m_Len; i++)
            {
                m_data[i] = (T)data[i];
            }
        }

        void Print(std::ofstream& fout, int col = 0)
        {
            if (col == 0)
            {
                for (int i = 0; i < m_Len; i++)
                {
                    fout << m_data[i] << " ";
                }
                fout << endl;
                return;
            }

            for (int i = 0; i < m_Len; i++)
            {
                fout << m_data[i] << " ";
                if (i % col == col - 1)
                    fout << endl;
            }
        }
        Vector<T>& Div(T value)
        {
            for (int i = 0; i < m_Len; i++)
            {
                m_data[i] /= value;
            }
            return *this;
        }

        Vector(const std::vector<T>& _data);
        Vector(const Vector<T>& other);
        Vector(Vector<T>&& other);
        virtual ~Vector();
        Vector<T>& operator = (T value)
        {
            for (int i = 0; i < m_Len; i++)
                m_data[i] = value;
            return *this;
        }

        Vector<T>& operator = (const Vector<T>& other);
        Vector<T>& operator = (Vector<T>&& other);

        Vector<T>& AddMul(const Matrix<T>& m, const Vector<T>& v)
        {
            T * mdata = m.m_data;
            for (int i = 0; i < m_Len; i++)
            {
                for (int j = 0; j < v.m_Len; j++, mdata ++)
                {
                    m_data[i] += *mdata + v.m_data[j];
                }
            }
            return *this;
        }

        void Resize(size_t len);
        Vector<T>& AddMul(T scale, const Vector<T>& other);
        Vector<T>& Add(const Vector<T>& other)
        {
            *this += other;
            return *this;
        }

        Vector<T>& Sub(const OneHotVector& other)
        {
            this->m_data[other.m_index] --;
            return *this;
        }

        Vector<T>& Sub(const Vector<T>& other)
        {
            *this -= other;
            return *this;
        }
        
        T CrossEntropyError(const OneHotVector& target)
        {
            T value = m_data[target.m_index];
            return -log(value);
        }

        Vector<T>& Sub(T scale, const Vector<T>& other)
        {
            for (int i = 0; i < m_Len; i++)
            {
                m_data[i] -= scale * other.m_data[i];
            }

            return *this;
        }

        Vector<T>& Mul(const Vector<T>& other)
        {
            for (int i = 0; i < m_Len; i++)
                m_data[i] = m_data[i] * other.m_data[i];
            return *this;
        }

        Vector<T>& MulScalarVecSub(T value, const Vector<T>& other)
        {
            for (int i = 0; i < m_Len; i++)
                m_data[i] *= value - other.m_data[i];
            return *this;
        }

        Vector<T>& MulScalarVec2Sub(T value, const Vector<T>& other)
        {
            for (int i = 0; i < m_Len; i++)
                m_data[i] *= value - other.m_data[i] * other.m_data[i];
            return *this;
        }

        // W * v
        Vector<T>& AssignMul(const Matrix<T>& W, const Vector<T>& v);

        Vector<T>& AssignMul(const Matrix<T>& W, const OneHotVector& v)
        {
            Resize(W.row);
            T* wdata = W.m_data + v.m_index;
            for (int i = 0; i < m_Len; i++, wdata += W.col)
            {
                m_data[i] = *wdata;
            }
            return *this;
        }

        // W' * v
        Vector<T>& AssignMulTMat(const Matrix<T>& W, const Vector<T>& v);
        Vector<T>& operator += (const Vector<T>& other);
        Vector<T>& operator -= (const Vector<T>& other);
        Vector<T>& operator += (const OneHotVector& other);
        Vector<T>& operator -= (const OneHotVector& other);
        Vector<T>& operator = (const OneHotVector& other);
        Vector<T>& operator *= (T val);
        Vector<T>& SoftMax();
        Vector<T>& Sigmod();
        Vector<T>& Tanh();
        Vector<T>& Relu();

        size_t Size()
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
        template<class U>
        friend std::ofstream& operator << (std::ofstream& fout, const Vector<U>& v);
        template<class U>
        friend std::ifstream& operator >> (std::ifstream& fin, Vector<U>& v);
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
        return *this;
    }

    template<class T>
    Vector<T>& Vector<T>::operator = (const OneHotVector& other)
    {
        if (m_Len != other.m_Len)
        {
            Resize(other.m_Len);
        }

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
            memset(m_data, 0, sizeof(T) * m_Len);
        }
    }

    template<class T>
    Vector<T>& Vector<T>::AddMul(T scale, const Vector<T>& other)
    {
        for (size_t i = 0; i < m_Len; i++)
        {
            m_data[i] += scale * other.m_data[i];
        }

        return *this;
    }

    //template<class T>
    //Vector<T>& Vector<T>::AssignMulTMat(const Matrix<T>& W, const Vector<T>& v)
    //{
    //    Resize(W.col);
    //    *this = 0;
    //    for (size_t i = 0; i < m_Len; i++)
    //    {
    //        for (int j = 0; j < W.row; j++)
    //        {
    //            m_data[i] += W(j, i) * v[j];
    //        }
    //    }
    //    return *this;
    //}

    //template<class T>
    //Vector<T>& Vector<T>::AssignMul(const Matrix<T>& W, const Vector<T>& v)
    //{
    //    Resize(W.Row());
    //    for (size_t i = 0; i < m_Len; i++)
    //    {
    //        T sum = 0;
    //        for (size_t j = 0; j < W.Col(); j++)
    //        {
    //            sum += W(i, j) * v[j];
    //        }
    //        m_data[i] = sum;
    //    }
    //    return *this;
    //}

    template<class T>
    Vector<T>& Vector<T>::AssignMul(const Matrix<T>& W, const Vector<T>& v)
    {
        Resize(W.row);
        T* wdata = W.m_data;
        T* data = m_data;
        for (size_t i = 0; i < m_Len; i++, data++)
        {
            T* vdata = v.m_data;
            T sum = 0;
            for (size_t j = 0; j < W.col; j++, vdata++, wdata++)
            {
                sum += *wdata * *vdata;
            }
            *data = sum;
        }
        return *this;
    }

    template<class T>
    Vector<T>& Vector<T>::AssignMulTMat(const Matrix<T>& W, const Vector<T>& v)
    {
        Resize(W.col);
        *this = 0;
        T* wdata = W.m_data;
        T* data = m_data;
        T* vdata = v.m_data;
        for (size_t i = 0; i < W.row; i++, vdata++)
        {
            for (size_t j = 0; j < W.col; j++, wdata++)
            {
                data[j] += *wdata * *vdata;
            }
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
    Vector<T>& Vector<T>::operator += (const OneHotVector& other)
    {
        this->m_data[other.m_index] ++;
        return *this;
    }

    template<class T>
    Vector<T>& Vector<T>::operator -= (const OneHotVector& other)
    {
        this->m_data[other.m_index] --;
        return *this;
    }

    template<class T>
    Vector<T>& Vector<T>::SoftMax()
    {
        T m = *std::max_element(m_data, m_data + m_Len);
        float sum = 0;
        for (size_t i = 0; i < m_Len; i++)
        {
            m_data[i] = exp(m_data[i] - m);
            sum += m_data[i];
        }

        sum = 1.0f / sum;

        for (size_t i = 0; i < m_Len; i++)
        {
            m_data[i] *= sum;
        }

        return *this;
    }

    template<class T>
    Vector<T>& Vector<T>::Sigmod()
    {
        for (size_t i = 0; i < m_Len; i++)
        {
            m_data[i] = static_cast<T>(1.0 / (1 + exp(-m_data[i])));
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

    template<class T>
    std::ofstream& operator << (std::ofstream& fout, const Vector<T>& v)
    {
        fout << v.m_Len << std::endl;
        for (int i = 0; i < v.m_Len; i++)
            fout << v.m_data[i] << " ";
        fout << std::endl;
        return fout;
    }

    template<class T>
    std::ifstream& operator >> (std::ifstream& fin, Vector<T>& v)
    {
        fin >> v.m_Len;
        v.Resize(v.m_Len);
        for (int i = 0; i < v.m_Len; i++)
            fin >> v.m_data[i];
        return fin;
    }
}
