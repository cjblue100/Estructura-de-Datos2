#ifndef _BMP_H_
#define _BMP_H_

#include <cstdint>

struct BitmapFileHeader
{
    char id[2];
    uint32_t file_size;
    uint16_t res1;
    uint16_t res2;
    uint32_t offset;
} __attribute__((packed));

struct BitmapInfoHeader
{
    uint32_t header_size;
    uint32_t bmp_width;
    uint32_t bmp_height;
    uint16_t bmp_planes;
    uint16_t bmp_bpp;
    uint32_t bmp_comp;
    uint32_t bmp_img_size;
    uint32_t bmp_horiz_res;
    uint32_t bmp_vert_res;
    uint32_t bmp_pal_colors;
    uint32_t bmp_imp_colors;
    uint32_t extra[17];
} __attribute__((packed));

#endif
