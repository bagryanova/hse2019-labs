#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    if (argc < 8) {
        return 1;
    }
    char* in_bmp = argv[2];
    char* out_bmp = argv[3];
    uint32_t x = atoi(argv[4]);
    uint32_t y = atoi(argv[5]);
    uint32_t w = atoi(argv[6]);
    uint32_t h = atoi(argv[7]);

    Result in = load_bmp(in_bmp);
    if (!in.done) {
        clear(in.bmp);
        return 1;
    }

    if (!(x < in.bmp->header.biWidth && y < in.bmp->header.biHeight 
        && x + w <= in.bmp->header.biWidth && y + h <= in.bmp->header.biHeight && h > 0 && w > 0)) {
        clear(in.bmp);
        return 1;
    }

    Result cropped = crop(in.bmp, x, y, w, h);
    clear(in.bmp);
    if (!cropped.done) {
        clear(cropped.bmp);
        return 1;
    }

    Result rotated = rotate(cropped.bmp);
    clear(cropped.bmp);
    if (!rotated.done) {
        clear(rotated.bmp);
        return 1;
    }

    if (!save_bmp(out_bmp, rotated.bmp)) {
        clear(rotated.bmp);
        return 1;
    }
    clear(rotated.bmp);
}