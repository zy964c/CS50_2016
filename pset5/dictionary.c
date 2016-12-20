/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;

int h_size = 1000;
node* hashtable[1000];
int ammount = 0;

unsigned long hash(char *str);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int lenght_word = strlen(word);
    char* placeholder = malloc(sizeof(char)*(lenght_word + 1));
    strcpy(placeholder, word);
    for (int i = 0; placeholder[i] != '\0'; i++)
    {
        placeholder[i] = tolower(placeholder[i]);
    }
    unsigned long hash_result = hash(placeholder);
    //printf("Bucket: %lu\n", hash_result);
    node* cursor1;
    cursor1 = hashtable[hash_result];
    while(cursor1 != NULL)
    {
        //printf("%lu, %s\n", hash_result, cursor1->word);
        if(strcmp(cursor1->word, placeholder) == 0)
        {
            free(placeholder);
            return true;
        }
        else
        {
            cursor1 = cursor1->next;
        }
    }
    
    free(placeholder);
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    int n;

    for (n=0; n<h_size; n++)
    {
        hashtable[n] = NULL;
    }
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return 1;
    }
    node* new_node = malloc(sizeof(node));
    while(fscanf(fp, "%s", new_node->word) != EOF)
    {
        ammount++;
        unsigned long hash_bucket = hash(new_node->word);
        //printf("%d - %s - %lu\n", i, new_node->word, hash_bucket);
        node* new_node1 = malloc(sizeof(node));
        strcpy(new_node1->word, new_node->word);

        new_node1->next = hashtable[hash_bucket];
        hashtable[hash_bucket] = new_node1;

    }
    free(new_node);
    fclose(fp);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return ammount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    int i;
    for(i = 0; i < h_size; i++)
    {
        node* cursor2;
        node* temp;
        cursor2 = hashtable[i];
        while(cursor2 != NULL)
        {
            temp = cursor2;
            cursor2 = cursor2->next;
            free(temp);
        }
    }

    return true;
}

unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = (*str++)))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash%1000;
}