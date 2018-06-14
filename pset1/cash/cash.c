#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int coinCount = 0;

    // Get floating number
    float f = -1.0;
    while (f < 0)
    {
        f = get_float("Change owed: ");
    }

    // Convert to cents
    int cents = round(f * 100);

    while (cents > 0)
    {
        // Check for quarters
        if (cents >= 25)
        {
            cents -= 25;
        }
        // Check for dimes
        else if (cents >= 10)
        {
            cents -= 10;
        }
        // Check for nickels
        else if (cents >= 5)
        {
            cents -= 5;
        }
        // Check for pennies
        else
        {
            cents -= 1;
        }
        coinCount++;
    }

    printf("%d\n", coinCount);
    return 0;
}