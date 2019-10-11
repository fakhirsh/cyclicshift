#include "String.hpp"

namespace FEngine
{
    namespace String
    {
        
        void PrependZeros(std::string & str, int totalDigits)
        {
            int zerosToPrepend = totalDigits - str.length();
            
            for(int i = 0; i < zerosToPrepend; i++)
            {
                str = std::string("0") + str;
            }
        }
        
    }
}
