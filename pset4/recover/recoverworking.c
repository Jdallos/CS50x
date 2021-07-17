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

    //repeat until end of card...
    //for (int a = 0; a < 50; a++)
    //{

    //create a buffer of 512 bytes
    //IS THIS THE CORRECT WAY TO CREATE BUFFER?
    uint8_t buffer[512];
    
    int counter = 0;

    //read the card into the buffer in 512 bytes.
    while (fread(buffer, sizeof(uint8_t), 512, card) == 1)

    //iterate over each byte in the buffer.
    //IS THIS NUMBER 512 RIGHT?
    for (int i = 0; i < 512 ; i++)
    {
        //bit wize arithmatic, just looking at the first four bits.
                    //hopefully this means it takes 0xe and ignores the final number.
                    //Want this as it could be one of 15 values.
                    //IS THIS THE CORRECT WAY TO GET WHAT I WANT TO HAPPEN HERE?
        //checking for the header signs 4 bytes in a row.
        if (buffer[i] == 0xff && buffer[i + 1] == 0xd8 && buffer[i + 2] == 0xff && (buffer[i + 3] & 0xf0) == 0xe0)
        {

                        //create a new file for storing the jpeg
                        //with a counter in the name so they are names correctly
                        int count = 0;

                        //sprintf prints to a string,%etc means 3 digits to represent the i, c is where the number would normally go.
                        //filename needs memory?
                        //see video 7.30
                        //IF FILENAME NEEDS TO STORE THE CREATED NAME, I HAVE ADDED ONE TO GIVE SPACE FOR THE \0 AT THE END OF 000.JPG
                        //suspect i need malloc here... check malloc
                        char *s = malloc(9);

                        if (s == NULL)
                        {
                            return 1;
                        }

                        sprintf(s, "%03i.jpg", count);

                        count++;



                        FILE *output = fopen(s, "w");
                        //8 mins, ready to write to the new file now.

                        fwrite(buffer, sizeof(uint8_t), 512, output);


                        //would be nice to put this at the end of the whole program.
                        free(s);








        }

    }
    //find the 3/4 byte(512) identifier of a new jpeg



}