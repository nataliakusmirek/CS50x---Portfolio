#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
// notes::
// w = writing permissions
// r = reading permissions

#define BUFFER_SIZE 512
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // open memory card check return value of fopen

    FILE *raw = fopen("card.raw", "r");
    if (raw == NULL)
    {
        printf("Forensic image cannot be opened for reading.\n");
        return 1;
    }
    unsigned char buffer[BUFFER_SIZE];
    FILE *img = NULL;
    int jpeg = 0;
    int value = 0;
    // while loop if (buffer...) is from medium.com -> the values of 0xff..etc.
    while (fread(buffer, BUFFER_SIZE, 1, raw) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 &&
            buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (jpeg == 1)
            {
                fclose(img);
            }
            else
            {
                jpeg = 1;
            }
            char filename[8];
            sprintf(filename, "%03i.jpg", value);
            img = fopen(filename, "a");
            value++;

        }
        if (jpeg == 1)
        {
            fwrite(&buffer, BUFFER_SIZE, 1, img);
        }

    }
    fclose(raw);
    fclose(img);


    return 0;
}
