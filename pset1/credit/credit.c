// does not identify as card type, check math and variables
#include <cs50.h>
#include <stdio.h>
#include <string.h>
int main(void)
{
    long value = 0;
    long length = 0;
    long digit = 0;
    int total = 0;
    int i = 0;
    int j = 0;
    int n = 0;

    // prompt user for credit card number
    {
        value = get_long("Number: ");
    }

    // determine length of user's input
    length = value;
    while (length > 0)
    {
        length = length / 10;
        n++;
    }

    // luhn algorithm
    do
    {
        length = length % 10;
        i++;
    }
    while (length > 0);

    {
        length = length / 10;
        length = length % 10;
        j++;
    }

    {
        total = j + i;
        total = total % 10;
    }

   if (n != 13 && n != 15 && n != 16 && total != 0)
    {
        printf("INVALID\n");
    }

   digit = n;
   do
   {
      digit = digit / 10;
   }
   while (digit > 80);

   if (digit / 10 == 4)
    {
       printf("VISA\n");
    }
   else if ((digit / 10 == 3) && (digit % 10 == 4 || digit % 10 == 7))
   {
       printf("AMEX\n");
   }
   else if ((digit / 10 == 5) && (digit % 10 == 1 || digit % 10 == 2 || digit % 10 == 3 || digit % 10 == 4 || digit % 10 == 5))
   {
       printf("MASTERCARD\n");
   }

    return 0;
}