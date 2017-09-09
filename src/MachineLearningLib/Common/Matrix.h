#pragma once
#include <vector>
#include "boost/random/uniform_01.hpp"
#include "boost/random/mersenne_twister.hpp"
#include <ctime>
#include <cmath>
#include <cassert>
namespace FengML
{
    template<class T>
    class Vector;

    template<class T>
    class Matrix
    {
    public:
        template<class U>
        friend class Vector;

        Matrix();
        Matrix(size_t _row, size_t _col);
        Matrix(const std::vector<std::vector<T>>& _data);
        Matrix(const Matrix<T>& other);
        Matrix(Matrix<T>&& other);
        virtual ~Matrix();
        void FanInFanOutRandomize();
        Matrix& operator = (const Matrix<T>& other);
        Matrix& operator = (Matrix<T>&& other);
        
        std::pair<size_t, size_t> Size() const
        {
            return std::make_pair(row, col);
        }

        void Resize(size_t _row, size_t _col)
        {
            if (row != _row || col != _col)
            {
                row = _row;
                col = _col;
                delete[] m_data;
                m_data = new T[row * col];
                memset(m_data, 0, sizeof(T) * row * col);
            }
        }

        size_t Row() const
        {
            return row;
        }

        size_t Col() const
        {
            return col;
        }

        T operator() (size_t _row, size_t _col) const
        {
            assert(_row < row && _col < col);
            return m_data[_row * col + _col];
        }

        T& operator() (size_t _row, size_t _col)
        {
            assert(_row < row && _col < col);
            return m_data[_row * col + _col];
        }

        Matrix<T>& Add(T scale, const Matrix<T>& other);
        Matrix<T>& Sub(T scale, const Matrix<T>& other)
        {
            return Add(-scale, other);
        }
        Matrix<T>& AssignMul(const Vector<T>& a, const Vector<T>& b);

    private:
        T *m_data;
        size_t row;
        size_t col;
    };

    template<class T>
    Matrix<T>::Matrix() : m_data(nullptr), row(0), col(0)
    {
    }

    template<class  T>
    Matrix<T>::~Matrix()
    {
        if (m_data != nullptr)
        {
            delete[] m_data;
        }
    }

    template<class T>
    Matrix<T>::Matrix(size_t _row, size_t _col) : row(_row), col(_col)
    {
        m_data = new T[_row * _col];
        memset(m_data, 0, sizeof(T) * row * col);
    }

    template<class T>
    Matrix<T>::Matrix(const std::vector<std::vector<T>>& _data)
    {
        m_Len = 0;
        m_data = nullptr;
        row = col = 0;
        if (_data.size() > 0 && _data[0].size() > 0)
        {
            row = _data.size();
            col = _data[0].size();
            m_data = new T[row * col];
            int start = 0;
            for each (auto& vec in _data)
            {
                std::copy(vec.begin(), vec.end(), m_data + start);
                start += col;
            }
        }
    }

    template<class T>
    Matrix<T>::Matrix(const Matrix<T>& other)
    {
        row = other.row;
        col = other.col;
        m_data = new T[row * col];
        std::copy(other.m_data, other.m_data + row * col, m_data);
    }

    template<class T>
    Matrix<T>::Matrix(Matrix<T>&& other)
    {
        row = other.row;
        col = other.col;
        m_data = other.m_data;
        other.m_data = nullptr;
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator = (const Matrix<T>& other)
    {
        if (row != other.row || col != other.col)
        {
            delete[]m_data;
            row = other.row;
            col = other.col;
            m_data = new T[row * col];
        }

        std::copy(other.m_data, other.m_data + row * col, m_data);
        return *this;
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator = (Matrix<T>&& other)
    {
        std::swap(row, other.row);
        std::swap(col, other.col);
        std::swap(m_data, other.m_data);
        return *this;
    }
    
    template<class T>
    void Matrix<T>::FanInFanOutRandomize()
    {
//        boost::random::mt19937 generator((uint32_t)time(0));
        boost::random::mt19937 generator(123456789);
        boost::uniform_01<boost::random::mt19937> dist(generator);

        T r = static_cast<T>(4 * sqrt(6.0 / (row + col)));
        size_t len = row * col;
        for (size_t i = 0; i < len; i++)
        {
            m_data[i] = static_cast<T>((dist() * 2 - 1) * r);
        }
    }

    template<class T>
    Matrix<T>& Matrix<T>::Add(T scale, const Matrix<T>& other)
    {
        auto len = this->col * this->row;
        for (size_t i = 0; i < len; i++)
        {
            m_data[i] += scale * other.m_data[i];
        }

        return *this;
    }

    // return a * b'
    template<class T>
    Matrix<T>& Matrix<T>::AssignMul(const Vector<T>& a, const Vector<T>& b)
    {
        Resize(a.Size(), b.Size());
        for (size_t i = 0; i < a.Size(); i++)
        {
            for (size_t j = 0; j < b.Size(); j++)
            {
                (*this)(i, j) = a[i] * b[j];
            }
        }

        return *this;
    }
}
