#include "helpers.h"
#include <math.h>

//typedef struct
//{
    //BYTE  rgbtBlue;
   // BYTE  rgbtGreen;
 //   BYTE  rgbtRed;
//} __attribute__((__packed__))
//RGBTRIPLE;




// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    //nested for loop to iterate over each height/ row.
    for (int i = 0; i < height; i ++)
    {
        //loop over the pixel within the row.
        for (int j = 0; j < width; j++)
        {
            double average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;

            //average needs to be an int so round
            int averageInt = round(average);

            //allocate average to the pixels
            image[i][j].rgbtBlue = averageInt;
            image[i][j].rgbtGreen = averageInt;
            image[i][j].rgbtRed = averageInt;

        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //nested for loop to iterate over each height/ row.
    for (int i = 0; i < height; i ++)
    {
        //loop over the pixel within the row.
        for (int j = 0; j < width; j++)
        {
            float sepiaRed = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            float sepiaGreen = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            float sepiaBlue = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;


            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

             if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

             if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            //allocate effect to the pixels

            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtBlue = round(sepiaBlue);

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //creating a variable to store the swapped pixels
    //otherwise by the time we get over half the width we are swappng the already swapped pixels, like a mirror in the middle
    RGBTRIPLE buffer;//[height][width];

    //nested for loop to iterate over each height/ row.
    for (int i = 0; i < height; i ++)
    {
        //loop over the pixel within the row, only need to do half the row as doing from both ends
        for (int j = 0; j < (width/2); j++)
        {

            //send the new pixel position to the buffer then later replace in the second nested for loops
            //buffer[i][j] = image[i][(width -1) - j];

            //store 'start' row in buffer
            buffer = image[i][j];
            //swap 'end' row position into 'start' position.
            image[i][j] = image[i][(width - 1) - j];
            //put the 'start' position into 'end' position.
            image[i][(width - 1) - j] = buffer;
            //can improve this by swapping the image, storing the original and swapping all in this single nested loop.. todo.

        }
    }

//below is the first way i did it by
    //looping again once buffer is complete
    //for (int i = 0; i < height; i ++)
    //{
        //loop over the pixel within the row.
      //  for (int j = 0; j < width; j++)
        //{
            //getting pixel position from the completed buffer.
          //  image[i][j] = buffer[i][j];

        //}
    //}

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //store original image pixel by pixel in a buffer;
            temp[i][j] = image[i][j];
        }
    }

    //again iterate row by pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            float red = 0;
            float green = 0;
            float blue = 0;
            float counter = 0;



            //iterate height and width -1 to +1 for each pixel
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {

                    //check if the pixel and its neightbour exists/ is valid, e.g. if i = 0 then with k -1 that is not in the image.
                    //same as above for a width/ j 0, l-1, also i height-1 + k+1 greater than height -1.
                    if (i + k < 0 || i + k > height -1)
                    {
                        continue;
                    }


                    if (j + l < 0 || j + l > width - 1 )
                    {
                        continue;
                    }

                    //add all the accepted pixels values and record it as a valid pixel in count;
                    red += temp[i + k][j + l].rgbtRed;
                    green += temp[i + k][j + l].rgbtGreen;
                    blue += temp[i + k][j + l].rgbtBlue;
                    counter++;

                }
            }

            image[i][j].rgbtRed = round(red / counter);
            image[i][j].rgbtGreen = round(green / counter);
            image[i][j].rgbtBlue = round(blue / counter);
        }
    }

    return;
}
