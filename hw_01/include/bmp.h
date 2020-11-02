#pragma once

#include <stdint.h>
#include <stdbool.h>

#pragma pack(push, 1)
typedef struct BmpHeader {
     uint16_t bfType;
     uint32_t bfSize;
     uint16_t bfReserved1;
     uint16_t bfReserved2;
     uint32_t bfOffBits;

     uint32_t biSize;
     uint32_t biWidth;
     uint32_t biHeight;
     uint16_t biPlanes;
     uint16_t biBitCount;
     uint32_t biCompression;
     uint32_t biSizeImage;
     uint32_t biXPelsPerMeter;
     uint32_t biYPelsPerMeter;
     uint32_t biClrUsed;
     uint32_t biClrImportant;
} BmpHeader;
#pragma pack(pop)

typedef struct Bmp {
    BmpHeader header;
    uint8_t** data;
    uint32_t count;
} Bmp;

typedef struct Result {
    Bmp* bmp;
    bool done;
} Result;

void clear(Bmp* bmp);

Result load_bmp(const char* name);

Result crop(Bmp* in, const uint32_t x, uint32_t y, uint32_t const w, uint32_t const h);

Result rotate(Bmp* source);

bool save_bmp(const char* name, Bmp* bmp);