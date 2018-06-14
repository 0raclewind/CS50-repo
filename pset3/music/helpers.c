// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // Check for a note length
    if (strncmp(fraction, "1/8", strlen(fraction)) == 0)    // One eigth
    {
        return 1;
    }
    else if (strncmp(fraction, "1/4", strlen(fraction)) == 0)   // Two eights
    {
        return 2;
    }
    else if (strncmp(fraction, "3/8", strlen(fraction)) == 0)   // Three eights
    {
        return 3;
    }
    else if (strncmp(fraction, "1/2", strlen(fraction)) == 0)   // Four eights
    {
        return 4;
    }
    else // return 8 eights if nothing else matches
    {
        return 8;
    }
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // Split note into separate variables
    double octave = 0.0;
    char accidental = 0;
    double freq = 0.0;

    // Check if note has accidental, calculate and set octave frequency
    // using formula 27.5 * (2^n)
    if (strlen(note) == 3)
    {
        octave = 27.5 * pow(2, atoi(&note[2]));
        accidental = note[1];
    }
    else
    {
        octave = 27.5 * pow(2, atoi(&note[1]));
    }

    // Semitone switch statement with conditional checks for 'b' or '#'
    // and calculates final frequency
    switch (note[0])
    {
        case 'C':
            if (accidental)
            {
                freq = octave / pow(2.0, 8.0 / 12.0);
            }
            else
            {
                freq = octave / pow(2.0, 9.0 / 12.0);
            }
            break;
        case 'D':
            if (accidental == 'b')
            {
                freq = octave / pow(2.0, 8.0 / 12.0);
            }
            else if (accidental == '#')
            {
                freq = octave / pow(2.0, 6.0 / 12.0);
            }
            else
            {
                freq = octave / pow(2.0, 7.0 / 12.0);
            }
            break;
        case 'E':
            if (accidental)
            {
                freq = octave / pow(2.0, 6.0 / 12.0);
            }
            else
            {
                freq = octave / pow(2.0, 5.0 / 12.0);
            }
            break;
        case 'F':
            if (accidental)
            {
                freq = octave / pow(2.0, 3.0 / 12.0);
            }
            else
            {
                freq = octave / pow(2.0, 4.0 / 12.0);
            }
            break;
        case 'G':
            if (accidental == 'b')
            {
                freq = octave / pow(2.0, 3.0 / 12.0);
            }
            else if (accidental == '#')
            {
                freq = octave / pow(2.0, 1.0 / 12.0);
            }
            else
            {
                freq = octave / pow(2.0, 2.0 / 12.0);
            }
            break;
        case 'A':
            if (accidental == 'b')
            {
                freq = octave / pow(2.0, 1.0 / 12.0);
            }
            else if (accidental == '#')
            {
                freq = octave * pow(2.0, 1.0 / 12.0);
            }
            else
            {
                freq = octave; // Initial semitone
            }
            break;
        case 'B':
            if (accidental)
            {
                freq = octave * pow(2.0, 1.0 / 12.0);
            }
            else
            {
                freq = octave * pow(2.0, 2.0 / 12.0);
            }
            break;

        default:
            return 0;
    }
    // Round and return final result
    int final_freq = round(freq);
    return final_freq;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // Return true if nothing in string
    if (strlen(s) == 0)
    {
        return true;
    }
    return false;
}
