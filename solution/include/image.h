#ifndef ASSIGNMENT_IMAGE_ROTATION_IMAGE_H
#define ASSIGNMENT_IMAGE_ROTATION_IMAGE_H

#include <stdint.h>

struct image
{
  uint64_t width, height;
  struct pixel *data;
};

struct image image_create(uint64_t width, uint64_t height);
void image_destroy(struct image *img);

struct pixel
{
  uint8_t b, g, r;
};

#endif
