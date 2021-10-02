#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask user for their name
    string name = get_string("What is your name?\n");
   
    printf("Hello, %s\n", name);
}