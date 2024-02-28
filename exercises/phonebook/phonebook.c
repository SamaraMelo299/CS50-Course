#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
    FILE *file = fopen("phonebook.csv", "a");
    if (file == NULL)
    {
        return 1;
    }
    char *nome = get_string("Nome: ");
    char *numero = get_string("Número: ");
    fprintf(file, "%s,%s\n", nome, numero);
    fclose(file);
}