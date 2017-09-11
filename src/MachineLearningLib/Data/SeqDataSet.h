#pragma once
#include <string>
#include <vector>
#include "..\Common\OneHotVector.h"
namespace FengML
{
    typedef std::vector<OneHotVector> SeqData;
    class SeqDataSet
    {
    public:
        SeqDataSet() = default;
        SeqDataSet(int categoryNumber);
        virtual bool Load(const std::string& dataFile) = 0;
        const SeqData& GetSeqData(size_t index) const;
        const SeqData& GetSeqTarget(size_t index) const;
        size_t Size() const
        {
            return m_allInput.size();
        }
    protected:
        std::vector<SeqData> m_allInput;
        std::vector<SeqData> m_allTargets;
        int m_categoryNumber;
    };
}
