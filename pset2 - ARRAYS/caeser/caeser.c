#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main (int argc, string argv[])
{
    // Verifica se o usuário forneceu a chave como argumento
    if (argc != 2)
    {
        printf ("Usage: ./caesar key");
        return 1;
    }

    string key = argv[1];
    // Verifica se a chave fornecida é um número
    for (int i = 0; i < strlen(key); i++)
    {
        if (!isdigit(key[i]))
        {
            printf ("Usage: ./caesar key");
            return 1;
        }
    }

    // Converte a chave de string para int
    int k = atoi(key);

    // Solicita ao usuário o texto a ser codificado
    string plaintext = get_string("plaintext: ");
    int length = strlen(plaintext);
    char ciphertext[length + 1];

    // Codifica o texto usando a cifra de César
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha (plaintext[i]))
        {
            char caractere = isupper (plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = (plaintext[i] - caractere + k) % 26 + caractere;
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[length] = '\0';

    // Imprime o texto codificado
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}