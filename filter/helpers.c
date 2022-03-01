#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
            
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int new_red = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int new_green = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int new_blue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            
            if (new_red > 255)
            {
                new_red = 255;
            }
            
            if (new_blue > 255)
            {
                new_blue = 255;
            }
            
            if (new_green > 255)
            {
                new_green = 255;
            }
            
            image[i][j].rgbtBlue = new_blue;
            image[i][j].rgbtGreen = new_green;
            image[i][j].rgbtRed = new_red;
            
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width-j-1];
            image[i][width-j-1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //count how many neighbour pixels
            int neighbour_pixels = 0;
            double new_rgbtRed = 0;
            double new_rgbtGreen = 0;
            double new_rgbtBlue = 0;
            
            //loop through 3x3 grid
            for (int k = i-1; k <= i+1; k++)
            {
                for (int l = j-1; l <= j+1; l++)
                {
                    if (k >= 0 && k < height && l >= 0 && l < width)
                    {
                        neighbour_pixels++;
                        new_rgbtRed += image[k][l].rgbtRed;
                        new_rgbtGreen += image[k][l].rgbtGreen;
                        new_rgbtBlue += image[k][l].rgbtBlue;
                    }
                }
            }
            
            new_rgbtRed = round(1.0 * new_rgbtRed / neighbour_pixels);
            new_rgbtGreen = round(1.0 * new_rgbtGreen / neighbour_pixels);
            new_rgbtBlue = round(1.0 * new_rgbtBlue / neighbour_pixels);
            
            //create new image with blurred pixels
            new_image[i][j].rgbtRed = new_rgbtRed;
            new_image[i][j].rgbtGreen = new_rgbtGreen;
            new_image[i][j].rgbtBlue = new_rgbtBlue;
            
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //update image using new image with blurred pixels
            image[i][j] = new_image[i][j];
        }
    }
    return;
}
