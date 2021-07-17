#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//Note function is taking command line arguments.
int main(int argc, string argv[])
{
    //must be 2 command line arguments = program name + another.
    if (argc != 2)
    {
        //error message
        printf("Usage: ./ caesar key\n");
        return 1;
    }
    else
    {
        //iterate over the length of the second command line argument.
        for (int i = 0, n = strlen(argv[1]); i < n; i ++)

        {
            //checking if each element in the array[1] is NOT a digit, if not then prints an error and ends programme by return 1.
            if (!isdigit(argv[1][i]))
            {
                printf("Usage: ./ caesar key\n");
                return 1;
            }
        }
    }
    //converts checked input to an integer.
    int key = atoi(argv[1]);


    //get text from user
    string plain = get_string("Plaintext:");


    //iterate over the total length of te text from user
    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        //uppercase A reduced to 0 and so on so formula works, the +65 to convert it back to ascii
        if (isupper(plain[i]))
        {
            plain[i] -= 65;
            plain[i] = (plain[i] + key) % 26;
            plain[i] += 65;
        }
        //lovwercase a reduced to 0 and so on so formula works, the +97 to convert it back to ascii
        else if (islower(plain[i]))
        {
            plain[i] -= 97;
            plain[i] = (plain[i] + key) % 26;
            plain[i] += 97;
        }

        //if not uppercase or lowercase then nothing happens and it is printed as is

    }

    //Arrays are not local, so the changes above carry over to the array and can be printed as a full string.
    printf("ciphertext: %s\n", plain);
}