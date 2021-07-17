#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int main(int argc, string argv[])
{

    if (argc != 2 )
    {
        printf("Usage: ./ caesar key\n");
        return 1;
    }
    else
    {
        for(int i= 0, n = strlen(argv[1]); i < n; i ++)
        {
        if(!isdigit(argv[1][i]))
        {
        printf("Usage: ./ caesar key\n");
        return 1;
        }
        }
    }

    int key = atoi(argv[1]);

        //printf("Success\n");

    string plain = get_string("Plaintext:");

    //printf("ciphertext: ");

    for(int i = 0, n = strlen(plain); i < n; i++)
    {

        if(isupper(plain[i]))
            {
                plain[i] -= 65;
                plain[i] = (plain[i] + key) % 26;
                plain[i] += 65;
            //printf("%c", (((plain[i] - 65) + key) % 26) + 65);
            }
            else if(islower(plain[i]))
            {
                plain[i] -= 97;
                plain[i] = (plain[i] + key) % 26;
                plain[i] += 97;
            //printf("%c", (((plain[i] - 97) + key) % 26) + 97);
            }
            else
            {
            //printf("%c", plain[i]);
            }
    }


printf("%s", plain);
            //this worked with later printing s
            //plain[i] += 1;

            //this is where i need to do wrap around etc
           // printf("%c", plain[i] + key);


    //printf("\n");
        //earlier converted by c and then print as a whole
        //printf("%s\n", plain);

        //printf("%i\n", key);
}








    //propt plaintext
    //encipher by character U-U, u-u, ,-,
    //alpha = key, wrap around:
    //c[i] = (p[i] + K) % 26 (? =key?/ +1)
    //print cipher
