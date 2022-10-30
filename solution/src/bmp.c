#include "../include/bmp.h"
#include "../include/file.h"
#include <stdio.h>
#include <stdlib.h>

#define TYPE 0x4D42
#define BIT_COUNT 24
#define PLANES 1
#define SIZE 40
#define RESERVED 0
#define COMPRESSION 0
#define XPELS_PER_METER 0
#define YPELS_PER_METER 0
#define CLR_USED 0
#define CLR_IMPORTANT 0

uint8_t get_padding(uint64_t width)
{
  return (uint8_t)(4 - (width * sizeof(struct pixel)) % 4) % 4;
}

struct bmp_header *bmp_header_create(struct image const *img)
{
  struct bmp_header *bmp_header = malloc(sizeof(struct bmp_header));
  uint32_t width = img->width;
  uint32_t height = img->height;
  uint32_t bmp_header_size = sizeof(struct bmp_header);
  uint32_t img_size = (uint32_t)(width * sizeof(struct pixel) + get_padding(width) * height);
  *bmp_header = (struct bmp_header){
      TYPE,
      img_size + bmp_header_size,
      RESERVED,
      bmp_header_size,
      SIZE,
      width,
      height,
      PLANES,
      BIT_COUNT,
      COMPRESSION,
      XPELS_PER_METER,
      YPELS_PER_METER,
      CLR_USED,
      CLR_IMPORTANT};
  return bmp_header;
}

enum read_status from_bmp(FILE *input_file, struct image *img)
{
  struct bmp_header *bmp_header = malloc(sizeof(struct bmp_header));
  if (!fread(bmp_header, 1, sizeof(struct bmp_header), input_file))
  {
    return READ_INVALID_HEADER;
  }
  *img = image_create(bmp_header->biWidth, bmp_header->biHeight);
  uint64_t i = 0;
  uint8_t padding = get_padding(bmp_header->biWidth);
  free(bmp_header);
  for (uint64_t y = 0; y < img->height; ++y)
  {
    for (uint64_t x = 0; x < img->width; ++x)
    {
      if (fread(img->data + i, sizeof(struct pixel), 1, input_file) != 1)
      {

        free(img->data);
        return READ_INVALID_BITS;
      }
      ++i;
    }
    if (fseek(input_file, padding, SEEK_CUR) != 0)
    {
      free(img->data);
      return READ_INVALID_BITS;
    }
  }
  return READ_OK;
}

enum write_status to_bmp(FILE *output_file, struct image const *img)
{
  struct bmp_header *bmp_header = bmp_header_create(img);
  if (fwrite(bmp_header, sizeof(struct bmp_header), 1, output_file) != 1)
  {
    free(bmp_header);
    return WRITE_ERROR;
  }
  uint8_t padding = get_padding(bmp_header->biWidth);
  free(bmp_header);
  uint64_t i = 0;
  for (uint64_t y = 0; y < img->height; ++y)
  {
    for (uint64_t x = 0; x < img->width; ++x)
    {
      if (fwrite(img->data + i, sizeof(struct pixel), 1, output_file) != 1)
      {
        return WRITE_ERROR;
      }
      ++i;
    }
    for (uint8_t j = 0; j < padding; ++j)
    {
      if (fwrite(&padding, sizeof(uint8_t), 1, output_file) != 1)
      {
        return WRITE_ERROR;
      }
    }
  }
  return WRITE_OK;
}

struct image from_bmp_check(const char *filename)
{
  struct file_with_status input_file = file_open(filename, "rb");
  struct image input_img = {0};
  bmp_read_message(from_bmp(input_file.file, &input_img));
  file_close(input_file.file);
  return input_img;
}

void to_bmp_check(struct image *output_img, const char *filename)
{
  struct file_with_status output_file = file_open(filename, "wb");
  bmp_write_message(to_bmp(output_file.file, output_img));
  file_close(output_file.file);
}

static const char *bmp_read_status_messages[] = {
    [READ_OK] = "Image is loaded succesfully\n",
    [READ_INVALID_SIGNATURE] = "Invalid Signature.\n",
    [READ_INVALID_BITS] = "Only 24-bit bmp file supported\n",
    [READ_INVALID_HEADER] = "Invalid file header\n",
    [READ_INVALID_FILENAME] = "Invalid file name\n"};

static const char *bmp_write_status_messages[] = {
    [WRITE_OK] = "Image is saved to file succesfully\n",
    [WRITE_ERROR] = "Write error\n"};

enum read_status bmp_read_message(enum read_status status)
{
  fprintf(stderr, "%s", bmp_read_status_messages[status]);
  return status;
}

enum write_status bmp_write_message(enum write_status status)
{
  fprintf(stderr, "%s", bmp_write_status_messages[status]);
  return status;
}
