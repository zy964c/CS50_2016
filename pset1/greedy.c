#include <stdio.h>
#include <cs50.h>
#include <math.h>

int CalcCoins(float sum, int coins, float value);
int GetInput(void);
int main(void)
{
    float sum;
    int coins;
    float value;
    int result;
    coins = 0;
    value = 25.0;
    sum = GetInput();
    result = CalcCoins(sum, coins, value);
}

int GetInput(void)
{
    float sum;
    float cents;
    do
    {
        printf("O hai! How much change is owed?\n");
        sum = GetFloat();
    }
    while (sum < 0);
    if (sum == 0)
    {
        return 0;
    }
    cents = (sum/0.01);
    return round(cents);
}

int CalcCoins(float sum, int coins, float value)
{
        int new_value;
        if ((sum - value) >= 0)
        {
            coins = coins + 1;
            sum = sum - value;
            if (sum == 0)
            {
                printf("%i\n", coins);
            }
            else
            {
                CalcCoins(sum, coins, value);
            }
        }
        else
        {
            if (value == 25.0)
            {
                new_value = 10.0;
            }
            if (value == 10.0)
            {
                new_value = 5.0;
            }
            if (value == 5.0)
            {
                new_value = 1.0;
            }
            CalcCoins(sum, coins, new_value);
        }
        return coins;
}