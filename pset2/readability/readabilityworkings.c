#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

//float average(float word, float ls);
int count_letters (string s);
int count_words (string s);
int count_sentences (string s);
int get_index (float letters, float words, float sentences);

int main(void)
{   //prompt user for text
    string s = get_string("Text: ");

    //getting the counts
    float letters = count_letters(s);
    float words = count_words(s);
    float sentences = count_sentences(s);

    int grade = get_index(letters, words, sentences);

    //print the counts
    //printf("%i letter(s)\n %i word(s)\n %i sentence(s)\n", letters, words, sentences);
    //printf("%i", grade);

    //Printing results
    if (grade < 1)
    {
        printf("Before grade 1");
    }
    else if (grade > 16)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("Grade %i\n", grade);
    }


}
//new function
int count_letters (string s)
{
    int count = 0;

    for(int i = 0, n = strlen(s); i < n; i++)
    {
        //if an alphabetical symbol add to the count
        if(isalpha(s[i]))
        {
        count ++;
        }
    }
    return count;
}

//function to count the spaces/words in a string.
int count_words (string s)
{
    int count = 0;

    for(int i = 0, n = strlen(s); i < n; i++)
    {
        //this needs modification to account for the end of sentences (but can't just include./? because mrs.)
        //if a space is present in the string, add to the count.
        if(s[i] == ' ')
        {
            count++;
        }

    }
return count;
}

    //move on from words and do sentecnes before see walkthrough.

int count_sentences(string s)
{
    int count = 0;

    for(int i = 0, n = strlen(s); i < n; i++)
    {
        if(s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            count++;
        }
    }
return count;

}


int get_index (float letters, float words, float sentences)
{

//what i don't know is how to check against 100 words, this calculation needs fixing
//Is this inputting into the average function the right way around?- think it should be this way around
//is * by 100 right? No because I currently have letters divided by all words and i want it to be per 100 words.
//same for both letters and sentences?
    //float L = average(words, letters) * 100;
    //float S = average(words, sentences) * 100;

    float L = (letters / words) * 100;
    float S = (sentences / words) * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    //printf("%f", index);

    //this renaming is messy(but works for now)
    //int index2 = round(index);
//better rounding, does it need to be declared a int or is that done by the program outputting an int?
    return index= round(index);



}
//where length = words(total scores) and array= letters (each individual score)
//float average(float word , float ls)
//{
    //start at zero and add each score in the array together
  //  int sum = 0;
    //for( int i = 0; i < word; i++)
     //{
      //sum += ls;
     //}
 //once above done, take the total and divide it by the length/ TOTAL
// return sum/ (float) word;
//}

//somewhee my calculations are off, inputting into the average or * by 100 after?
//read through code to understand again then
//then watch walkthrough- I need, how to check it against 100 words not just the average of total words.

//problem is in the average calculation, from total wrds and total letters, time to watch walkthrough.