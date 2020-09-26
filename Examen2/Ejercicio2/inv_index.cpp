#include "inv_index.h"

void IIdx::writeIndex(const IndexDataVector &idx_datav, std::ostream &out)
{

    FileHeader fh;
    fh.word_count = idx_datav.size();
    fh.crc = CRC::Calculate(reinterpret_cast<char *>(&fh), sizeof(FileHeader) - sizeof(uint32_t), CRC::CRC_32());
    out.write(reinterpret_cast<const char *>(&fh), sizeof(FileHeader));
    uint32_t offset=sizeof(FileHeader) + (sizeof(FileIndexEntry) *idx_datav.size());
    for (int i = 0; i < fh.word_count-1; i++)
    {

        FileIndexEntry fie;
        std::copy(idx_datav.at(i).country.begin(), idx_datav.at(i).country.end(), fie.name);
        fie.entry_count = idx_datav.at(i).locations.size();
        fie.entry_offset = offset;

        out.write(reinterpret_cast<const char *>(&fie), sizeof(FileIndexEntry));
        offset+=sizeof(IndexData);
    }

    for (int i = 0; i < fh.word_count-1; i++)
    {
        
        out.write(reinterpret_cast<const char*>(&idx_datav.at(i).locations),sizeof(IndexData));
    }
}