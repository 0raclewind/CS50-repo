// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Define trie node
typedef struct node
{
    struct node *children[27];
    bool word_end;
}
node;

// Word count
unsigned int word_count = 0;


int index_char(char c);
node *create_node();
void unload_node(node *n);

// Root node
node *root;


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *current_node = root;

    for (int i = 0; strlen(word) > i; i++)
    {
        int index = index_char(word[i]);

        if (current_node -> children[index] == NULL)
        {
            return false;
        }

        current_node = current_node -> children[index];
    }
    return current_node -> word_end;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    word_count = 0;

    // Open dictionary file
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        return false;
    }

    // Get dictionary size
    fseek(fp, 0, SEEK_END);
    unsigned int file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // Load entire dictionary to buffer
    char *buffer = malloc(file_size + 1);
    if (buffer == NULL)
    {
        fclose(fp);
        return false;
    }

    fread(buffer, file_size, 1, fp);
    fclose(fp);

    // NULL termination of buffer
    buffer[file_size] = '\0';

    // Create TRIE node
    root = create_node();
    if (root == NULL)
    {
        free(buffer);
        return false;
    }

    node *current_node = root;

    // Iterate over characters
    for (int i = 0; i < file_size; i++)
    {
        // Word end
        if (buffer[i] == '\n')
        {
            current_node -> word_end = true;
            current_node = root;
            word_count++;
            continue;
        }

        int index = index_char(buffer[i]);

        // Check if node is NULL
        if (current_node -> children[index] == NULL)
        {
            current_node -> children[index] = create_node();

            // If node is still NULL, malloc must've failed
            if (current_node -> children[index] == NULL)
            {
                printf("malloc FAILED");
                free(buffer);
                return false;
            }
        }
        current_node = current_node -> children[index];
    }
    free(buffer);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    unload_node(root);
    return true;
}

// Returns index based on character
int index_char(char c)
{
    if (c == '\'')
    {
        return 26;
    }
    else if (c >= 'A' && c <= 'Z')
    {
        return c - 65;
    }
    else
    {
        return c - 97;
    }
}

// Creates empy node with NULL values
node *create_node()
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return NULL;
    }

    // Nullify node values
    for (int i = 0; i < 27; i ++)
    {
        n -> children[i] = NULL;
    }

    n -> word_end = false;

    return n;
}

// Unload node from memory
void unload_node(node *n)
{
    for (int i = 0; i < 27; i++)
    {
        if (n -> children[i] != NULL)
        {
            unload_node(n -> children[i]);
        }
    }
    free(n);
}