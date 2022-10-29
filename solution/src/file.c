#include "../include/file.h"
#include <stdio.h>
#include <string.h>

struct file_with_status file_open(const char *filename, char *mode)
{
    FILE *file = fopen(filename, mode);
    if (!file && strcmp((const char *)mode, (const char *)"rb") == 0)
    {
        fprintf(stderr, "%s", "File read error.\n");
        return (struct file_with_status){.file = file, .status = OPEN_READ_ERROR};
    }
    if (!file && strcmp((const char *)mode, (const char *)"rb") == 0)
    {
        fprintf(stderr, "%s", "File write error\n");
        return (struct file_with_status){.file = file, .status = OPEN_WRITE_ERROR};
    }
    fprintf(stderr, "%s", "File is opened succesfully\n");
    return (struct file_with_status){.file = file, .status = OPEN_OK};
}

enum file_close_status file_close(FILE *file)
{
    if (!file)
    {
        fprintf(stderr, "%s", "File close error\n");
        return CLOSE_ERROR;
    }
    fclose(file);
    fprintf(stderr, "%s", "File is closed succesfully\n");
    return CLOSE_OK;
}
