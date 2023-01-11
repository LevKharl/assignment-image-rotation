#include "../include/bmp.h"
#include "../include/file.h"
#include "../include/rotation.h"

#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        return 1;
    }
    
    struct image source = from_bmp_check(argv[1]);
    if (!source.data)
    {
        image_destroy(&source);
        fprintf(stderr, "Bmp ---> image failed\n");
        return 1;
    }

    struct image rotated_img = rotate(source);
    image_destroy(&source);

    if (!rotated_img.data)
    {
        image_destroy(&rotated_img);
        fprintf(stderr, "Rotation failed\n");
        return 1;
    }

    to_bmp_check(&rotated_img, argv[2]);
    image_destroy(&rotated_img);

    return 0;
}
