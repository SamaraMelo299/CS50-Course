#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Define o número maximo de candidatos e eleitores
#define MAX_CANDIDATES 9
#define MAX_VOTERS 100

// Define uma estrutura para um candidato
typedef struct
{
    char name[20];     // Nome do candidato
    int votes;         // Número de votos que o candidato possui
    bool eliminated;   // Indica se o candidato foi eliminado
} candidate;

// Define uma matriz global de candidatos e uma matriz de preferencias
candidate candidates[MAX_CANDIDATES] = {{"Alice", 0, false}, {"Bob", 0, false}, {"Charlie", 0, false}};
int preferences[MAX_VOTERS][MAX_CANDIDATES];
int candidate_count = 3;
int voter_count = 0;

// Função para registrar um voto
bool vote(int voter, int rank, char *name)
{
    // Percorre a lista de candidatos
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Função para tabular os votos
void tabulate(void)
{
    // Percorre a lista de eleitores
    for (int i = 0; i < voter_count; i++)
    {
        // Percorre a lista de preferencias do eleitor
        for (int j = 0; j < candidate_count; j++)
        {
            int candidate_index = preferences[i][j];
            if (!candidates[candidate_index].eliminated)
            {
                candidates[candidate_index].votes++;
                break;
            }
        }
    }
}

 // Função para imprimir o vencedor
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > voter_count / 2)
        {
            printf("O vencedor é: %s\n", candidates[i].name);
            return true;
        }
    }
    // Se ninguém ganhou ainda, retorna falso
    return false;
}

// Função para encontrar o número minimo de votos
int find_min(void)
{
    int min_votes = MAX_VOTERS;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            min_votes = candidates[i].votes;
        }
    }
    return min_votes;
}

// Função para verificar se houve empate
bool is_tie(int min_votes)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes != min_votes)
        {
            return false;
        }
    }
    return true;
}

// Função para eliminar o candidato com o número mínimo de votos
void eliminate(int min_votes)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min_votes)
        {
            candidates[i].eliminated = true;
        }
    }
}

// Função principal
int main(void)
{
    printf("Digite o número de eleitores: ");
    scanf("%d", &voter_count);

    // Recebe as preferências de voto de cada eleitor
    for (int i = 0; i < voter_count; i++)
    {
        printf("Eleitor %d\n", i + 1);
        for (int j = 0; j < candidate_count; j++)
        {
            char name[20];
            printf("Rank %d: ", j + 1);
            scanf("%s", name);

             // Se o voto é inválido, solicita ao usuário para votar novamente
            if (!vote(i, j, name))
            {
                printf("Candidato inválido.\n");
                j--;  // Desfaz o incremento do loop para repetir a votação
            }
        }
    }

     // Entra em um loop infinito
    while (true)
    {
        tabulate();

        // Verifica se há um vencedor
        bool won = print_winner();
        if (won)
        {
            break;
        }

        int min_votes = find_min();
        bool tie = is_tie(min_votes);

        // Se houver um empate
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Elimina o candidato com o número mínimo de votos
        eliminate(min_votes);
    }

    return 0;
}
