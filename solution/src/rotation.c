#include "../include/image.h"
#include "../include/rotation.h"

struct image rotate(struct image const source)
{
    struct image rotated_img = image_create(source.height, source.width);
    for (size_t row = 0; row < source.height; row++)
    {
        for (size_t col = 0; col < source.width; col++)
        {
            rotated_img.data[col * source.height + (source.height - 1 - row)] = source.data[row * source.width + col];
        }
    }
    return rotated_img;
}
