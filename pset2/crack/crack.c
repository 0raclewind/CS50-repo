//
//      Password cracking program which are hashed with
//      DES algorithm.
//

#include <stdio.h>
#include <cs50.h>
#include <crypt.h>
#include <string.h>
#include <unistd.h>

int main(int argc, string argv[])
{
    // If more than one argument was passed terminate program
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    // Hash passed as argument
    string hash = argv[1];

    // Salt - first two characters of hash
    char salt[3];
    salt[0] = hash[0];
    salt[1] = hash[1];
    salt[2] = '\0';

    // Define and fill guess with \0
    char guess[6];
    for (int i = 1; i <= 5; i++)
    {
        guess[i] = '\0';
    }

    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";


    // Fift letter loop
    for (int i = 0; i < strlen(alphabet); i++)
    {
        // Fourth letter loop
        for (int j = 0; j < strlen(alphabet); j++)
        {
            // Third letter loop
            for (int k = 0; k < strlen(alphabet); k++)
            {
                // Second letter loop
                for (int l = 0; l < strlen(alphabet); l++)
                {
                    // First letter loop and check if correct
                    for (int m = 0; m < strlen(alphabet); m++)
                    {
                        guess[0] = alphabet[m];
                        string crypted = crypt(guess, salt);
                        // If correct display and quit
                        if (strcmp(hash, crypted) == 0)
                        {
                            printf("%s\n", guess);
                            return 0;
                        }
                    }
                    guess[1] = alphabet[l];
                }
                guess[2] = alphabet[k];
            }
            guess[3] = alphabet[j];
        }
        guess[4] = alphabet[i];
    }
}