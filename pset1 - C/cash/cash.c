#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void)
{
    // 25c, 10c, 5c, 1c
    // get_value
    float dollars;
    do {
        dollars = get_float("Dollars: ");
    }
    while (dollars < round (0.01));

    int cents = round (dollars * 100); // Em cents
    int coins = 0; // Contar moedas

    printf("You have = %i C \n", cents);

    // Repetir até que cents seja maior ou igual a 0
    while (cents > 0) {
        if (cents >= 25) {
            cents -=25;
            coins ++;
        } else if (cents >= 10) {
            cents -= 10;
            coins ++;
        } else if (cents >= 5) {
            cents -= 5;
            coins ++;
        } else {
            cents -= 1;
            coins ++;
        }
    }

    printf ("%d\n", coins);
}