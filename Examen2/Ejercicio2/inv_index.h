#ifndef _INV_INDEX_H_
#define _INV_INDEX_H_

#include <cstdint>
#include <iosfwd>
#include <string>
#include <vector>
#include<iostream>

namespace IIdx
{
    struct FileHeader
    {
        uint32_t word_count;
        uint32_t crc;
    } __attribute((packed));

    struct FileIndexEntry
    {
        FileIndexEntry()
        {
            std::fill(name,name + 64,0);
        }
        char name[64];
        uint32_t entry_count;
        uint32_t entry_offset;
    } __attribute((packed));
    
    struct IndexData
    {
        std::string country;
        std::vector<uint32_t> locations;
    };
    using IndexDataVector = std::vector<IndexData>;

    void writeIndex(const IndexDataVector& idx_datav, std::ostream& out);
} // namespace InvIdx

#endif
