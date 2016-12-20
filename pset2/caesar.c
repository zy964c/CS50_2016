#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

char* GetName(void);
int main(int argc, string argv[])
{
    int i;
    int encrypted_value;
    if(argc == 2)
    {
        int k = atoi(argv[1]);
        char* name = GetName();
        /*printf("%i, %s", k, name);*/
        for (i=0; i < strlen(name); i++)
        {
            if(isalpha(name[i]))
            {
                if(isupper(name[i]))
                {
                    encrypted_value = ((((name[i] - 65) + k) % 26 )) + 65;
                }
                else
                {
                    encrypted_value = ((((name[i] - 97) + k) % 26 )) + 97;
                }
                printf("%c", encrypted_value);
            }
            else
            {
                printf("%c", name[i]);
            }
        }
        printf("\n");
        return 0;
    }
    else
    {
        printf("Please give 1 argument!\n");
        return 1;
    }
}   
char* GetName(void)
{
    char* name;
    do
    {
        /*printf("Please enter your name:\n");*/
        name = GetString();
    }
    while (name == NULL);
    return name;
}
    