#include "../include/image.h"
#include <malloc.h>
#include <stdint.h>

struct image image_create(uint64_t width, uint64_t height)
{
    struct image img = {
        .width = width,
        .height = height,
        .data = malloc(width * height * sizeof(struct pixel))};
    return img;
}

void image_destroy(struct image *img)
{
    if (img)
    {
        free(img->data);
    }
}
