/*
*   This is text encoding machine
*   Usage: ./caesar k
*   k - positive integer
*/

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, string argv[])
{
    // Check for correct argument count
    if (argc != 2)
    {
        printf("Usage: ./caesar k\n");
        exit(1);
    }

    int number = (atoi(argv[1])) % 26;
    if (argc == 2 && number > 0)
    {
        string input = get_string("plaintext: ");
        printf("ciphertext: ");

        for (int i = 0; i < strlen(input); i++)
        {
            //Check if input is letter
            if ((input[i] >= 65 && input[i] <= 90) || (input[i] >= 97 && input[i] <= 122))
            {
                int new_char = input[i] + number;

                // If input character is uppercase letter
                if ((input[i] >= 65 && input[i] <= 90) && new_char > 90)
                {
                    new_char -= 26;
                }
                // If input character is uppercase letter
                else if ((input[i] >= 97 && input[i] <= 122) && new_char > 122)
                {
                    new_char -= 26;
                }
                printf("%c", (char)new_char);
            }
            else
            {
                printf("%c", (char)input[i]);
            }
        }
        printf("\n");
    }
    // If input is negative number
    else
    {
        printf("Positive integer argument is required.\n");
        printf("Terminating the program.\n");
    }
}