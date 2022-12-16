#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //get the red, green, and blue values and calculate the average pixel values
    //for the individual values and use that average as the new values for all three colors.
    //need to use round int to accomadate for pixels that are not whole ints

    // step one: create two loops for loop through all the rows and columns of the image
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;
            
            // step two: calculate the average pixel
            int avg = round((red + green + blue)/3.0);
            
            // step three: set each color value to the average value
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //looping through 2d array
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++){
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            //calculations to get to sepia colors
            int sepiaRed = round((.393 * red) + (.769 * green) + (.189 * blue));
            int sepiaGreen = round((.349 * red) + (.686 * green) + (.168 * blue));
            int sepiaBlue = round((.272 * red) + (.534 * green) + (.131 * blue));
            
            //if over 255 revert to 255 
            if (sepiaRed > 255) {
                sepiaRed = 255;
            }
            if (sepiaBlue > 255) {
                sepiaBlue = 255;
            } 
            if (sepiaGreen > 255){
                sepiaGreen = 255;
            }
            
            //applying new color to all pixels
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //swap pixels horizontally opposite sides
    for (int i = 0; i <= height; i++){
    //i played around with the variables of whether int j should start at  -1  or not and kept running into errors where for some reason
    //the next line of at [i][0] would get pulled in and then it would go back to the previous line for the rest of the results
    //made me think: hey? maybe im going over which why I put int n = width-1 
    int n = width-1;
    int j = 0;
        //making n and j reach the halfway point to the full width so that they don't override each other
        //aka if width is 600 > each will have to reach 300 and will mirror the other at this halfway point
        //using the tmprcolor as a temporary variable to hold the needed numbers to make the subsitution (and repeats it for every RGB)
        while (n >= width/2 && j <= width/2) {
            int tmpred = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][n].rgbtRed;
            image[i][n].rgbtRed = tmpred;


            int tmpgreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][n].rgbtGreen;
            image[i][n].rgbtGreen = tmpgreen;

            int tmpblue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][n].rgbtBlue;
            image[i][n].rgbtBlue = tmpblue;
            
            n--;
            j++;
        }
    }
    return;
}

