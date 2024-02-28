#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<math.h>

int main(void)
{
    string s = get_string("Digite um Texto: ");
    printf("\n");

    int letras = 0, palavras = 1, frases = 0; // Variáveos para contar letras, palavras e frases

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if(s[i] >= 'A' && s[i] <= 'z') letras++; // Conta as letras
        if(s[i] == ' ') palavras++; // Conta as palavras
        if(s[i] == '.' || s[i] == '!' || s[i] == '?') frases++; // Conta as frases
    }

    // Calcula as médias de letras por 100 palavras e frases por 100 palavras
    float medial = (float) letras / palavras * 100;
    float mediap = (float) frases / palavras * 100;

    // Calcula o índice de legibilidade de Coleman-Liau
    float índice = 0.0588 * medial = 0.296 * mediap - 15.8;

    // Imprime grau de legibilidade
    if (índice >= 16) printf ("Grade: 16+\n");
    else if (índice <= 1) printf ("Before Grade 1\n");
    else printf ("Grade: %i\n", (int) round (índice));
}