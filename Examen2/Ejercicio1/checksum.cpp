#include "checksum.h"

uint32_t Checksum::compute(const std::string &str)
{
    uint32_t sum = 0;
    std::string temp = str;
    int size = str.length() % 4;


    if(str.length()%4 ==0)
    {
        int i=0;
        while (i <= str.length()-1)
        {
            sum += makeWord(str[i], str[i + 1], str[i + 2], str[i + 3]);
            i += 4;
        }
       
        return (~sum + 1);
    }

    while (temp.length() % 4 != 0 )
    {
        temp += ' ';
    }
    

    int i = 0;
    if (str.length() % 4 != 0 && str.length() > 4)
    {
        
        while (i <= temp.length()-1)
        {
            sum += makeWord(temp[i], temp[i + 1], temp[i + 2], temp[i + 3]);
            
            i += 4;
        }
        
        return (~sum + 1);
    }

    if (str.length() < 4)
    {
        if (str.length() == 1)
        {
            sum += makeWord(str[0],' ', ' ', ' ');
        }

        if (str.length() == 2)
        {
            sum += makeWord(str[0], str[1], ' ', ' ');
        }

        if (str.length() == 3)
        {
            sum += makeWord(str[0], str[1], str[2], ' ');
        }

       
        return  (~sum + 1);
    }

  
    return (~sum + 1);
}

uint8_t chech(const std::string &str, size_t size)
{
}