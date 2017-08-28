#pragma once
#include <vector>
namespace FengML
{
    template<class T>
    class Matrix
    {
    public:
        Matrix();
        Matrix(size_t _row, size_t _col);
        Matrix(const std::vector<std::vector<T>>& _data);
        Matrix(const Matrix<T>& other);
        Matrix(Matrix<T>&& other);
        ~Matrix();
        Matrix& operator = (const Matrix<T>& other);
        Matrix& operator = (Matrix<T>&& other);

        std::pair<size_t, size_t> Size() const
        {
            return std::make_pair(row, col);
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

        template<class U>
        friend class Vector;

        template<class U>
        friend class OneHotVector;

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
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator = (Matrix<T>&& other)
    {
        std::swap(row, other.row);
        std::swap(col, other.col);
        std::swap(m_data, other.m_data);
    }
}
