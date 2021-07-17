// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
//with experimentation found only 0.02 difference when N was from 100- 150000;
const unsigned int N = 100;

//Need a global count variable
int count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //need to make a lowercase copy of the word to hash
    int length = strlen(word);

    //copy is + 1 for \0
    char copy[length + 1];

    copy[length] = '\0';

    //copy into copy via to lower
    for (int i = 0; i < length; i++)
    {
        copy[i] = tolower(word[i]);
    }

    //hash copy index value
    int index = hash(copy);

    //access linked list where word originally went
    node *cursor = table[index];


    //loop over the linked list until end
    while (cursor != NULL)
    {
        //0 if copy and word in list match
        if (strcasecmp(cursor->word, copy) == 0)
        {
            return true;
        }
        else
        {
            //cursor moves along to next node of linked list
            cursor = cursor->next;
        }
    }

    //if no match
    return false;
}

// Hashes word to a number
// hash table source:  http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c = *word;

    while (c == *word++)
    {
        hash = ((hash << 5) + hash) + c;   /* hash * 33 + c */
    }

    // modified with this line to ensure return a value within table limits
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    //open dictionary
    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        return false;
    }

    //this allocates the required space for the word, a buffer
    char word[LENGTH + 1];


    //read string from pointer to file into 'word'
    while (fscanf(dict, "%s", word) != EOF)
    {

        //allocate memory for node
        node *wordnode = malloc(sizeof(node));

        if (wordnode == NULL)
        {
            fclose(dict);
            return false;
        }

        //copying from fscanf into the node
        strcpy(wordnode->word, word);

        wordnode->next = NULL;

        //passing the string to the hash function and hash index
        //No need tolower as all dict words are already lowercase
        int index = hash(word);

        // node points to the start of the particluar index, works if filled or empty
        wordnode->next = table[index];

        //THEN point index to node
        table[index] = wordnode;

        //add to the count as one word is added to list.
        count++;

    }

    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //this is why its a global variable.
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    //iterate over each index in table and free
    for (int i = 0; i < N; i++)
    {
        //points at the first index
        node *cursor = table[i];

        while (cursor != NULL)
        {
            //for each index, mark the start
            node *tmp = cursor;

            //move along to mark the next in list
            cursor = cursor->next;

            //then free the previous
            free(tmp);

            //cursor is moved along to next position in list and the loop repeats moving along linked list until NULL.

        }
    }

    return true;
}
