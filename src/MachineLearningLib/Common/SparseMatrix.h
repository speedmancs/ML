#pragma once
namespace FengML
{
    template<class T>
    class SparseMatrix : public Matrix<T>
    {
    public:
        SparseMatrix();
        ~SparseMatrix() override;
    };

    template<class T>
    SparseMatrix<T>::SparseMatrix() {}

    template<class T>
    SparseMatrix<T>::~SparseMatrix() {}
}