#include <iostream>
#include <fstream>
#include <vector>
#include "zip.h"


void writeZip(char *argv,std::ofstream &out)
{
    std::ifstream in(argv);
    LocalFileHeader lfh;

    
    //0x02014b5
    
    
    
    uint32_t signa=0x04034b50;
    lfh.signature=signa;
    lfh.version=0x14;
    lfh.flags=0;
    lfh.comp_method=0;
    lfh.mtime=zip::makeTime(4,30,15);
    lfh.mdate=zip::makeDate(20,8,2020);
    in.seekg(0,in.end);
    long posi=in.tellg();
    lfh.comp_file_size=posi;
    lfh.orig_file_size=posi;
    std::string nambe=argv;
    lfh.name_len=nambe.length();
    
    out.write(reinterpret_cast<char*>(&lfh),sizeof(LocalFileHeader));
    out.write(argv,sizeof(argv));
    
    long offset=out.tellp();

    CentralDirectoryFileHeader cdh;
    
    uint32_t sig=0x02014b50;
    cdh.signature=sig;

    

    
    cdh.version_made=0x14;
    cdh.version_extract=0x14;
    cdh.flags=0;
    cdh.file_comment_len=0;
    cdh.extra_len=0;
    cdh.comp_method=0;
    cdh.file_attrs1=0;
    cdh.file_attrs2=0;
    cdh.crc32=0;
    cdh.mtime=zip::makeTime(4,30,15);
    cdh.mdate=zip::makeDate(20,8,2020);
    cdh.orig_file_size=posi;
    cdh.comp_file_size=posi;
    cdh.name_len=nambe.length();
    out.write(reinterpret_cast<char*>(&cdh),sizeof(CentralDirectoryFileHeader));
    
    

    EndOfCentralDirectory ecd;

    sig=0x06054b50;
    ecd.signature=sig;
    ecd.disk_number=0;
    ecd.disk_start=0;
    ecd.cd_records1=3;
    ecd.cd_records2=3;
    ecd.size_of_cd=(sizeof(CentralDirectoryFileHeader));
    ecd.offset_of_cd=offset;
    ecd.comment_length=0;

    out.write(reinterpret_cast<char*>(&ecd),sizeof(EndOfCentralDirectory));


    in.close();
}


int main(int argc, char *argv[])
{
    
    if (argc != 5)
    {
        std::cerr << "Usage: " << argv[0] << " <input file 1>  <input file 2>  <input file 3>  <zip file>\n";
        return 1;
    }
    // argv[1] -> input file
    // argv[2] -> input file
    // argv[3] -> input file

    // argv[4] -> output zip file
    
    std::ofstream out(argv[4]);

    writeZip(argv[1],out);
    writeZip(argv[2],out);
    writeZip(argv[3],out);
    
    out.close();



}
