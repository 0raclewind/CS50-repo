#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover infile.\n");
        return 1;
    }

    char *file = argv[1];

    // Open file for reading
    FILE *inptr = fopen(file, "r");

    // Open file for writing
    FILE *outptr = NULL;

    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", file);
        return 2;
    }

    // Initialize variables
    // Img count for dinamic filename
    int img_count = 0;

    // Opened file indicator
    int file_open = 0;

    // First match indicator
    int found = 0;
    while (!feof(inptr))
    {
        char block[512];

        fread(block, 512, 1, inptr);

        if (block[0] == '\xff' &&
            block[1] == '\xd8' &&
            block[2] == '\xff' &&
            (block[3] == '\xe0' || block[3] == '\xe1'))
        {
            if (file_open && found)
            {
                fclose(outptr);
                img_count++;
                file_open = 0;
            }
            found = 1;
        }

        if (!file_open && found)
        {
            char filename[8];
            snprintf(filename, 8, "%03d.jpg", img_count);
            outptr = fopen(filename, "w");
            fwrite(block, 512, 1, outptr);
            file_open = 1;
        }
        else if (file_open)
        {
            fwrite(block, 512, 1, outptr);
        }
    }

    fclose(outptr);
    fclose(inptr);
    return 0;
}