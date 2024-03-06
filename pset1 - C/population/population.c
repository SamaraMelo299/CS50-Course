#include <stdio.h>
#include <cs50.h>

int main (void)
{
    int startSize;
    int endSize;
    int actualPopulation;
    int years = 0;

    // Prompt de entrada de população inicial e final
    do
    {
        startSize = get_int("População inicial:");
    } while (startSize < 9);

    do
    {
        endSize = get_int("População final:");
    } while (endSize < startSize);

    // Calcular anos necessários para atingir a população final
    actualPopulation = startSize;

    while (actualPopulation < endSize)
    {
        actualPopulation += actualPopulation / 3 - actualPopulation / 4;
        years ++;
    }

    printf("Anos para atingir a população final: %i\n", years);

    return 0;
}