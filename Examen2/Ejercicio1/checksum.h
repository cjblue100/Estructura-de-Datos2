#ifndef _CHECKSUM_H_ 
#define _CHECKSUM_H_

#include <cstdint>
#include <string>

inline uint32_t makeWord(char b0, char b1, char b2, char b3)
{
    return ((static_cast<uint32_t>(static_cast<uint8_t>(b0)) << 24)
            | (static_cast<uint32_t>(static_cast<uint8_t>(b1)) << 16)
            | (static_cast<uint32_t>(static_cast<uint8_t>(b2)) <<  8)
            | (static_cast<uint32_t>(static_cast<uint8_t>(b3)) <<  0));
}

uint8_t chech(std::string& str, size_t size)
{
    uint8_t sum=0;
    for(int i=0;i<size;i++)
    {
        sum+=static_cast<uint8_t>(str[i]);
    }

    return (~sum +1);

}

namespace Checksum
{
    uint32_t compute(const std::string& str);
    


    
    
    
}

#endif
