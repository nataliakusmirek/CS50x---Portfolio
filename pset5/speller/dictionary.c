// Implements a dictionary's functionality
#include <stdbool.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
// Number of buckets in hash table
const unsigned int N = 3000;

// Hash table
node *table[N];
int size_of_n = 0;
node *n;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int value;
    value = hash(word);
    n = table[value];

    // if n is not null, compare the word to the words in the dictionary
    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        n = n->next;
        // checks next word
    }
    return false;
}
// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned int number = 0;
    // if word has actual letters then we hash them, if they do not (punctuation, etc)
    // we leave it as 0 so it is not changed.
    if (toupper(word[0]) >= 65 && toupper(word[0]) <= 90)
    {
        // hash by alphabetical order, use ASCII chart to find difference value
        number = (toupper(word[0]) - 64);
    }
    else
    {
        number = 0;
    }
    return number;
}
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char *word = 0;
    unsigned int number;

    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char sub[LENGTH + 1];
    while (fscanf(file, "%s", sub) != EOF)
    {
        node *extra = malloc(sizeof(node));
        if (extra == NULL)
        {
            return false;
        }
        strcpy(extra -> word, sub);
        extra -> next = NULL;
        int index = hash(sub);

        if (table[index] == NULL)
        {
            table[index] = extra;
        }
        else
        {
            extra -> next = table[index];
            table[index] = extra;
        }
        size_of_n++;
    }
    fclose(file);
    return true;

}
// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return size_of_n;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *z;
    for (int i = 0; i < N; i++)
    {
        z = table[i];
    }
    if (z != NULL)
    {
        // unload
        node *extra = z;
        n->next = z;
        free(extra);
    }
    else
    {
        return true;
    }
    return false;
}
