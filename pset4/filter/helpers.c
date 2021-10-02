#include "helpers.h"
#include <math.h>
#include <cs50.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // used compare and copy and string notes from lecture 4 of cs50.
    for (int i = 0; i < height; i++)
    {
        for (int n = 0; n < width; n++)
        {
            int r = image[i][n].rgbtRed;
            int g = image[i][n].rgbtGreen;
            int b = image[i][n].rgbtBlue;

            float total = (round(r) + round(g) + round(b)) / 3;
            total = round(total);

            image[i][n].rgbtRed = total;
            image[i][n].rgbtGreen = total;
            image[i][n].rgbtBlue = total;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int n = 0; n < width; n++)
        {
            int originalRed = image[i][n].rgbtRed;
            int originalGreen = image[i][n].rgbtGreen;
            int originalBlue = image[i][n].rgbtBlue;

            // create red and cap value at 255
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            if (sepiaRed > 255)
            {
                // cap value
                sepiaRed = 255;
            }
            // create green and cap value at 255
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            if (sepiaGreen > 255)
            {
                // cap value
                sepiaGreen = 255;
            }
            // create blue and cap value at 255
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            if (sepiaBlue > 255)
            {
                // cap value
                sepiaBlue = 255;
            }

            image[i][n].rgbtRed = sepiaRed;
            image[i][n].rgbtGreen = sepiaGreen;
            image[i][n].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
// used compare and copy notes from lecture 4 to complete.
    int swap = width / 2;
    for (int i = 0; i < height; i++)
    {
        for (int n = 0; n < swap; n++)
        {
            RGBTRIPLE temp = image[i][n];
            image[i][n] = image[i][width - 1 - n];
            image[i][width - 1 - n] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int Red = 0;
    int Green = 0;
    int Blue = 0;
    int pixelcounter = 0;
    RGBTRIPLE Imagecopy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int n = 0; n < width; n++)
        {
            // 3x3 box!
            Imagecopy[i][n] = image[i][n];

            // check for values on the left side of the pixel
            if (n - 1 < width)
            {
                Red += image[i][n - 1].rgbtRed;
                Green += image[i][n - 1].rgbtGreen;
                Blue += image[i][n - 1].rgbtBlue;
                pixelcounter++;
            }
            // check for values on the right side of the pixel
            if (n + 1 < width)
            {
                Red += image[i][n + 1].rgbtRed;
                Green += image[i][n + 1].rgbtGreen;
                Blue += image[i][n + 1].rgbtBlue;
                pixelcounter++;
            }

            // check for values above the pixel
            if (i - 1 < height)
            {
                Red += image[i - 1][n].rgbtRed;
                Green += image[i - 1][n].rgbtGreen;
                Blue += image[i - 1][n].rgbtBlue;
                pixelcounter++;
            }
            // check for values under the pixel
            if (i + 1 < height)
            {
                Red += image[i + 1][n].rgbtRed;
                Green += image[i + 1][n].rgbtGreen;
                Blue += image[i + 1][n].rgbtBlue;
                pixelcounter++;
            }
            // check if there is a top left corner pixel
            if (i - 1 >= 0 && n - 1 < width)
            {
                Red += image[i - 1][n - 1].rgbtRed;
                Green += image[i - 1][n - 1].rgbtGreen;
                Blue += image[i - 1][n - 1].rgbtBlue;
                pixelcounter++;
            }
            // check if there is a top right corner pixel, go from the outside to the center pixel itself
            if (i - 1 >= 0 && n + 1 < width)
            {
                Red += image[i - 1][n + 1].rgbtRed;
                Green += image[i - 1][n + 1].rgbtGreen;
                Blue += image[i - 1][n + 1].rgbtBlue;
                pixelcounter++;
            }
            // check if there is a bottom right corner pixel
            if (i + 1 >= 0 && n + 1 < width)
            {
                Red += image[i + 1][n + 1].rgbtRed;
                Green += image[i + 1][n + 1].rgbtGreen;
                Blue += image[i + 1][n + 1].rgbtBlue;
                pixelcounter++;
            }
            // check if there is a bottom left corner pixel
            if (i + 1 >= 0 && n - 1 < width)
            {
                Red += image[i + 1][n - 1].rgbtRed;
                Green += image[i + 1][n - 1].rgbtGreen;
                Blue += image[i + 1][n - 1].rgbtBlue;
                pixelcounter++;
            }
            // add in the middle pixels values
            Red += image[i][n].rgbtRed;
            Green += image[i][n].rgbtGreen;
            Blue += image[i][n].rgbtBlue;
            pixelcounter++;

            // take the total colour value of the pixels and divide it by the counted number of pixels to get the average
            Imagecopy[i][n].rgbtRed = round(Red / pixelcounter);
            Imagecopy[i][n].rgbtGreen = round(Green / pixelcounter);
            Imagecopy[i][n].rgbtBlue = round(Blue / pixelcounter);

            // make sure the values are not over 255, that is the limit and it wont work if its over that value
            if (Imagecopy[i][n].rgbtRed > 255)
            {
                {
                    Imagecopy[i][n].rgbtRed = 255;
                }
                if (Imagecopy[i][n].rgbtGreen > 255)

                {
                    Imagecopy[i][n].rgbtGreen = 255;
                }
                if (Imagecopy[i][n].rgbtBlue > 255)
                {
                    Imagecopy[i][n].rgbtBlue = 255;
                }
            }

            // replace orignal image with the imagecopy that is blurred so it actually blurs the image
            for (int h = 0; h < height; h++)
            {
                for (int c = 0; c < width; c++)
                {
                    image[h][c].rgbtRed = Imagecopy[h][c].rgbtRed;
                    image[h][c].rgbtGreen = Imagecopy[h][c].rgbtGreen;
                    image[h][c].rgbtBlue = Imagecopy[h][c].rgbtBlue;
                }
            }
        }
    }
    return;
}