#pragma once
namespace FengML
{
    class OneHotVector
    {
    public:
        OneHotVector(size_t index, size_t len) : m_Len(len), m_index(index) {}
        virtual ~OneHotVector() {}
        size_t Size() const
        {
            return this->m_Len;
        }
        size_t HotIndex() const
        {
            return m_index;
        }

        template<class T>
        friend class Vector;
    private:
        size_t m_index;
        size_t m_Len;
    };
}
