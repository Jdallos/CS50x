#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

//prototype fuction list
int count_letters(string s);
int count_words(string s);
int count_sentences(string s);
int get_index(float letters, float words, float sentences);

int main(void)
{
    //prompt user for text
    string s = get_string("Text: ");

    //getting the counts and storing as floats
    float letters = count_letters(s);
    float words = count_words(s);
    float sentences = count_sentences(s);

    //entering counts into readability formula
    int grade = get_index(letters, words, sentences);


    //Printing results
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

//new function counting alphabetical symbols
int count_letters(string s)
{
    int count = 0;
    //loop based upon the length of the inputted string.
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        //if an alphabetical symbol add to the count
        if (isalpha(s[i]))
        {
            count ++;
        }
    }
    return count;
}

//function to count the spaces/words in a string with a plus 1.
int count_words(string s)
{
    int count = 0;

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        //this needs modification to account for the end of sentences (but can't just include./? because mrs.)
        //if a space is present in the string, add to the count.
        if (s[i] == ' ')
        {
            count++;
        }

    }
    return count + 1;
}

//function to count sentences by reference to .?!
int count_sentences(string s)
{
    int count = 0;

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            count++;
        }
    }
    return count;
}

//Function inputting to readability formula and then rounding to an interger
int get_index(float letters, float words, float sentences)
{

    float L = (letters / words) * 100;
    float S = (sentences / words) * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;


    return index = round(index);
}