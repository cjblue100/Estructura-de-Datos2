#ifndef _ZIP_H_
#define _ZIP_H_

#include <cstdint>

/*
0	4	Local file header signature = 0x04034b50 (read as a little-endian number)
4	2	Version needed to extract (minimum)
6	2	General purpose bit flag
8	2	Compression method
10	2	File last modification time
12	2	File last modification date
14	4	CRC-32 of uncompressed data
18	4	Compressed size
22	4	Uncompressed size
26	2	File name length (n)
28	2	Extra field length (m)
30	n	File name
30+n	m	Extra field
*/

struct LocalFileHeader
{
    uint32_t signature;
    uint16_t version;
    uint16_t flags;
    uint16_t comp_method;
    uint16_t mtime;
    uint16_t mdate;
    uint32_t crc32;
    uint32_t comp_file_size;
    uint32_t orig_file_size;
    uint16_t name_len;
    uint16_t extra_len;
    // File name
    // Extra field
} __attribute((packed));

struct CentralDirectoryFileHeader
{
    uint32_t signature;
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
    uint32_t file_offset;
    // File name
    // Extra field
    // File comment
} __attribute((packed));

struct EndOfCentralDirectory
{
    uint32_t signature;
    uint16_t disk_number;
    uint16_t disk_start;
    uint16_t cd_records1;
    uint16_t cd_records2;
    uint32_t size_of_cd;
    uint32_t offset_of_cd;
    uint16_t comment_length;
} __attribute((packed));

namespace zip
{
    static inline uint16_t makeTime(uint8_t h, uint8_t m, uint8_t s)
    {
        return  (((h & 0x1f) << 11)
                | ((m & 0x3f) << 5)
                | ((s & 0x1f)>> 1));
    }

    static inline uint16_t makeDate(uint8_t d, uint8_t m, uint16_t y)
    {
        return  ((((y - 1980) & 0x7f) << 9)
                | ((m & 0xf) << 5)
                | (d & 0x1f));
    }
}

#endif
