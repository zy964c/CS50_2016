#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("minutes: ");
    int minutes = GetInt();
    int bottles_per_minute = 12;
    int bottels_per_shower = minutes * bottles_per_minute;
    printf("bottles: %i\n", bottels_per_shower);
}

