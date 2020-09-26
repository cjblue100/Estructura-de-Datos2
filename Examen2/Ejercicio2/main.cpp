#include <cstdint>
#include <iostream>
#include <fstream>
#include "inv_index.h"

IIdx::IndexDataVector idx_datav = {
    { "Honduras", {82, 91, 44, 73, 90, 27, 12} },
    { "Guatemala", {88, 71, 18, 43, 8, 47, 83, 83, 100} },
    { "Belice", {37, 29, 25, 100, 39} },
    { "El Salvador", {76, 89, 79, 54, 71} },
    { "Costa Rica", {18, 95, 38, 41, 95, 26} },
    { "Nicaragua", {58, 86, 56, 89, 86, 99, 12, 97, 94, 48, 3} },
    { "Panama", {10, 18, 83, 69, 66, 4, 59, 52, 42} },
};

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <output file>\n";
        return 1;
    }
    
    std::ofstream out(argv[1], std::ios::out|std::ios::trunc);

    if (!out.is_open())
    {
        std::cerr << "Cannot open file '" << argv[1] << "'\n";
        return 1;
    }

    
    
    


    IIdx::writeIndex(idx_datav, out);
    




    out.close();
    
    return 0;
}
