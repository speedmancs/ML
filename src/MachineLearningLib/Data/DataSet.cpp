#include "DataSet.h"
#include "..\Common\OneHotVector.h"
namespace FengML
{
    DataSet::DataSet(int categoryNumber):
        m_categoryNumber(categoryNumber)
    {
    }

    const Vector<float>& DataSet::GetData(size_t index) const
    {
        assert(index < m_allData.size());
        return m_allData[index];
    }

    const OneHotVector& DataSet::GetTarget(size_t index) const
    {
        return m_targets[index];
    }
}