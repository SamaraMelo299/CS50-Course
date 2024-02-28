#include <stdio.h>
#include <cs50.h>
 
// Função get_altura
int get_height_int(void)
{
    // Declarar variável no escopo global
    int n;
    do {
        n = get_int("Height: ");
    } while (n < 1 || n > 8);
    return n;
}

//Função para imprimir pontos na horizontal
void print_dots(int dots) {
    for (int z = 0; z < dots; z++) {
        printf(".");
    }
}

// Função principal
int main(void)
{
    int height = get_height_int();
    for (int i = 1; i <= height; i++) {
        print_dots(height - i);

        for (int j = 0; j < i; j++) {
            printf("#");
        }
        //Gera uma nova linha após cada iteração
        printf("\n");
    }
    return 0;
}
