#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int d = -1; // Negative value needed not to reject first input request
    // Run until input is number 0 - 23
    while (d > 23 || d < 0)
    {
        d = get_int("Height: ");
    }

    // Main loop starting with 1 pieced step
    int steps = 1;
    for (int i = 0; i < d; i++)
    {
        int spaces = d - steps;
        // Spaces loop
        for (int m = 0; m < spaces; m++)
        {
            printf(" ");
        }

        // Hashes loop
        for (int n = 0; n < steps; n++)
        {
            printf("#");
        }

        printf("  ");

        // Alternate hashes loop
        for (int n = 0; n < steps; n++)
        {
            printf("#");
        }

        steps++;
        printf("\n");
    }
}