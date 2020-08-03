#include <iostream>
#include <fstream>
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input file>\n";
        return 1;
    }

    std::ifstream in(argv[1]);
   
    if (!in.is_open())
    {
        std::cerr << "Cannot open file " << argv[1] << '\n';
        return 1;
    }

    char buffer[2]={};
    in.read(buffer,2);

    if(buffer[0]=='B' && buffer[1]=='M')
    {
        std::cout<<"Valid BMP";
    }else
    {
        std::cout<< "Invalid BMP" <<"\n";
        return 1;
    }
    std::cout<<"\n";
    int size;
    in.read(reinterpret_cast<char *>(&size),4);
    std::cout << "Size: "<< size << "\n";

    int extra;
    in.read(reinterpret_cast<char *>(&extra),4);

    int offset;
    in.read(reinterpret_cast<char *>(&offset),4);
    
    std::cout<<"Offset: " << offset<< "\n";
    
    int headerSize;
    in.read(reinterpret_cast<char *>(&headerSize),4);
    std::cout<<"Size: " << headerSize<<"\n";

    int Width;
    in.read(reinterpret_cast<char *>(&Width),4);
    std::cout<<"Width: " << Width<<"\n";
    
    uint16_t Height;
    in.read(reinterpret_cast<char *>(&Height),4);
    std::cout<<"Height: " << Height<<"\n";


    return 0;
}
