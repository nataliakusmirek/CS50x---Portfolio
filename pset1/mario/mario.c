#include <cs50.h>
#include <stdio.h>

int num = 0;
int hash = 0;

int main(void)
{
    // Prompt user for height size
    int height;
    do
    {
        height = get_int("Height: ");
    }
    // Repeat prompt if size is less than 1 or greater than 8
    while (height > 8 || height < 1);

    for (int o = 0; o < height; o++)
    {
        for (int m = 0; m < height - o - 1; m++)
        {
            printf(" ");
        }

// Print right-side hashes
        for (int i = height - o; i <= height; i++)
        {

            printf("#");
        }

// Print space between pyramids

        printf("  ");

// Print right pyramid

        for (int i = height - o; i <= height; i++)
        {
            printf("#");
        }

        printf("\n");

    }
}
