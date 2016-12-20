#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

char* GetName(void);
int encrypt_ones(int k, char letter_to_encrypt);
char current_key(char* key, int order);
int check_input(char* e_word);

int main(int argc, string argv[])
{
    int i;
    int j;
    int encrypted_value;
    char* encrypt_word;
    int k;
    int n = 0;
    char* name;
    if(argc == 2)
    {
        encrypt_word = argv[1];
        int value = check_input(encrypt_word);
        if(value == 0)
        {
            name = GetName();
            for (j=0; j <= strlen(name); j++)
            {
                if (encrypt_word[j] >= 65 && encrypt_word[j] <= 90)
                {
                    encrypt_word[j] = encrypt_word[j] + 32;
                }
            }
            /*printf("%s\n", encrypt_word);*/
            for (i=0; i < strlen(name); i++)
            {
                if(isalpha(name[i]))
                {
                    k = current_key(encrypt_word, n);
                    /*printf("k = %i\n", k);*/
                    encrypted_value = encrypt_ones(k, name[i]);
                    printf("%c", encrypted_value);
                    n++;
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
        printf("Please give valid argument!\n");
        return 1;
        } 
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
        name = GetString();
    }
    while (name == NULL);
    return name;
}

int encrypt_ones(int k, char letter_to_encrypt)
{
    int encrypted_value;

    if(isupper(letter_to_encrypt))
    {
        encrypted_value = ((((letter_to_encrypt - 65) + (k-97)) % 26 )) + 65;
    }
    else
    {
        encrypted_value = ((((letter_to_encrypt - 97) + (k-97)) % 26 )) + 97;
    }
    return encrypted_value;
}

char current_key(char* key, int i)
{
    char key_letter;
    key_letter = key[(i%strlen(key))];
    /*printf("key letter: %i\n", key_letter);*/
    return key_letter;
}

int check_input(char* e_word)
{
    int t = 0;
    int i;
    for (i=0; i <= strlen(e_word); i++)
    {
        if(isalpha(e_word[i]))
        {
            t++;
        }
    }
    if(t == strlen(e_word))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}