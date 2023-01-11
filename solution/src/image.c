#include "../include/image.h"
#include <malloc.h>
#include <stdint.h>

struct image image_create(uint64_t width, uint64_t height)
{
    struct image img = {
        .width = width,
        .height = height,
        .data = malloc(height*width*sizeof(struct pixel))};
    return img;
}

void image_destroy(struct image *img)
{
    if (img)
    {
        img->height = 0;
        img->width = 0;
        free(img->data);
    }
}
