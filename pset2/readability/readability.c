#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

float index = 0, lettercount = 0, sentences = 0, wordcount = 1;
int grade = 0;

int main(void)
{
    string prompt = get_string("Text: ");

    for (int i = 0; i < strlen(prompt); i++)
    {
        if (prompt[i] >= 97 && prompt[i] <= 122)
        {
            lettercount++;
        }

        if (prompt[i] >= 65 && prompt[i] <= 90)
        {
            lettercount++;
        }
    }

    for (int i = 0; prompt[i] != '\0'; i++)
    {
        if (prompt[i] == ' ' && prompt[i + 1] != ' ')
        {
            wordcount++;
        }
    }
    for (int i = 0; prompt[i] != '\0'; i++)
    {
        if (prompt[i] == '.' || prompt[i] == '!' || prompt[i] == '?')
        {
            sentences++;
        }
    }

    // You might want to cast your one or more values to float before performing division when calculating L and S!

    {
        float L = (lettercount * 100) / (wordcount);
        float S = (sentences * 100) / (wordcount);
        index = 0.0588 * L - 0.296 * S - 15.8;
        grade = round(index);
    }

    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}


