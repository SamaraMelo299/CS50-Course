#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Número máximo de candidatos
#define MAX 9

// preferences[i][j] é o número de eleitores que preferem i a j
int preferences[MAX][MAX];

// locked[i][j] significa que i está bloqueado em j
bool locked[MAX][MAX];

// Cada par tem um vencedor, um perdedor
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array de candidatos
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Protótipos de função
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Verifica se há uso inválido
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Preenche matriz de candidatos
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Limpa gráfico de pares bloqueados
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Consulta de votos
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] é a preferência do eleitor
        int ranks[candidate_count];

        // Consulta para cada classificação
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Atualiza classificações com uma nova votação
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Atualiza preferências de acordo com a classificação de um eleitor
void record_preferences(int ranks[])
{
    for (int rank = 0; rank < candidate_count; rank++)
    {
        for (int col = rank + 1; col < candidate_count; col++)
        {
            preferences[ranks[rank]][ranks[col]] += 1;
        }
    }
    return;
}

// Registra pares de candidatos onde um é preferido ao outro
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pair new_pair = {i, j};
                pairs[pair_count] = new_pair;
                pair_count += 1;
            }
        }
    }
    return;
}

int pair_weight(int i)
{
    int pair_winner = pairs[i].winner;
    int pair_loser = pairs[i].loser;
    return preferences[pair_winner][pair_loser];
}

// Classifica os pares em ordem decrescente por força de vitória
void sort_pairs(void)
{
    // Classificação de seleção reversa para que tenhamos ordem decrescente
    for (int i = pair_count - 1; i >= 0; i--)
    {
        int min_weight = pair_weight(i);
        int min_idx = i;
        for (int j = i - 1; j >= 0; j--)
        {
            if (pair_weight(j) < min_weight)
            {
                min_weight = pair_weight(j);
                min_idx = j;
            }
        }
        // Troca a vitória mais forte pelo index atual
        pair temp = pairs[min_idx];
        pairs[min_idx] = pairs[i];
        pairs[i] = temp;
    }
    return;
}

bool has_cycle(int winner, int loser)
{
    if (locked[loser][winner] == true)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
       if (locked[i][winner] && has_cycle(i, loser))
        {
            return true;
        }
    }
    return false;
}

// Bloqueia pares no gráfico candidato em ordem, sem criar ciclos
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!has_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Imprime o vencedor da eleição
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                winner = false;
                break;
            }
        }
        if (winner)
        {
            printf("The winner is: %s\n", candidates[i]);
            return;
        }
    }
    return;
}