// Blur image
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //swap pixels horizontally opposite sides
    for (int i = 0; i <= height; i++){
    //i played around with the variables of whether int j should start at  -1  or not and kept running into errors where for some reason
    //the next line of at [i][0] would get pulled in and then it would go back to the previous line for the rest of the results
    //made me think: hey? maybe im going over which why I put int n = width-1
    int n = width-1;
    int j = 0;
        //making n and j reach the halfway point to the full width so that they don't override each other
        //aka if width is 600 > each will have to reach 300 and will mirror the other at this halfway point
        //using the tmprcolor as a temporary variable to hold the needed numbers to make the subsitution (and repeats it for every RGB)
        while (n >= width/2 && j <= width/2) {
            int tmpred = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][n].rgbtRed;
            image[i][n].rgbtRed = tmpred;

            //using the tmprcolor as a temporary variable to hold the needed numbers to make the subsitution (and repeats it for every RGB)
            int tmpgreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][n].rgbtGreen;
            image[i][n].rgbtGreen = tmpgreen;

            //using the tmprcolor as a temporary variable to hold the needed numbers to make the subsitution (and repeats it for every RGB)
            int tmpblue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][n].rgbtBlue;
            image[i][n].rgbtBlue = tmpblue;

            n--;
            j++;
        }
    }
    return;
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //this is the ugliest and longest if else statement i've ever written, apologies
    //im sure theres a better way of doing this but i could not think of one lol
    RGBTRIPLE copy[height][width];

    //create a copy of image[][]
    for (int i = 0; i < height;  i++){
        for (int j = 0; j < width; j++){
            //getting the values of the pixels within one row and one column from a specific pixel
            //get average of all pixels
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;

        }
    }
    //looping through copy
    for (int i = 0; i <  height; i++){
        for (int j = 0; j < width; j++){
            //case for the [0][0] to only retrieve the 4 around the pixel for RGB
            if (j == 0  && i == 0) {
                int red = copy[i][j].rgbtRed;
                red += copy[i+1][j+1].rgbtRed;
                red += copy[i][j+1].rgbtRed;
                red += copy[i+1][j].rgbtRed;

                int avgRed = round(red/4.0);
                image[i][j].rgbtRed = avgRed;

                int green = copy[i][j].rgbtGreen;
                green += copy[i+1][j+1].rgbtGreen;
                green += copy[i][j+1].rgbtGreen;
                green += copy[i+1][j].rgbtGreen;

                int avgGreen = round(green/4.0);
                image[i][j].rgbtGreen = avgGreen;


                int blue = copy[i][j].rgbtBlue;
                blue += copy[i+1][j+1].rgbtBlue;
                blue += copy[i][j+1].rgbtBlue;
                blue += copy[i+1][j].rgbtBlue;


                int avgBlue = round(blue/4.0);
                image[i][j].rgbtBlue = avgBlue;
            }
            //case for bottom left of the picture, to only get the 4 for each RGB
            else if(j == 0 && i == height-1){
                int red = copy[i][j].rgbtRed;
                red += copy[i][j+1].rgbtRed;
                red += copy[i-1][j].rgbtRed;
                red += copy[i-1][j+1].rgbtRed;

                int avgRed = round(red/4.0);
                image[i][j].rgbtRed = avgRed;

                int green = copy[i][j].rgbtGreen;
                green += copy[i][j+1].rgbtGreen;
                green += copy[i-1][j].rgbtGreen;
                green += copy[i-1][j+1].rgbtGreen;

                int avgGreen = round(green/4.0);
                image[i][j].rgbtGreen = avgGreen;

                int blue = copy[i][j].rgbtBlue;
                blue += copy[i][j+1].rgbtBlue;
                blue += copy[i-1][j].rgbtBlue;
                blue += copy[i-1][j+1].rgbtBlue;

                int avgBlue = round(blue/4.0);
                image[i][j].rgbtBlue = avgBlue;
            }
            //case for if the pixel is in the first column and i is not zero or max, to only get the six surrounding the pixel for RGB
            else if (j == 0 && i != height-1) {
                int red = copy[i][j].rgbtRed;
                red += copy[i-1][j+1].rgbtRed;
                red += copy[i][j+1].rgbtRed;
                red += copy[i+1][j+1].rgbtRed;
                red += copy[i+1][j].rgbtRed;
                red += copy[i-1][j].rgbtRed;

                int avgRed = round(red/6.0);
                image[i][j].rgbtRed = avgRed;

                int green = copy[i][j].rgbtGreen;
                green += copy[i-1][j+1].rgbtGreen;
                green += copy[i][j+1].rgbtGreen;
                green += copy[i+1][j+1].rgbtGreen;
                green += copy[i+1][j].rgbtGreen;
                green += copy[i-1][j].rgbtGreen;

                int avgGreen = round(green/6.0);
                image[i][j].rgbtGreen = avgGreen;
                int blue = copy[i][j].rgbtBlue;
                blue += copy[i-1][j+1].rgbtBlue;
                blue += copy[i][j+1].rgbtBlue;
                blue += copy[i+1][j+1].rgbtBlue;
                blue += copy[i+1][j].rgbtBlue;
                blue += copy[i-1][j].rgbtBlue;

                int avgBlue = round(blue/6.0);
                image[i][j].rgbtBlue = avgBlue;
            }
            //case for when the top rightmost pixel and getting the RGB of the 4 surrounding pixels
            else if(j == width-1 && i == 0){
                int red = copy[i][j].rgbtRed;
                red += copy[i+1][j].rgbtRed;
                red += copy[i][j-1].rgbtRed;
                red += copy[i+1][j-1].rgbtRed;

                int avgRed = round(red/4.0);
                image[i][j].rgbtRed = avgRed;


                int green = copy[i][j].rgbtGreen;
                green += copy[i+1][j].rgbtGreen;
                green += copy[i][j-1].rgbtGreen;
                green +=  copy[i+1][j-1].rgbtGreen;

                int avgGreen = round(green/4.0);
                image[i][j].rgbtGreen = avgGreen;

                int blue = copy[i][j].rgbtBlue;
                blue += copy[i+1][j].rgbtBlue;
                blue += copy[i][j-1].rgbtBlue;
                blue += copy[i+1][j-1].rgbtBlue;

                int avgBlue = round(blue/4.0);
                image[i][j].rgbtBlue = avgBlue;
            }
            //case for when bottom row of pixels, when i = height, but j is not 0 or the width-1, for each RGB to get the 6 surrounding pixels
            else if (j != width-1 && i == height-1){
                int red = copy[i][j].rgbtRed;
                red += copy[i][j+1].rgbtRed;
                red += copy[i][j-1].rgbtRed;
                red += copy[i-1][j+1].rgbtRed;
                red += copy[i-1][j].rgbtRed;
                red += copy[i-1][j-1].rgbtRed;

                int avgRed = round(red/6.0);
                image[i][j].rgbtRed = avgRed;

                int green = copy[i][j].rgbtGreen;
                green += copy[i][j+1].rgbtGreen;
                green += copy[i][j-1].rgbtGreen;
                green += copy[i-1][j+1].rgbtGreen;
                green += copy[i-1][j].rgbtGreen;
                green += copy[i-1][j-1].rgbtGreen;

                int avgGreen = round(green/6.0);
                image[i][j].rgbtGreen = avgGreen;
                int blue = copy[i][j].rgbtBlue;
                blue += copy[i][j+1].rgbtBlue;
                blue += copy[i][j-1].rgbtBlue;
                blue += copy[i-1][j+1].rgbtBlue;
                blue += copy[i-1][j].rgbtBlue;
                blue += copy[i-1][j-1].rgbtBlue;

                int avgBlue = round(blue/6.0);
                image[i][j].rgbtBlue = avgBlue;
            }
            //case for when the pixel is in the top row but not an edgecase, to get the six surrounding pixels for RGB
            else if(j != width-1 && i == 0) {
                int red = copy[i][j].rgbtRed;
                red += copy[i][j-1].rgbtRed;
                red += copy[i][j+1].rgbtRed;
                red += copy[i+1][j-1].rgbtRed;
                red += copy[i+1][j].rgbtRed;
                red += copy[i+1][j+1].rgbtRed;

                int avgRed = round(red/6.0);
                image[i][j].rgbtRed = avgRed;

                int green = copy[i][j].rgbtGreen;
                green += copy[i][j-1].rgbtGreen;
                green += copy[i][j+1].rgbtGreen;
                green += copy[i+1][j-1].rgbtGreen;
                green += copy[i+1][j].rgbtGreen;
                green += copy[i+1][j+1].rgbtGreen;

                int avgGreen = round(green/6.0);
                image[i][j].rgbtGreen = avgGreen;

                int blue = copy[i][j].rgbtBlue;
                blue += copy[i][j-1].rgbtBlue;
                blue += copy[i][j+1].rgbtBlue;
                blue += copy[i+1][j-1].rgbtBlue;
                blue += copy[i+1][j].rgbtBlue;
                blue += copy[i+1][j+1].rgbtBlue;

                int avgBlue = round(blue/6.0);
                image[i][j].rgbtBlue = avgBlue;
            }
            //case for when j is equal to width but i is not height or 0 to get the six surrounding pixels for RGB
            else if(j == width-1 && i != height-1) {
                int red = copy[i][j].rgbtRed;
                red += copy[i+1][j].rgbtRed;
                red += copy[i+1][j-1].rgbtRed;
                red += copy[i-1][j].rgbtRed;
                red += copy[i][j-1].rgbtRed;
                red += copy[i-1][j-1].rgbtRed;
                int avgRed = round(red/6.0);
                image[i][j].rgbtRed = avgRed;

                int green = copy[i][j].rgbtGreen;
                green += copy[i+1][j].rgbtGreen;
                green += copy[i+1][j-1].rgbtGreen;
                green += copy[i-1][j].rgbtGreen;
                green += copy[i][j-1].rgbtGreen;
                green += copy[i-1][j-1].rgbtGreen;

                int avgGreen = round(green/6.0);
                image[i][j].rgbtGreen = avgGreen;

                int blue = copy[i][j].rgbtBlue;
                blue += copy[i+1][j].rgbtBlue;
                blue += copy[i+1][j-1].rgbtBlue;
                blue += copy[i-1][j].rgbtBlue;
                blue += copy[i][j-1].rgbtBlue;
                blue += copy[i-1][j-1].rgbtBlue;

                int avgBlue = round(blue/6.0);
                image[i][j].rgbtBlue = avgBlue;

            }
            //case for when j is equal to width and i is equal to height (the bottom rightmost pixel), to only get the surrounding 4 pixels for RGB
            else if (j == width-1 && i == height-1){
                int red = copy[i][j].rgbtRed;
                red += copy[i-1][j].rgbtRed;
                red += copy[i-1][j-1].rgbtRed;
                red += copy[i][j-1].rgbtRed;

                int avgRed = round(red/4.0);
                image[i][j].rgbtRed = avgRed;

                int green = copy[i][j].rgbtGreen;
                green += copy[i-1][j].rgbtGreen;
                green += copy[i-1][j-1].rgbtGreen;
                green += copy[i][j-1].rgbtGreen;

                int avgGreen = round(green/4.0);
                image[i][j].rgbtGreen = avgGreen;
                int blue = copy[i][j].rgbtBlue;
                blue += copy[i-1][j].rgbtBlue;
                blue += copy[i-1][j-1].rgbtBlue;
                blue += copy[i][j-1].rgbtBlue;

                int avgBlue = round(blue/4.0);
                image[i][j].rgbtBlue = avgBlue;
            }
            //case for any other pixel that is not in a corner or in the top or bottom row (for example, a pixel in the dead center of the picture)
            //getting the surrounding 9 pixels for each RGB
            else if (j != width -1 && i != height) {
                int red = copy[i-1][j-1].rgbtRed;
                red += copy[i-1][j].rgbtRed;
                red += copy[i-1][j+1].rgbtRed;
                red += copy[i][j-1].rgbtRed;
                red += copy[i][j].rgbtRed;
                red += copy[i][j+1].rgbtRed;
                red += copy[i+1][j-1].rgbtRed;
                red += copy[i+1][j].rgbtRed;
                red += copy[i+1][j+1].rgbtRed;

                int avgRed = round(red/9.0);
                image[i][j].rgbtRed = avgRed;


                int green = copy[i-1][j-1].rgbtGreen;
                green += copy[i-1][j].rgbtGreen;
                green += copy[i-1][j+1].rgbtGreen;
                green += copy[i][j-1].rgbtGreen;
                green += copy[i][j].rgbtGreen;
                green += copy[i][j+1].rgbtGreen;
                green += copy[i+1][j-1].rgbtGreen;
                green += copy[i+1][j].rgbtGreen;
                green += copy[i+1][j+1].rgbtGreen;

                int avgGreen = round(green/9.0);
                image[i][j].rgbtGreen = avgGreen;


                int blue = copy[i-1][j-1].rgbtBlue;
                blue += copy[i-1][j].rgbtBlue;
                blue += copy[i-1][j+1].rgbtBlue;
                blue += copy[i][j-1].rgbtBlue;
                blue += copy[i][j].rgbtBlue;
                blue += copy[i][j+1].rgbtBlue;
                blue += copy[i+1][j-1].rgbtBlue;
                blue += copy[i+1][j].rgbtBlue;
                blue += copy[i+1][j+1].rgbtBlue;

                int avgBlue = round(blue/9.0);
                image[i][j].rgbtBlue = avgBlue;
            }

        }
    }
    return;
}

