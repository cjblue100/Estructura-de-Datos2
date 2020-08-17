#include <iostream>
#include <fstream>
#include <string>

class FiRe
{
    public:

    FiRe(int argc, char *argv[]);

    int getMagicN(char *argv[]);

    void printFormat(std::string magicN,std::ifstream &in,char *argv[],unsigned char* lol);
    void printResolution(std::string magicN);

};


