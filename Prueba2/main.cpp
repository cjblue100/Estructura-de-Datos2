#include <iostream>
#include <fstream>
#include <vector>
#include "bmp.h"
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input file>\n";
        return 1;
    }

    std::ifstream in(argv[1]);
    std::ofstream out(argv[2]);
   
    if (!in.is_open())
    {
        std::cerr << "Cannot open file " << argv[1] << '\n';
        return 1;
    }

    BitmapFileHeader bmpfh;

    in.read(reinterpret_cast<char*>(&bmpfh),sizeof(bmpfh));

    if(in.gcount() != sizeof(BitmapFileHeader))
    {
        std:: cerr << "Error reading BMP File: " << argv[1] << "\n";
        return 2;
    }

    if(bmpfh.id[0]!=0x42 || bmpfh.id[1]!=0x4d)
    {
        std::cerr << "Invalid BMP \n";
        in.close();
        return 1;
    }

    std::cout << "Valid Bmp\n";
    std::cout << "Size: "<<bmpfh.file_size <<"\n"
                <<"Offset: " << bmpfh.offset << "\n";

    BitmapInfoHeader bth;
    in.read(reinterpret_cast<char*>(&bth),sizeof(BitmapInfoHeader));

    if(in.gcount()!=sizeof(BitmapInfoHeader))
    {
        std:: cerr<< "Error reading BMP File: " << argv[1] <<"\n";
        return 2;
    }

    std::cout << "SIzeInfoH: " << bth.header_size << "\n";
    std::cout << "Width: " << bth.bmp_width << "\n";
    std::cout << "Height: " << bth.bmp_height << "\n";
    std::cout << "BPP: "<< bth.bmp_bpp << "\n";
    std::cout << "Colors used: "<< bth.bmp_pal_colors << "\n";
    std::cout << "Colors IMportant: "<< bth.bmp_imp_colors << "\n";
    std::vector<uint32_t> pal(bth.bmp_pal_colors);
    if(bth.bmp_pal_colors>0)
    {
        unsigned poffset = sizeof(BitmapFileHeader)+ bth.header_size;
        in.seekg(poffset);
       
        
        int sece=pal.size() * sizeof(uint32_t);
        in.read(reinterpret_cast<char*>(pal.data()),sece);
        

        if(in.gcount()!=sece)
        {
        std:: cerr<< "Error reading COLOR PALETTE \n";
        return 2;
        }
        /*
        int i=0;
        pal[2];

        std::cout<<std::hex<< "LOL: " << pal[2] << std::dec<<"\n";
        for(auto c: pal)
        {
            std::cout<<i++<<" : "<<std::hex << c << std::dec << "\n";
            
        }

        return 1;
        */

    }


    in.seekg(bmpfh.offset);
    char pixel[3];
    in.read(pixel, sizeof(pixel));

    if(in.gcount()!=sizeof(pixel))
    {
        std:: cerr<< "Error reading BMP File: " << argv[1] <<"\n";
        return 2;
    }

    size_t row_size = ((bth.bmp_comp * bth.bmp_width + 31)/32)*4;
    std::vector<std::vector<uint8_t>> img_rows(bth.bmp_height);
    size_t row_sizeRounded= ((row_size* 24 + 31)/32)*4;
    in.seekg(bmpfh.offset);
    uint32_t pArray_Size=row_sizeRounded*bth.bmp_width;
    for(int i=0;i<bth.bmp_height;i++)
    {
        img_rows[i].resize(row_sizeRounded);
        in.read(reinterpret_cast<char*>(img_rows[i].data()),row_sizeRounded);

        if(in.gcount()!=row_size)
        {
            std:: cerr<< "Error reading pixel data\n";
            return 2;

        }
    }
    uint32_t filesize= (sizeof(BitmapFileHeader)+sizeof(BitmapInfoHeader)) + pArray_Size;
    out.write(bmpfh.id,sizeof(bmpfh.id));
    out.write((char*)&filesize,sizeof(bmpfh.file_size));
    out.write((char*)&bmpfh.res1,sizeof(bmpfh.res1));
    out.write((char*)&bmpfh.res2,sizeof(bmpfh.res2));
    out.write((char*)(sizeof(BitmapFileHeader)+sizeof(BitmapInfoHeader)),sizeof(bmpfh.offset));
    out.write((char*)&bth.header_size,sizeof(bth.header_size));
    out.write((char*)&bth.bmp_width,sizeof(bth.bmp_width));
    out.write((char*)&bth.bmp_height,sizeof(bth.bmp_height));
    out.write((char*)&bth.bmp_planes,sizeof(bth.bmp_planes));
    out.write((char*)24,sizeof(bth.bmp_bpp));
    out.write((char*)&bth.bmp_comp,sizeof(bth.bmp_comp));
    out.write((char*)&pArray_Size,sizeof(bth.bmp_img_size));
    out.write((char*)&bth.bmp_horiz_res,sizeof(bth.bmp_horiz_res));
    out.write((char*)&bth.bmp_vert_res,sizeof(bth.bmp_vert_res));
    out.write((char*)0,sizeof(bth.bmp_pal_colors));
    out.write((char*)0,sizeof(bth.bmp_imp_colors));
    out.write((char*)bth.extra,sizeof(bth.extra));



    
    out.close();

    in.close();

    
    return 0;
}
