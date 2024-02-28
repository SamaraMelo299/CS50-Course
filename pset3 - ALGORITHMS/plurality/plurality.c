#include <stdio.h>
#include <string.h>

// Define o número máximo de candidatos que uma eleição pode ter
#define MAX 9

// Define uma estrutura para um candidato
typedef struct
{
    char name[20]; // Nome do candidato
    int votes;    // Número de votos que o candidato possui
} candidate;

// Define uma matriz global de candidatos
candidate candidates [MAX];
int candidate_count = 0;

// Função para registrar um voto
int vote (char *name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return 1;
        }
    }
    // Se o nome fornecido não corresponder ao nome de nenhum candidato, retorna 0
    return 0;
}

// Função para imprimir o vencedor da eleição
void print_winner (void)
{
    // Inicializa a variável para o número máximo de votos
    int max_votes = 0;

    // Encontra o número máximo de votos
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    }

    // Imprime o nome de cada candidato que tem o número máximo de votos
    printf("O vencedor é:");
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}

// Função principal
int main (void)
{
    // Define o número de candidatos e seus nomes
    candidate_count = 3;
    strcpy(candidates[0].name, "Alice");
    strcpy(candidates[1].name, "Bob");
    strcpy(candidates[2].name, "Charlie");

    int num_voters;
    printf("Digite o número de eleitores:\n");
    if (scanf("%d", &num_voters) != 1 || num_voters < 1)
    {
        printf("Número inválido de eleitores.\n");
        return 1;
    }

    // Permite que cada eleitor vote em um candidato
    char name[20];
    for (int i = 0; i < num_voters; i++)
    {
        printf("Digite o nome do candidato para votar:\n");
        scanf("%s", name);
        if (!vote(name))
        {
            printf("Candidato Inválido!\n");
            i--; // Desfaz o incremento do loop para repetir a votação
        }
    }

    // Imprime o vencedor da eleição
    print_winner();

    return 0;
}
