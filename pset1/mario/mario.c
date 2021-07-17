# include <cs50.h>
# include <stdio.h>


int main(void)
{
    //Variable creation
    int height;

    //Prompt user for height
    do
    {
        height = get_int("Height of pyramid (1-8): ");
    }

    //Keep prompting until height 1-8
    while (height < 1 || height > 8);


    //print accepted height
    //printf("%i\n", height);

    // New line loop tied to height
    for (int i = 0; i < height; i++)
    {
        //Right align by printing spaces, decreases with each line
        for (int j = height - 1; j > i; j--)
        {
            printf(" ");
        }

        //Print blocks, increases by one each new line.
        for (int j = 0; j <= i ; j++)
        {
            printf("#");

        }
        printf("\n");
    }
}
