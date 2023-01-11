#include "../include/file.h"
#include <stdio.h>
#include <string.h>

struct file_with_status file_open(const char *filename, char *mode)
{
    FILE *file = fopen(filename, mode);
    if (!file && strcmp((const char *)mode, (const char *)"rb") == 0)
    {
        return (struct file_with_status){.file = file, .status = OPEN_READ_ERROR};
    }
    if (!file && strcmp((const char *)mode, (const char *)"rb") == 0)
    {
        return (struct file_with_status){.file = file, .status = OPEN_WRITE_ERROR};
    }
    return (struct file_with_status){.file = file, .status = OPEN_OK};
}

enum file_close_status file_close(FILE *file)
{
    if (!file)
    {
        return CLOSE_ERROR;
    }
    fclose(file);
    return CLOSE_OK;
}
