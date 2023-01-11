#include "../include/image.h"
#include "../include/rotation.h"

struct image rotate(struct image const source)
{
    struct image rotated_img = image_create(source.height, source.width);
    for (size_t row = 0; row < source.height; row++)
    {
        for (size_t col = 0; col < source.width; col++)
        {
            struct pixel* original_pos = (struct pixel*) geto_address_by_pixel(source.data, col, row, source.width);
            struct pixel* rotated_pos = (struct pixel*) getr_address_by_pixel(rotated_img.data, col, row, source.height);
            *rotated_pos = *original_pos;
        }
    }
    return rotated_img;

}

uint8_t* geto_address_by_pixel(struct pixel* const start, size_t col, size_t row, uint64_t width) {
    return (uint8_t*) start + 3 * (col + width * row); 
}
uint8_t* getr_address_by_pixel(struct pixel* const start, size_t col, size_t row, uint64_t height) {
    return (uint8_t*) start + 3 * (height - row - 1 + height * col);
}
