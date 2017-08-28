#include "DataSet.h"
namespace FengML
{
    int DataSet::TotalCategory = 10;
    DataSet::DataSet(const std::string& filePath)
    {
        Load(filePath);
    }

    bool DataSet::Load(const std::string& filePath)
    {
        // should update TotalCategory
        return true;
    }

    Vector<float>& DataSet::GetData(size_t index)
    {
        assert(index < m_allData.size());
        return *m_allData[index].data;
    }

    OneHotVector<float> DataSet::GetTarget(size_t index)
    {
        return OneHotVector<float>(m_allData[index].target, TotalCategory);
    }
}