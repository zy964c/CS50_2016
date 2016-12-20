/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if(n > 0)
    {
        int first = 0;
        int last = n;
        int middle = (first + last)/2;
        while(first <= last)
        {
            if(values[middle] == value)
            {
                return true;
            }
            else if(values[middle] > value)
            {
                last = middle - 1;
            }
            else
                first = middle + 1;
                
            middle = (first + last)/2;
        }
        
        
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    if(n > 0)
    {
        int i;
        int swap;
        bool sorted = true;
        for(i = 0; i <= (n - 1); i++)
        {
            /*printf("here is an i: %i\n", i);*/
            if(values[i] > values[i+1])
            {
                /*int j;
                for(j = 0; j <= n; j++) 
                {
                    printf("array_before: %i\n", values[j]);
                }*/
                swap = values[i+1];
                values[i+1] = values[i];
                values[i] = swap;
                /*for(j = 0; j <= n; j++) 
                {
                    printf("array_after: %i\n", values[j]);
                }*/
                sorted = false;
            }
            else
            {
                continue;
            }
        }
        if(sorted != true)
        {
            sort(values, n);
        }
    }
    return;
}