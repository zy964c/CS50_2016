#include <stdio.h>
#include <cs50.h>

int PrintPyramid(int height, int hashes);
int GetInput(void);
int main(void)
{
    int height = GetInput();
    PrintPyramid(height, 2);
}

int GetInput(void)
{
    int height;
    do
    {
    printf("Please inter a non-negative integer no greater than 23: ");
    height = GetInt();
    }
    while (height > 23);
    if (height == 0)
    {
        return 0;
    }
    while (height <0)
    {
       height = GetInput();
    }
    return height;
}

int PrintPyramid(height, hashes)
{
    if (height < 1)
    {
        return 0;
    }
    int spaces;
    int pos;
    int hash;
    spaces = (height - 1);
    pos = 0;
    hash = 0;
    while (pos < spaces)
    {
        printf(" ");
        pos++; 
    }
    while (hash < hashes)
    {
        printf("#");
        hash++;
    }
    printf("\n");
    hashes++;
    if ((height - 1) > 0)
    {
        PrintPyramid((height - 1), hashes);
    }
    return 0;
}