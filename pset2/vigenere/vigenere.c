//
//          This is program that encrypts
//          messages using Vigenère’s cipher.
//

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Check for correct argument input
    if (argc != 2)
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }

    // Check for a digits in a password
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (argv[1][i] >= 48 && argv[1][i] <= 57)
        {
            printf("Usage: ./caesar k\n");
            exit(1);
        }
    }

    string input = get_string(" plaintext: ");
    printf("ciphertext: ");
    string pass = argv[1];
    int pass_iterator = 0;

    for (int i = 0; i < strlen(input); i++)
    {
        //Check if input is letter
        if (isalpha(input[i]))
        {
            // Make password letter uppercase and convert it to alphanumeric
            int encoder = toupper(pass[pass_iterator]) - 65;
            int letter = input[i];
            int new_char;

            // Make calculation in alphanumeric and convert back to ASCII
            if (islower(letter))
            {
                letter -= 97;
                new_char = ((letter + encoder) % 26) + 97;
            }
            else
            {
                letter -= 65;
                new_char = ((letter + encoder) % 26) + 65;
            }

            printf("%c", (char) new_char);

            // Increase password iterator by 1 if it reached the end
            if (pass_iterator >= strlen(pass) - 1)
            {
                pass_iterator = 0;
            }
            else
            {
                pass_iterator++;
            }
        }
        else
        {
            printf("%c", (char)input[i]);
        }
    }
    printf("\n");
}