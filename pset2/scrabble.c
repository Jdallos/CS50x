
#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

//Prototype
int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner, depending on scores
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}
//Score program taking word input
int compute_score(string word)
{
    //To keep track of the points
    int score = 0;

    //Loop to cycle through each letter of the word
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        //Function checks if character uppercase letter
        if (isupper(word[i]))
        {
            //We add to the score variable, the appropriate value from the POINTS array.
            //Calculated by taking the character of the word, and taking off the value (both a letter and an ascii number).
            //This drops a to 0 (the correct positon within the POINTS array), b to 1 so on and so on.
            score += POINTS[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            score += POINTS[word[i] - 'a'];
        }

    }
//need to output this score back to main function.
    return score;

}