#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{

    float change = 0;
    int dollar = 0;
    int coins = 0;

    // prompt input then convert dollars to cents
    do
    {
        change = get_float("Change owed: ");
    }
    while (change <= 0);

    dollar = round(change * 100);

    // subtracting with quarters
    while (dollar >= 25)
    {
        dollar = dollar - 25;
        coins++;
    }

    // subtracting with dimes
    while (dollar >= 10 && dollar < 25)
    {
        dollar = dollar - 10;
        coins++;
    }

    // subtracting with nickels
    while (dollar >= 5 && dollar < 10)
    {
        dollar = dollar - 5;
        coins++;
    }

    // subtracting with pennies
    while (dollar >= 1 && dollar < 5)
    {
        dollar = dollar - 1;
        coins++;
    }

    // print final amount of coins
    {
        printf("%i\n", coins);
    }

}
