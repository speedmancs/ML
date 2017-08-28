#pragma once
namespace FengML
{
    template<class T>
    class SparseVector : public OneHotVector<T>
    {
    public:
        SparseVector();
        ~SparseVector() override;
    };

    template<class T>
    SparseVector<T>::SparseVector()
    {

    }

    template<class T>
    SparseVector<T>::~SparseVector()
    {

    }
}