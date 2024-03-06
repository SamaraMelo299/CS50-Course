#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include "dictionary.h"

// Representa um node em uma tabela hash
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Número de buckets na tabela hash
const unsigned int N = 26;

// Hash table
node **table;

// Declara variáveis
unsigned int word_count;

// Retorna verdadeiro se a palavra estiver no dicionário, caso contrário, falso
bool check(const char *word)
{
    // TODO
    unsigned int hash_value = hash(word);
    node *cursor = table[hash_value];

    // Percorre a lista vinculada
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes palavra para um número
unsigned int hash(const char *word)
{
    // TODO
    unsigned long total = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        total += tolower(word[i]);
    }
    return total % N;
}

// Carrega o dicionário na memória, retornando verdadeiro se for bem-sucedido, caso contrário, falso
bool load(const char *dictionary)
{
    // Aloca memória para a tabela hash
    table = malloc(N * sizeof(node*));
    if (table == NULL)
    {
        return false;
    }
    // Inicializa a tabela hash
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Abre dicionário
    FILE *file = fopen(dictionary, "r");

    // Retorne NULL se o arquivo não puder ser aberto
    if (file == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }
    // Declara variável chamada palavra
    char word[LENGTH + 1];

    // Procure no dicionário por strings até EOF
    while (fscanf(file, "%s", word) != EOF)
    {
        // Alocar memória para novo node
        node *n = malloc(sizeof(node));

        // Se malloc retornar NULL, retorne falso
        if (n == NULL)
        {
            return false;
        }

        // Copie a palavra no node
        strcpy(n->word, word);
        unsigned int hash_value = hash(word);
        n->next = table[hash_value];
        table[hash_value] = n;
        word_count++;
    }
    fclose(file);
    return true;
}

// Retorna o número de palavras no dicionário se carregado, caso contrário 0 se ainda não carregado
unsigned int size(void)
{
    return word_count;
}

// Descarrega o dicionário da memória, retornando verdadeiro se for bem-sucedido, caso contrário, falso
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    // Libera a memória alocada para a tabela hash
    free(table);
    return true;
}
