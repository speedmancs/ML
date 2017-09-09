#include "MnistDataSet.h"
#include "..\Common\Utility.h"
#include <fstream>
using namespace std;
namespace FengML
{
    bool MnistDataSet::Load(const std::string& dataFile, const std::string& labelFile)
    {
        LoadData(dataFile);
        LoadLabels(labelFile);
        return true;
    }
    bool MnistDataSet::Dump(const std::string& filePath)
    {
        ofstream fout(filePath.c_str());
        fout << "samples:" << m_allData.size() << endl;
        fout << "categories:" << m_categoryNumber << endl;
        for (int i = 0; i < m_allData.size(); i++)
        {
            if (i % 1000 == 0)
            {
                cout << i << " samples dumped" << endl;
            }
            fout << "sample " << i << ": label: " << m_targets[i].HotIndex() << endl;
            m_allData[i].Print(fout, col);
            fout << "====================================" << endl;
        }
        return true;
    }

    bool MnistDataSet::LoadData(const std::string& dataFile)
    {
        std::ifstream fin(dataFile.c_str(), std::ifstream::binary);
        if (!fin)
            return false;

        int magicNumber;
        int number;
        fin.read((char *)&magicNumber, 4);
        magicNumber = Utility::EndiannessSwap(magicNumber);
        fin.read((char *)&number, 4);
        number = Utility::EndiannessSwap(number);
        fin.read((char *)&row, 4);
        fin.read((char *)&col, 4);
        row = Utility::EndiannessSwap(row);
        col = Utility::EndiannessSwap(col);
        
        unsigned char* buffer = new unsigned char[row * col];
        for (int i = 0; i < number; i++)
        {
            if (i % 1000 == 0)
            {
                cout << "\r" << i << " samples loaded";
            }
            fin.read((char *)buffer, row * col);
            m_allData.emplace_back(buffer, row * col);
            m_allData.back().Div(255.0f);
        }

        cout << endl;
        delete[]buffer;
        return true;
    }

    bool MnistDataSet::LoadLabels(const std::string& labelFile)
    {
        std::ifstream fin(labelFile.c_str(), std::ifstream::binary);
        if (!fin)
            return false;
        
        int magicNumber;
        int number;
        fin.read((char *)&magicNumber, 4);
        magicNumber = Utility::EndiannessSwap(magicNumber);
        fin.read((char *)&number, 4);
        number = Utility::EndiannessSwap(number);

        unsigned char t;
        for (int i = 0; i < number; i++)
        {
            fin.read((char *)&t, 1);
            m_targets.push_back(OneHotVector((size_t)t, m_categoryNumber));
        }
        return true;
    }
}