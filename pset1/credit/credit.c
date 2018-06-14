#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Counts total digit count
int digit_count(long long n)
{
    if (n == 0)
    {
        return 0;
    }
    return 1 + digit_count(n / 10);
}

int main(void)
{
    long long cc_number = get_long_long("Enter CC #: ");
    int total_digits = digit_count(cc_number);
    int sum = 0;

    // Looping  throught first set of numbers, doubling them and adding to sum
    long first_division = 10;
    for (int i = 0; i < total_digits / 2; i++)
    {
        int current_number_doubled = ((cc_number / first_division) % 10) * 2;

        // If doubled number ends up being two digit number run another loop
        // which adds digits one by one
        if (current_number_doubled > 9)
        {
            int local_multiplier = 1;
            for (int j = 0; j < 2; j++)
            {
                sum += (current_number_doubled / local_multiplier) % 10;
                local_multiplier = 10;
            }
        }
        else
        {
            sum += current_number_doubled;
        }
        first_division *= 100;
    }

    // Run second loop which adds non multiplied digits to sum
    long second_division = 1;
    for (int i = 0; i < total_digits; i += 2)
    {
        int current_number = (cc_number / second_division) % 10;
        sum += current_number;
        second_division *= 100;
    }

    // Check for a first digit to determine whether it is a valid
    // American Express, MasterCard, or Visa card number
    int first_number = (long long)(cc_number / pow(10, total_digits - 1));
    int two_first_numbers = (long long)(cc_number / pow(10, total_digits - 2));

    // Validation check
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        // Vendor check
        if (two_first_numbers == 34 || two_first_numbers == 37)
        {
            printf("AMEX\n");
        }
        else if (two_first_numbers == 51 || two_first_numbers == 52 || two_first_numbers == 53 || two_first_numbers == 54
                 || two_first_numbers == 55)
        {
            printf("MASTERCARD\n");
        }
        else if (first_number == 4 && total_digits > 12)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}