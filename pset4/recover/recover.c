#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
    //Force command argument selecting image to be recovered
    if (argc != 2)
    {
        printf("Usage: ./recover file.name");
        return 1;
    }

    //open the file and set to card
    FILE *card = fopen(argv[1], "r");

    //check was opened correctly
    if (card == NULL)
    {
        printf("Cannot read file.");
        return 1;
    }


    //create a buffer of 512 bytes
    uint8_t buffer[512];

    //for recovered images
    int count = 0;

    //file pointer to write images
    FILE *output = NULL;

    //to store the jpg names, could also be an array?
    char *s = malloc(8);


    //read the card into the buffer in 512 bytes.
    while (fread(buffer, sizeof(buffer), 1, card) == 1)
    {
        //checking for the header signs 4 bytes in a row.
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //so first match
            if (count == 0)
            {
                //allocating s, format specified, based up count.
                sprintf(s, "%03i.jpg", count);

                count++;

                //file output opening a write file called s
                output = fopen(s, "w");

                //write from buffer, a size of buffer, to file output
                fwrite(buffer, sizeof(buffer), 1, output);

                //complete this iteration of the loop and back to the while, othewise it goes to if statement below and closes this incomplete jpg
                continue;
            }

            if (count > 0)
            {
                //if found another match and not first time, close the previous jpg
                fclose(output);

                //and create a new one
                sprintf(s, "%03i.jpg", count);

                count++;

                output = fopen(s, "w");

                //check here?
                fwrite(buffer, sizeof(buffer), 1, output);
            }
        }

        else if (count > 0)
        {
            //once it has begun if not matching a new jpg, continue writing buffer into same filename.
            fwrite(buffer, sizeof(buffer), 1, output);
        }

    }

    fclose(card);
    fclose(output);

    free(s);

}