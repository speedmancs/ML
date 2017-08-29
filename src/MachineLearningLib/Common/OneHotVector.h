#pragma once
namespace FengML
{
    class OneHotVector
    {
    public:
        OneHotVector(size_t index, size_t len);
        virtual ~OneHotVector();

        template<class T>
        friend class Vector;
    private:
        size_t m_index;
        size_t m_len;
    };
}
