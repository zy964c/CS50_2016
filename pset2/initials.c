#include <stdio.h>
#include <cs50.h>
#include <string.h>

char* GetName(void);
int main(void)
{
    int i;
    int n;
    int first_char = 1;
    char* name = GetName();
    /*printf("My name is: %s\n", name);*/
    for (i = 0, n = strlen(name); i < n; i++)
    {
        if (first_char == 1)
        {
            printf("%c", name[i]);
            first_char = 0;
        }
        else
        {
            if (strncmp(&name[i], " ", 1) == 0)
            {
                first_char = 1;
            }
        }
    }
    printf("\n");
}

char* GetName(void)
{
    int i;
    char* name;
    do
    {
        /*printf("Please enter your name:\n");*/
        name = GetString();
    }
    while (name == NULL);
    for (i=0; i <= strlen(name); i++)
    {
        if (name[i] >= 97 && name[i] <= 122)
        name[i] = name[i] - 32;
    }
    return name;
}