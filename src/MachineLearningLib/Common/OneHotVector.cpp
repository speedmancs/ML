#include "OneHotVector.h"
namespace FengML
{
    OneHotVector::OneHotVector(size_t index, size_t len) :
        m_len(len),
        m_index(index)
    {}

    OneHotVector::~OneHotVector()
    {
    }
}