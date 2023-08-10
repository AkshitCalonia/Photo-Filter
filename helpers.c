#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE dup[height][width];
    for (int i = 0; i<height; i++)
    {
        for (int j = width-1; j>=0; j--)
        {
            dup[i][width-j-1].rgbtRed = image[i][j].rgbtRed;
            dup[i][width-j-1].rgbtGreen = image[i][j].rgbtGreen;
            dup[i][width-j-1].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            image[i][j].rgbtRed = dup[i][j].rgbtRed;
            image[i][j].rgbtGreen = dup[i][j].rgbtGreen;
            image[i][j].rgbtBlue = dup[i][j].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE dup_b[height][width];

    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            //all corner cases
            if ((i == 0 && j == 0) || (i == 0 && j == width-1) || (i == height-1 && j == 0) || (i == height-1 && j == width-1))
            {
                //top left pixel
                if (i == 0 && j == 0)
                {
                    dup_b[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j+1].rgbtRed + image[i+1][j].rgbtRed)/4.0);
                    dup_b[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i+1][j].rgbtGreen)/4.0);
                    dup_b[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i+1][j].rgbtBlue)/4.0);
                }

                //top right pixel
                else if (i == 0 && j == width-1)
                {
                    dup_b[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed)/4.0);
                    dup_b[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen)/4.0);
                    dup_b[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue)/4.0);
                }

                //bottom left pixel
                else if (i == height-1 && j == 0)
                {
                    dup_b[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j+1].rgbtRed)/4.0);
                    dup_b[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j+1].rgbtGreen)/4.0);
                    dup_b[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j+1].rgbtBlue)/4.0);
                }

                //bottom right pixel
                else if (i == height-1 && j == width-1)
                {
                    dup_b[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j-1].rgbtRed + image[i][j-1].rgbtRed)/4.0);
                    dup_b[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i][j-1].rgbtGreen)/4.0);
                    dup_b[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i][j-1].rgbtBlue)/4.0);
                }
            }


            //all edge cases
            else if ((i == height-1) || (i == 0) || (j == width-1) || (j == 0))
            {
                if (i == height-1)
                {
                    dup_b[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j+1].rgbtRed)/6.0);
                    dup_b[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j+1].rgbtGreen)/6.0);
                    dup_b[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j+1].rgbtBlue)/6.0);
                }

                else if (i == 0)
                {
                    dup_b[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed + image[i][j+1].rgbtRed)/6.0);
                    dup_b[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i][j+1].rgbtGreen)/6.0);
                    dup_b[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i][j+1].rgbtBlue)/6.0);
                }

                else if (j == width-1)
                {
                    dup_b[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j-1].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed)/6.0);
                    dup_b[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen)/6.0);
                    dup_b[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue)/6.0);
                }
                else if (j == 0)
                {
                    dup_b[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j+1].rgbtRed + image[i+1][j].rgbtRed)/6.0);
                    dup_b[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i+1][j].rgbtGreen)/6.0);
                    dup_b[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i+1][j].rgbtBlue)/6.0);

                }
            }

            else
            // all in the middle (having 8 surrounding pixels)
            {
                dup_b[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed)/9.0);
                dup_b[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen)/9.0);
                dup_b[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue)/9.0);
            }
        }
    }

    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            image[i][j].rgbtRed = dup_b[i][j].rgbtRed;
            image[i][j].rgbtGreen = dup_b[i][j].rgbtGreen;
            image[i][j].rgbtBlue = dup_b[i][j].rgbtBlue;
        }
    }
    return;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE dup_e[height][width];

    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            //all corner cases
            if ((i == 0 && j == 0) || (i == 0 && j == width-1) || (i == height-1 && j == 0) || (i == height-1 && j == width-1))
            {
                //top left pixel
                if (i == 0 && j == 0)
                {
                    int gx_r = (2)*(image[i][j+1].rgbtRed) + (1)*(image[i+1][j+1].rgbtRed) + (0)*(image[i+1][j].rgbtRed);
                    int gy_r = (0)*(image[i][j+1].rgbtRed) + (1)*(image[i+1][j+1].rgbtRed) + (2)*(image[i+1][j].rgbtRed);
                    int ans_r = round(sqrt((gx_r*gx_r) + (gy_r*gy_r)));
                    if (ans_r>=255)
                    {
                        dup_e[i][j].rgbtRed = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtRed = ans_r;
                    }

                    int gx_g = (2)*(image[i][j+1].rgbtGreen) + (1)*(image[i+1][j+1].rgbtGreen) + (0)*(image[i+1][j].rgbtGreen);
                    int gy_g = (0)*(image[i][j+1].rgbtGreen) + (1)*(image[i+1][j+1].rgbtGreen) + (2)*(image[i+1][j].rgbtGreen);
                    int ans_g = round(sqrt((gx_g*gx_g) + (gy_g*gy_g)));
                    if (ans_g>=255)
                    {
                        dup_e[i][j].rgbtGreen = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtGreen = ans_g;
                    }

                    int gx_b = (2)*(image[i][j+1].rgbtBlue) + (1)*(image[i+1][j+1].rgbtBlue) + (0)*(image[i+1][j].rgbtBlue);
                    int gy_b = (0)*(image[i][j+1].rgbtBlue) + (1)*(image[i+1][j+1].rgbtBlue) + (2)*(image[i+1][j].rgbtBlue);
                    int ans_b = round(sqrt((gx_b*gx_b) + (gy_b*gy_b)));
                    if (ans_b>=255)
                    {
                        dup_e[i][j].rgbtBlue = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtBlue = ans_b;
                    }
                }

                //top right pixel
                else if (i == 0 && j == width-1)
                {
                    int gx_r = (-2)*(image[i][j-1].rgbtRed) + (-1)*(image[i+1][j-1].rgbtRed) + (0)*(image[i+1][j].rgbtRed);
                    int gy_r = (0)*(image[i][j-1].rgbtRed) + (1)*(image[i+1][j-1].rgbtRed) + (2)*(image[i+1][j].rgbtRed);
                    int ans_r = round(sqrt((gx_r*gx_r) + (gy_r*gy_r)));
                    if (ans_r>=255)
                    {
                        dup_e[i][j].rgbtRed = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtRed = ans_r;
                    }

                    int gx_g = (-2)*(image[i][j-1].rgbtGreen) + (-1)*(image[i+1][j-1].rgbtGreen) + (0)*(image[i+1][j].rgbtGreen);
                    int gy_g = (0)*(image[i][j-1].rgbtGreen) + (1)*(image[i+1][j-1].rgbtGreen) + (2)*(image[i+1][j].rgbtGreen);
                    int ans_g = round(sqrt((gx_g*gx_g) + (gy_g*gy_g)));
                    if (ans_g>=255)
                    {
                        dup_e[i][j].rgbtGreen = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtGreen = ans_g;
                    }

                    int gx_b = (-2)*(image[i][j-1].rgbtBlue) + (-1)*(image[i+1][j-1].rgbtBlue) + (0)*(image[i+1][j].rgbtBlue);
                    int gy_b = (0)*(image[i][j-1].rgbtBlue) + (1)*(image[i+1][j-1].rgbtBlue) + (2)*(image[i+1][j].rgbtBlue);
                    int ans_b = round(sqrt((gx_b*gx_b) + (gy_b*gy_b)));
                    if (ans_b>=255)
                    {
                        dup_e[i][j].rgbtBlue = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtBlue = ans_b;
                    }
                }

                //bottom left pixel
                else if (i == height-1 && j == 0)
                {
                    int gx_r = (2)*(image[i][j+1].rgbtRed) + (1)*(image[i-1][j+1].rgbtRed) + (0)*(image[i-1][j].rgbtRed);
                    int gy_r = (0)*(image[i][j+1].rgbtRed) + (-1)*(image[i-1][j+1].rgbtRed) + (-2)*(image[i-1][j].rgbtRed);
                    int ans_r = round(sqrt((gx_r*gx_r) + (gy_r*gy_r)));
                    if (ans_r>=255)
                    {
                        dup_e[i][j].rgbtRed = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtRed = ans_r;
                    }

                    int gx_g = (2)*(image[i][j+1].rgbtGreen) + (1)*(image[i-1][j+1].rgbtGreen) + (0)*(image[i-1][j].rgbtGreen);
                    int gy_g = (0)*(image[i][j+1].rgbtGreen) + (-1)*(image[i-1][j+1].rgbtGreen) + (-2)*(image[i-1][j].rgbtGreen);
                    int ans_g = round(sqrt((gx_g*gx_g) + (gy_g*gy_g)));
                    if (ans_g>=255)
                    {
                        dup_e[i][j].rgbtGreen = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtGreen = ans_g;
                    }

                    int gx_b = (2)*(image[i][j+1].rgbtBlue) + (1)*(image[i-1][j+1].rgbtBlue) + (0)*(image[i-1][j].rgbtBlue);
                    int gy_b = (0)*(image[i][j+1].rgbtBlue) + (-1)*(image[i-1][j+1].rgbtBlue) + (-2)*(image[i-1][j].rgbtBlue);
                    int ans_b = round(sqrt((gx_b*gx_b) + (gy_b*gy_b)));
                    if (ans_b>=255)
                    {
                        dup_e[i][j].rgbtBlue = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtBlue = ans_b;
                    }
                }

                //bottom right pixel
                else if (i == height-1 && j == width-1)
                {
                    int gx_r = (-2)*(image[i][j-1].rgbtRed) + (-1)*(image[i-1][j-1].rgbtRed) + (0)*(image[i-1][j].rgbtRed);
                    int gy_r = (0)*(image[i][j-1].rgbtRed) + (-1)*(image[i-1][j-1].rgbtRed) + (-2)*(image[i-1][j].rgbtRed);
                    int ans_r = round(sqrt((gx_r*gx_r) + (gy_r*gy_r)));
                    if (ans_r>=255)
                    {
                        dup_e[i][j].rgbtRed = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtRed = ans_r;
                    }

                    int gx_g = (-2)*(image[i][j-1].rgbtGreen) + (-1)*(image[i-1][j-1].rgbtGreen) + (0)*(image[i-1][j].rgbtGreen);
                    int gy_g = (0)*(image[i][j-1].rgbtGreen) + (-1)*(image[i-1][j-1].rgbtGreen) + (-2)*(image[i-1][j].rgbtGreen);
                    int ans_g = round(sqrt((gx_g*gx_g) + (gy_g*gy_g)));
                    if (ans_g>=255)
                    {
                        dup_e[i][j].rgbtGreen = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtGreen = ans_g;
                    }

                    int gx_b = (-2)*(image[i][j-1].rgbtBlue) + (-1)*(image[i-1][j-1].rgbtBlue) + (0)*(image[i-1][j].rgbtBlue);
                    int gy_b = (0)*(image[i][j-1].rgbtBlue) + (-1)*(image[i-1][j-1].rgbtBlue) + (-2)*(image[i-1][j].rgbtBlue);
                    int ans_b = round(sqrt((gx_b*gx_b) + (gy_b*gy_b)));
                    if (ans_b>=255)
                    {
                        dup_e[i][j].rgbtBlue = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtBlue = ans_b;
                    }
                }
            }


            //all edge cases
            else if ((i == height-1) || (i == 0) || (j == width-1) || (j == 0))
            {
                if (i == height-1)
                {
                    int gx_r = (-2)*(image[i][j-1].rgbtRed) + (-1)*(image[i-1][j-1].rgbtRed) + (0)*(image[i-1][j].rgbtRed) + (1)*(image[i-1][j+1].rgbtRed) + (2)*(image[i][j+1].rgbtRed);
                    int gy_r = (0)*(image[i][j-1].rgbtRed) + (-1)*(image[i-1][j-1].rgbtRed) + (-2)*(image[i-1][j].rgbtRed) + (-1)*(image[i-1][j+1].rgbtRed) + (0)*(image[i][j+1].rgbtRed);
                    int ans_r = round(sqrt((gx_r*gx_r) + (gy_r*gy_r)));
                    if (ans_r>=255)
                    {
                        dup_e[i][j].rgbtRed = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtRed = ans_r;
                    }

                    int gx_g = (-2)*(image[i][j-1].rgbtGreen) + (-1)*(image[i-1][j-1].rgbtGreen) + (0)*(image[i-1][j].rgbtGreen) + (1)*(image[i-1][j+1].rgbtGreen) + (2)*(image[i][j+1].rgbtGreen);
                    int gy_g = (0)*(image[i][j-1].rgbtGreen) + (-1)*(image[i-1][j-1].rgbtGreen) + (-2)*(image[i-1][j].rgbtGreen) + (-1)*(image[i-1][j+1].rgbtGreen) + (0)*(image[i][j+1].rgbtGreen);
                    int ans_g = round(sqrt((gx_g*gx_g) + (gy_g*gy_g)));
                    if (ans_g>=255)
                    {
                        dup_e[i][j].rgbtGreen = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtGreen = ans_g;
                    }

                    int gx_b = (-2)*(image[i][j-1].rgbtBlue) + (-1)*(image[i-1][j-1].rgbtBlue) + (0)*(image[i-1][j].rgbtBlue) + (1)*(image[i-1][j+1].rgbtBlue) + (2)*(image[i][j+1].rgbtBlue);
                    int gy_b = (0)*(image[i][j-1].rgbtBlue) + (-1)*(image[i-1][j-1].rgbtBlue) + (-2)*(image[i-1][j].rgbtBlue) + (-1)*(image[i-1][j+1].rgbtBlue) + (0)*(image[i][j+1].rgbtBlue);
                    int ans_b = round(sqrt((gx_b*gx_b) + (gy_b*gy_b)));
                    if (ans_b>=255)
                    {
                        dup_e[i][j].rgbtBlue = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtBlue = ans_b;
                    }
                }

                else if (i == 0)
                {
                    int gx_r = (-2)*(image[i][j-1].rgbtRed) + (-1)*(image[i+1][j-1].rgbtRed) + (0)*(image[i+1][j].rgbtRed) + (1)*(image[i+1][j+1].rgbtRed) + (2)*(image[i][j+1].rgbtRed);
                    int gy_r = (0)*(image[i][j-1].rgbtRed) + (1)*(image[i+1][j-1].rgbtRed) + (2)*(image[i+1][j].rgbtRed) + (1)*(image[i+1][j+1].rgbtRed) + (0)*(image[i][j+1].rgbtRed);
                    int ans_r = round(sqrt((gx_r*gx_r) + (gy_r*gy_r)));
                    if (ans_r>=255)
                    {
                        dup_e[i][j].rgbtRed = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtRed = ans_r;
                    }

                    int gx_g = (-2)*(image[i][j-1].rgbtGreen) + (-1)*(image[i+1][j-1].rgbtGreen) + (0)*(image[i+1][j].rgbtGreen) + (1)*(image[i+1][j+1].rgbtGreen) + (2)*(image[i][j+1].rgbtGreen);
                    int gy_g = (0)*(image[i][j-1].rgbtGreen) + (1)*(image[i+1][j-1].rgbtGreen) + (2)*(image[i+1][j].rgbtGreen) + (1)*(image[i+1][j+1].rgbtGreen) + (0)*(image[i][j+1].rgbtGreen);
                    int ans_g = round(sqrt((gx_g*gx_g) + (gy_g*gy_g)));
                    if (ans_g>=255)
                    {
                        dup_e[i][j].rgbtGreen = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtGreen = ans_g;
                    }

                    int gx_b = (-2)*(image[i][j-1].rgbtBlue) + (-1)*(image[i+1][j-1].rgbtBlue) + (0)*(image[i+1][j].rgbtBlue) + (1)*(image[i+1][j+1].rgbtBlue) + (2)*(image[i][j+1].rgbtBlue);
                    int gy_b = (0)*(image[i][j-1].rgbtBlue) + (1)*(image[i+1][j-1].rgbtBlue) + (2)*(image[i+1][j].rgbtBlue) + (1)*(image[i+1][j+1].rgbtBlue) + (0)*(image[i][j+1].rgbtBlue);
                    int ans_b = round(sqrt((gx_b*gx_b) + (gy_b*gy_b)));
                    if (ans_b>=255)
                    {
                        dup_e[i][j].rgbtBlue = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtBlue = ans_b;
                    }
                }

                else if (j == width-1)
                {
                    int gx_r = (0)*(image[i-1][j].rgbtRed) + (-1)*(image[i-1][j-1].rgbtRed) + (-2)*(image[i][j-1].rgbtRed) + (-1)*(image[i+1][j-1].rgbtRed) + (0)*(image[i+1][j].rgbtRed);
                    int gy_r = (-2)*(image[i-1][j].rgbtRed) + (-1)*(image[i-1][j-1].rgbtRed) + (0)*(image[i][j-1].rgbtRed) + (1)*(image[i+1][j-1].rgbtRed) + (2)*(image[i+1][j].rgbtRed);
                    int ans_r = round(sqrt((gx_r*gx_r) + (gy_r*gy_r)));
                    if (ans_r>=255)
                    {
                        dup_e[i][j].rgbtRed = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtRed = ans_r;
                    }

                    int gx_g = (0)*(image[i-1][j].rgbtGreen) + (-1)*(image[i-1][j-1].rgbtGreen) + (-2)*(image[i][j-1].rgbtGreen) + (-1)*(image[i+1][j-1].rgbtGreen) + (0)*(image[i+1][j].rgbtGreen);
                    int gy_g = (-2)*(image[i-1][j].rgbtGreen) + (-1)*(image[i-1][j-1].rgbtGreen) + (0)*(image[i][j-1].rgbtGreen) + (1)*(image[i+1][j-1].rgbtGreen) + (2)*(image[i+1][j].rgbtGreen);
                    int ans_g = round(sqrt((gx_g*gx_g) + (gy_g*gy_g)));
                    if (ans_g>=255)
                    {
                        dup_e[i][j].rgbtGreen = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtGreen = ans_g;
                    }

                    int gx_b = (0)*(image[i-1][j].rgbtBlue) + (-1)*(image[i-1][j-1].rgbtBlue) + (-2)*(image[i][j-1].rgbtBlue) + (-1)*(image[i+1][j-1].rgbtBlue) + (0)*(image[i+1][j].rgbtBlue);
                    int gy_b = (-2)*(image[i-1][j].rgbtBlue) + (-1)*(image[i-1][j-1].rgbtBlue) + (0)*(image[i][j-1].rgbtBlue) + (1)*(image[i+1][j-1].rgbtBlue) + (2)*(image[i+1][j].rgbtBlue);
                    int ans_b = round(sqrt((gx_b*gx_b) + (gy_b*gy_b)));
                    if (ans_b>=255)
                    {
                        dup_e[i][j].rgbtBlue = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtBlue = ans_b;
                    }

                }
                else if (j == 0)
                {
                    int gx_r = (0)*(image[i-1][j].rgbtRed) + (1)*(image[i-1][j+1].rgbtRed) + (2)*(image[i][j+1].rgbtRed) + (1)*(image[i+1][j+1].rgbtRed) + (0)*(image[i+1][j].rgbtRed);
                    int gy_r = (-2)*(image[i-1][j].rgbtRed) + (-1)*(image[i-1][j+1].rgbtRed) + (0)*(image[i][j+1].rgbtRed) + (1)*(image[i+1][j+1].rgbtRed) + (2)*(image[i+1][j].rgbtRed);
                    int ans_r = round(sqrt((gx_r*gx_r) + (gy_r*gy_r)));
                    if (ans_r>=255)
                    {
                        dup_e[i][j].rgbtRed = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtRed = ans_r;
                    }

                    int gx_g = (0)*(image[i-1][j].rgbtGreen) + (1)*(image[i-1][j+1].rgbtGreen) + (2)*(image[i][j+1].rgbtGreen) + (1)*(image[i+1][j+1].rgbtGreen) + (0)*(image[i+1][j].rgbtGreen);
                    int gy_g = (-2)*(image[i-1][j].rgbtGreen) + (-1)*(image[i-1][j+1].rgbtGreen) + (0)*(image[i][j+1].rgbtGreen) + (1)*(image[i+1][j+1].rgbtGreen) + (2)*(image[i+1][j].rgbtGreen);
                    int ans_g = round(sqrt((gx_g*gx_g) + (gy_g*gy_g)));
                    if (ans_g>=255)
                    {
                        dup_e[i][j].rgbtGreen = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtGreen = ans_g;
                    }

                    int gx_b = (0)*(image[i-1][j].rgbtBlue) + (1)*(image[i-1][j+1].rgbtBlue) + (2)*(image[i][j+1].rgbtBlue) + (1)*(image[i+1][j+1].rgbtBlue) + (0)*(image[i+1][j].rgbtBlue);
                    int gy_b = (-2)*(image[i-1][j].rgbtBlue) + (-1)*(image[i-1][j+1].rgbtBlue) + (0)*(image[i][j+1].rgbtBlue) + (1)*(image[i+1][j+1].rgbtBlue) + (2)*(image[i+1][j].rgbtBlue);
                    int ans_b = round(sqrt((gx_b*gx_b) + (gy_b*gy_b)));
                    if (ans_b>=255)
                    {
                        dup_e[i][j].rgbtBlue = 255;
                    }
                    else
                    {
                        dup_e[i][j].rgbtBlue = ans_b;
                    }

                }
            }

            // all in the middle (having 8 surrounding pixels)
            else
            {
                int gx_r = (-1)*(image[i-1][j-1].rgbtRed) + 0*(image[i-1][j].rgbtRed) + 1*(image[i-1][j+1].rgbtRed) - (2)*(image[i][j-1].rgbtRed) + 2*(image[i][j+1].rgbtRed) - 1*(image[i+1][j-1].rgbtRed) + 0*(image[i+1][j].rgbtRed) + 1*(image[i+1][j+1].rgbtRed);
                int gy_r = (-1)*(image[i-1][j-1].rgbtRed) - 2*(image[i-1][j].rgbtRed) - 1*(image[i-1][j+1].rgbtRed) - (0)*(image[i][j-1].rgbtRed) + 0*(image[i][j+1].rgbtRed) + 1*(image[i+1][j-1].rgbtRed) + 2*(image[i+1][j].rgbtRed) + 1*(image[i+1][j+1].rgbtRed);
                int ans_r = round(sqrt((gx_r*gx_r) + (gy_r*gy_r)));
                if (ans_r>=255)
                {
                    dup_e[i][j].rgbtRed = 255;
                }
                else
                {
                    dup_e[i][j].rgbtRed = ans_r;
                }

                int gx_g = (-1)*(image[i-1][j-1].rgbtGreen) + 0*(image[i-1][j].rgbtGreen) + 1*(image[i-1][j+1].rgbtGreen) - (2)*(image[i][j-1].rgbtGreen) + 2*(image[i][j+1].rgbtGreen) - 1*(image[i+1][j-1].rgbtGreen) + 0*(image[i+1][j].rgbtGreen) + 1*(image[i+1][j+1].rgbtGreen);
                int gy_g = (-1)*(image[i-1][j-1].rgbtGreen) - 2*(image[i-1][j].rgbtGreen) - 1*(image[i-1][j+1].rgbtGreen) - (0)*(image[i][j-1].rgbtGreen) + 0*(image[i][j+1].rgbtGreen) + 1*(image[i+1][j-1].rgbtGreen) + 2*(image[i+1][j].rgbtGreen) + 1*(image[i+1][j+1].rgbtGreen);
                int ans_g = round(sqrt((gx_g*gx_g) + (gy_g*gy_g)));
                if (ans_g>=255)
                {
                    dup_e[i][j].rgbtGreen = 255;
                }
                else
                {
                    dup_e[i][j].rgbtGreen = ans_g;
                }

                int gx_b = (-1)*(image[i-1][j-1].rgbtBlue) + 0*(image[i-1][j].rgbtBlue) + 1*(image[i-1][j+1].rgbtBlue) - (2)*(image[i][j-1].rgbtBlue) + 2*(image[i][j+1].rgbtBlue) - 1*(image[i+1][j-1].rgbtBlue) + 0*(image[i+1][j].rgbtBlue) + 1*(image[i+1][j+1].rgbtBlue);
                int gy_b = (-1)*(image[i-1][j-1].rgbtBlue) - 2*(image[i-1][j].rgbtBlue) - 1*(image[i-1][j+1].rgbtBlue) - (0)*(image[i][j-1].rgbtBlue) + 0*(image[i][j+1].rgbtBlue) + 1*(image[i+1][j-1].rgbtBlue) + 2*(image[i+1][j].rgbtBlue) + 1*(image[i+1][j+1].rgbtBlue);
                int ans_b = round(sqrt((gx_b*gx_b) + (gy_b*gy_b)));
                if (ans_b>=255)
                {
                    dup_e[i][j].rgbtBlue = 255;
                }
                else
                {
                    dup_e[i][j].rgbtBlue = ans_b;
                }
            }
        }
    }
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            image[i][j].rgbtRed = dup_e[i][j].rgbtRed;
            image[i][j].rgbtGreen = dup_e[i][j].rgbtGreen;
            image[i][j].rgbtBlue = dup_e[i][j].rgbtBlue;
        }
    }

    return;
}
