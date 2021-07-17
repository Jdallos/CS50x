// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    //type of size bytes, containing header_size spaces
    uint8_t header[HEADER_SIZE];

    //read into header, header_size/ 44, once, from input
    fread(header, HEADER_SIZE, 1, input);
    //write from header, a header_size amount to output.
    fwrite(header, HEADER_SIZE, 1, output);


    // TODO: Read samples from input file and write updated data to output file

    //create a 2 byte size type
    int16_t buffer;

    //loop over, reading into the address of buffer (needs to be address becuase don't know the full amount dealing with, unlike header_size)
    //reading at a size of 2 bytes, 1 at a time, from the input.
    //this goes on until the fread fails as it reaches the end, which is when it returns a 0, hence !=0
    //however apparently this is not needed to close the loop
    while (fread(&buffer, sizeof(int16_t), 1, input) != 0)
    {
        //multiply contents of the buffer by factor to adjust volume.
        buffer *= factor;

        //write now modified buffer contents to the output.
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);


}
