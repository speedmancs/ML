#include "SeqDataSet.h"
namespace FengML
{
    SeqDataSet::SeqDataSet(int _categoryNumber)
    {
        m_categoryNumber = _categoryNumber;
    }

    const SeqData& SeqDataSet::GetSeqData(size_t index) const
    {
        return m_allInput[index];
    }

    const SeqData& SeqDataSet::GetSeqTarget(size_t index) const
    {
        return m_allTargets[index];
    }
}