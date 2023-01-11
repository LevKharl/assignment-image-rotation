#ifndef ASSIGNMENT_IMAGE_ROTATION_BMP_H
#define ASSIGNMENT_IMAGE_ROTATION_BMP_H

#include "../include/format.h"
#include "../include/image.h"
#include <stdint.h>
#include <stdio.h>

enum read_status
{
  READ_OK = 0,
  READ_INVALID_SIGNATURE,
  READ_INVALID_BITS,
  READ_INVALID_HEADER,
  READ_INVALID_FILENAME
};

enum write_status
{
  WRITE_OK = 0,
  WRITE_ERROR
};

struct bmp_header bmp_header_create(struct image const *img);

enum read_status from_bmp(FILE *input_file, struct image *img);
enum write_status to_bmp(FILE *output_file, struct image const *img);

struct image from_bmp_check(const char *filename);
void to_bmp_check(struct image *output_img, const char *filename);

enum read_status bmp_read_message(enum read_status status);
enum write_status bmp_write_message(enum write_status status);

#endif
