#ifndef ASSIGNMENT_IMAGE_ROTATION_TRANSFORMATIONS_H
#define ASSIGNMENT_IMAGE_ROTATION_TRANSFORMATIONS_H

#include "image.h"
#include "malloc.h"

struct image rotate(struct image const source);
uint8_t* geto_address_by_pixel(struct pixel* const start, size_t col, size_t row, uint64_t width);
uint8_t* getr_address_by_pixel(struct pixel* const start, size_t col, size_t row, uint64_t height);

#endif
