#ifndef ASSIGNMENT_IMAGE_ROTATION_FILE_H
#define ASSIGNMENT_IMAGE_ROTATION_FILE_H

#include <stdio.h>

enum file_open_status
{
  OPEN_OK = 0,
  OPEN_READ_ERROR,
  OPEN_WRITE_ERROR
};

enum file_close_status
{
  CLOSE_OK = 0,
  CLOSE_ERROR
};

struct file_with_status
{
  FILE *file;
  enum file_open_status status;
};

struct file_with_status file_open(const char *filename, char *mode);
enum file_close_status file_close(FILE *file);

#endif
