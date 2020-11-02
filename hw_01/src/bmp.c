#include "bmp.h"
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


void clear(Bmp* bmp) {
    if (bmp != NULL) {
        if (bmp->data != NULL) {
            for (uint32_t i = 0; i < bmp->header.biHeight; ++i) {
                if (bmp->data[i] == NULL) {
                    break;
                }
                free(bmp->data[i]);
            }
            free(bmp->data);
        }
        free(bmp);
    }
}


bool init_bmp(Bmp* bmp) {
    assert(bmp != NULL);
    bmp->count = 3 * bmp->header.biWidth;
    if ((3 * bmp->header.biWidth) % 4 > 0) {
        bmp->count += 4 - (3 * bmp->header.biWidth % 4);
    }
    bmp->data = (uint8_t**)malloc(bmp->header.biHeight * sizeof(uint8_t*));
   
    if (bmp->data == NULL) {
        return false;
    }

    for (uint32_t i = 0; i < bmp->header.biHeight; ++i) { 
        bmp->data[i] = (uint8_t*)calloc(bmp->count, 1);
        if (bmp->data[i] == NULL) {
            return false;
        }
    }
    return true;
}


Result get_new_bmp_from_old(Bmp* oldBmp, const uint32_t w, const uint32_t h) {
    assert(oldBmp != NULL);
    Result newBmp = {NULL, false};

    newBmp.bmp = malloc(sizeof(struct Bmp));
    if (newBmp.bmp == NULL) {
        return newBmp;
    }

    newBmp.bmp->header = oldBmp->header;
    newBmp.bmp->header.biWidth = w;
    newBmp.bmp->header.biHeight = h;

    if (!init_bmp(newBmp.bmp)) {
        return newBmp;
    }

    newBmp.bmp->header.bfSize -= oldBmp->header.biHeight * oldBmp->count;
    newBmp.bmp->header.bfSize += h * newBmp.bmp->count;
    newBmp.bmp->header.biSizeImage -= oldBmp->header.biHeight * oldBmp->count;
    newBmp.bmp->header.biSizeImage += h * newBmp.bmp->count;

    newBmp.done = true;
    return newBmp;
}


Result load_bmp(const char* fileName) {
    Result bmp = {NULL, false};
    if (fileName == NULL) {
        return bmp;
    }

    FILE* in = fopen(fileName, "rb");
    if (in == NULL) {
        return bmp;
    }

    bmp.bmp = malloc(sizeof(struct Bmp));
    if (bmp.bmp == NULL) {
        fclose(in);
        return bmp;
    }

    if (fread(&bmp.bmp->header, sizeof(struct BmpHeader), 1, in) != 1) {
        fclose(in);
        return bmp;
    } 

    if (!init_bmp(bmp.bmp)) {
        fclose(in);
        return bmp;
    }

    for (uint32_t i = 0; i < bmp.bmp->header.biHeight; ++i) { 
        if (fread(bmp.bmp->data[i], 1, bmp.bmp->count, in) != bmp.bmp->count) {
            fclose(in);
            return bmp;
        }
    }

    fclose(in);
    bmp.done = true;
    return bmp;
}


Result crop(Bmp* source, const uint32_t x, uint32_t y, const uint32_t w, const uint32_t h) {
    assert(source != NULL);

    Result result = get_new_bmp_from_old(source, w, h);
    if (!result.done) {
        return result;
    }


    y = source->header.biHeight - (y + h);
    for (uint32_t i = y; i < y + h; ++i) {
        for (uint32_t j = 3 * x; j < 3 * (x + w); ++j) {
            result.bmp->data[i - y][j - 3 * x] = source->data[i][j];
        }
    }

    result.done = true;
    return result;
}


Result rotate(Bmp* source) {
    assert(source != NULL);

    Result result = get_new_bmp_from_old(source, source->header.biHeight, source->header.biWidth);
    if (!result.done) {
        return result;
    }

    for (uint32_t i = 0; i < source->header.biHeight; ++i) {
        for (uint32_t j = 0; j < source->header.biWidth; ++j) {
            result.bmp->data[result.bmp->header.biHeight - 1 - j][3 * i] = source->data[i][3 * j];
            result.bmp->data[result.bmp->header.biHeight - 1 - j][3 * i + 1] = source->data[i][3 * j + 1];
            result.bmp->data[result.bmp->header.biHeight - 1 - j][3 * i + 2] = source->data[i][3 * j + 2];
        }
    }

    result.done = true;
    return result;
}


bool save_bmp(const char* fileName, Bmp* bmp) {
    if (fileName == NULL) {
        return false;
    }

    FILE* out = fopen(fileName, "wb");
    if (out == NULL) {
        return false;
    }

    if (fwrite(&bmp->header, sizeof(struct BmpHeader), 1, out) != 1) {
        return false;
    }

    for (uint32_t i = 0; i < bmp->header.biHeight; ++i) { 
        if (fwrite(bmp->data[i], 1, bmp->count, out) != bmp->count) {
            return false;
        }
    }

    fclose(out);
    return true;
}
