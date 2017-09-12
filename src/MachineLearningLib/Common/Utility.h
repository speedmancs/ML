#pragma once
#include <string>
namespace FengML
{
    class Utility
    {
    public:
        static int EndiannessSwap(int value);
        static void ToLower(std::string& str);
    };
}
