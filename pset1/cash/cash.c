# include <cs50.h>
# include <stdio.h>
# include <math.h>

int main(void)
{
    //Prompt user for change owed
    float dollars;
    do
    {
        dollars = get_float("Change owed ");
    }
    //must be non-negative
    while (dollars < 0);

    //convert float to int
    int cents = round(dollars * 100);

    int due = cents;
    int coins = 0;

    //take values from due adding a coin each time
    while (due >= 25)
    {
        due -= 25;
        coins++;
    }

    while (due >= 10)
    {
        due -= 10;
        coins++;
    }

    while (due >= 5)
    {
        due -= 5;
        coins++;
    }

    while (due >= 1)
    {
        due -= 1;
        coins++;
    }

    //Print number of coins used
    printf("%i\n", coins);

}