#include <iostream>
#include <fstream>
#include <vector>
#include "zip.h"





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

    /*uint32_t signature;
    uint16_t version;
    uint16_t flags;
    uint16_t comp_method;
    uint16_t mtime;
    uint16_t mdate;
    uint32_t crc32;
    uint32_t comp_file_size;
    uint32_t orig_file_size;
    uint16_t name_len;
    uint16_t extra_len;*/
    int offset1=0;
    for(int x=1;x<4;x++)
    {

    std::ifstream in(argv[x]);
    LocalFileHeader lfh;
    uint32_t signa=0x04034b50;
    uint16_t ver=0x14;
    lfh.signature=signa;
    lfh.version=ver;
    lfh.flags=0;
    lfh.comp_method=0;
    lfh.mtime=zip::makeTime(4,30,15);
    lfh.mdate=zip::makeDate(20,8,2020);
    lfh.crc32=0;
    in.seekg(0,std::ios::end);
    uint32_t size=in.tellg();
    
    lfh.comp_file_size=size;
    lfh.orig_file_size=size;
    std::string nombre=argv[x];
    lfh.name_len=nombre.size();
    lfh.extra_len=0;

    unsigned char buf[size];
    in.seekg(0,std::ios::beg);
    offset1=in.tellg();
    in.read(reinterpret_cast<char*>(&buf),sizeof(buf));
    
    out.write(reinterpret_cast<const char*>(&lfh),sizeof(LocalFileHeader));
    out.write(reinterpret_cast<const char*>(nombre.data()),nombre.size());
    out.write(reinterpret_cast<const char*>(buf),sizeof(buf));

    }
    uint32_t offset = out.tellp();


    /*uint32_t signature;
    uint16_t version_made;
    uint16_t version_extract;
    uint16_t flags;
    uint16_t comp_method;
    uint16_t mtime;
    uint16_t mdate;
    uint32_t crc32;
    uint32_t comp_file_size;
    uint32_t orig_file_size;
    uint16_t name_len;
    uint16_t extra_len;
    uint16_t file_comment_len;
    uint16_t disk_number;
    uint16_t file_attrs1;
    uint32_t file_attrs2;
    uint32_t file_offset;*/
    for(int x=1;x<4;x++)
    {
    std::ifstream in(argv[x]);
    CentralDirectoryFileHeader cdh;

    uint32_t sig=0x02014b50;
    cdh.signature=sig;
    cdh.version_made=0x14;
    cdh.version_extract=0x14;
    cdh.flags=0;
    cdh.comp_method=0;
    cdh.mtime=zip::makeTime(4,30,15);
    cdh.mdate=zip::makeDate(20,8,2020);
    cdh.crc32=0;

    in.seekg(0,std::ios::end);
    uint32_t size=in.tellg();
    cdh.comp_file_size=size;
    cdh.orig_file_size=size;
    std::string nombre=argv[x];
    cdh.name_len=nombre.size();
    cdh.extra_len=0;
    cdh.file_comment_len=0;
    cdh.disk_number=0;
    cdh.file_attrs1=0;
    cdh.file_attrs2=0;
    cdh.file_offset=offset1;

    out.write(reinterpret_cast<char *>(&cdh),sizeof(CentralDirectoryFileHeader));
    out.write(reinterpret_cast<const char*>(nombre.data()),nombre.size());
    
    
    }
    uint32_t temp= out.tellp();
    uint32_t cd_Size=temp - offset; 
    /*uint32_t signature;
    uint16_t disk_number;
    uint16_t disk_start;
    uint16_t cd_records1;
    uint16_t cd_records2;
    uint32_t size_of_cd;
    uint32_t offset_of_cd;
    uint16_t comment_length;*/

    EndOfCentralDirectory ecd;
    uint32_t signan=0x06054b50;
    ecd.signature=signan;
    ecd.disk_number=0;
    ecd.disk_start=0;
    ecd.cd_records1=3;
    ecd.cd_records2=3;
    ecd.size_of_cd=cd_Size;
    ecd.offset_of_cd=offset;
    ecd.comment_length=0;

    out.write(reinterpret_cast<char*>(&ecd),sizeof(EndOfCentralDirectory));





   
    
    
    out.close();



}
