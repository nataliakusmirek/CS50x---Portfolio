#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// make variable that stores the keyed cycled version of input and prints that somehow, VARIABLE MUST BE A STRING
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    {
        int key = atoi(argv[1]);
        string plaintext = get_string("plaintext: ");
        printf("ciphertext: ");

        int length = strlen(plaintext);
        for (int i = 0; i < length; i++)
        {
            if (isalpha(plaintext[i]))
            {
                if (islower(plaintext[i]))
                {
                    printf("%c", ((((plaintext[i] + key) - 97) % 26) + 97));
                }
                if (isupper(plaintext[i]))
                {
                    printf("%c", ((((plaintext[i] + key) - 65) % 26) + 65));
                }
            }
            else
                // if not a letter, (maybe punctuation,etc) do not rotate, leave as is
            {
                printf("%c", plaintext[i]);
            }
        }
        printf("\n");
        return 0;

    }

}
