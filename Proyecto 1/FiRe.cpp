#include "FiRe.h"
#include <netinet/in.h>
FiRe::FiRe(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input file>\n";
        
    }
}

int FiRe::getMagicN(char *argv[])
{
    
    std::ifstream in(argv[1]);
  
    if (!in.is_open())
    {
        std::cerr << "Cannot open file " << argv[1] << '\n';
        return 1;
    }

    unsigned char lol[10]={};
    in.read(reinterpret_cast<char*>(lol),10);
   
    std::string magicN="";
    for(int x=0;x<10;x++)
    {
        
        if(( unsigned char )lol[x]>=65 &&( unsigned char )lol[x]<=90 ||( unsigned char )lol[x]>=97 &&( unsigned char )lol[x]<=122 )
            magicN+=lol[x];
    }
    std::string id=argv[1];
    printFormat(magicN,in,argv,lol);
    return 0;
}

void FiRe::printFormat(std::string magicN,std::ifstream &in,char *argv[],unsigned char* lol)
{
    std::cout<< "El formato del archivo es: ";
    if(magicN=="IIF")
    {
        std::cout<< "TIF";
    }else if(magicN=="JFIF")
    {
        std::cout<< "JPG";

        
        
        FILE *f=fopen(argv[1],"rb");
        if (f==0)
        {
            std::cout << "Error";
        } 
        fseek(f,0,SEEK_END);
        long len=ftell(f);
        fseek(f,0,SEEK_SET);
        if (len<24) {
            fclose(f);
            std::cout << "Error: " << len << "\n";
        }
        

        unsigned char buf[24]; fread(buf,1,24,f);

        
        if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF && buf[3]==0xE0 && buf[6]=='J' && buf[7]=='F' && buf[8]=='I' && buf[9]=='F')
        { 
            long pos=2;
            while (buf[2]==0xFF)
            {
                if (buf[3]==0xC0 || buf[3]==0xC1 || buf[3]==0xC2 || buf[3]==0xC3 || buf[3]==0xC9 || buf[3]==0xCA || buf[3]==0xCB) break;
                pos += 2+(buf[4]<<8)+buf[5];
                if (pos+12>len) break;
                fseek(f,pos,SEEK_SET); fread(buf+2,1,12,f);
            }
        }

        fclose(f);

 
        if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF)
        { 
           int y = (buf[7]<<8) + buf[8];
           int x = (buf[9]<<8) + buf[10];
           std::cout << "\nHeight: " << y << "\n";
           std::cout<< "Width: " << x<< "\n";

           
        }



    }else if(magicN=="PNG")
    {
        std::cout<< "PNG" <<"\n";


        in.seekg(16L, in.beg);
        int width;
        in.read(reinterpret_cast<char*>(&width),4);
        width=ntohl(width);
        std::cout<< "Width: " << width<< "\n";
        int height;
        in.read(reinterpret_cast<char*>(&height),4);
        height=ntohl(height);
        std::cout<< "Height: " << height<< "\n";

    }else if(magicN=="GIFa")
    {
        std::cout<< "GIF";
    }else if(magicN=="xmlvers")
    {
        std::cout<< "SVG";
    }else if(lol[0]==0x42 && lol[1]==0x4d)
    {
        std::cout<< "BMP" << "\n";

        in.seekg(18L,in.beg);
            
            int width;
            in.read(reinterpret_cast<char*>(&width),4);
            std::cout<< "Width: " << width<< "\n";
            int height;
            in.read(reinterpret_cast<char*>(&height),4);
            std::cout<< "Height: " << height<< "\n";
    }else if(magicN=="PK")
    {
       std::cout<< "ZIP" << "\n";
    }else if(magicN=="RarY")
    {
        std::cout<< "RAR" << "\n";
    }else if(magicN=="O")
    {
        std::cout<< "GZIP" << "\n";
    }else if(magicN=="BZhAYSY")
    {
        std::cout<< "BZIP" << "\n";
    }else if(magicN=="zXZ")
    {
        std::cout<< "XZ" << "\n";

    }else if(magicN=="ELF")
    {
        in.seekg(4L,in.beg);
        int type;
        in.read(reinterpret_cast<char*>(&type),1);

        if(type==1)
            type=32;
        if(type==2)
            type=64;

        std::cout<< "Ejecutable linux de "<< type<<" bits\n";

    }else if(magicN=="MZ")
    {
        in.seekg(0,in.beg);
        char type[4];
        in.read(reinterpret_cast<char*>(type),4);

        while(!in.eof())
        {
            if(type[0]=0x50 && type[1]==0x45 && type[2]==0x00 && type[3]==0x00)
            {
                
                break;
            }
             in.read(reinterpret_cast<char*>(type),4);
        }
        
        int pop;
        in.read(reinterpret_cast<char*>(&pop),2);

        if(pop==34404)
            pop=64;
        if(pop==332)
            pop=32;

        std::cout<< "Ejecutable de windows: " << pop <<"\n";
        


    }
    else 
    {
        std::cout<< "No es un tipo de archivo compatible" << "\n";
    }
    

    std::cout<<"\n";

}