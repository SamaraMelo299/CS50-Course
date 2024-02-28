#include <stdio.h>

int main (void)
{
    long long num_cartao, cc_atual, divisor = 10;
    int soma1 = 0, soma2 = 0, somaTot = 0, cont = 0;

    do
    {
        printf("Informe o número do cartão de crédito:\n");
        scanf("%lld", &num_cartao);
    } while (num_cartao <= 0);

    // Primeiro passo
    cc_atual = num_cartao;
    while (cc_atual > 0)
    {
        int ultimoDig = cc_atual % 10;
        soma1 = soma1 + ultimoDig;
        cc_atual = cc_atual / 100;
    }

    // Segundo passo
    cc_atual = num_cartao / 10;
    while (cc_atual > 0)
    {
        int ultimoDig = cc_atual % 10;
        int mult = ultimoDig * 2;
        soma2 = soma2 + (mult % 10) + (mult / 10);
        cc_atual = cc_atual / 100;
    }

    // Terceiro passo
    somaTot = soma1 + soma2;

    cc_atual = num_cartao;
    while (cc_atual != 0)
    {
        cc_atual = cc_atual / 10;
        cont ++;
    }

    for (int i = 0; i < cont - 2; i++)
    {
        divisor = divisor * 10;
    }

    int primeiroDig = num_cartao / divisor;
    int doisPrimeiros = num_cartao / (divisor / 10);

if (somaTot % 10 == 0) {
    if (primeiroDig == 4 && (cont == 13 || cont == 16)) {
        printf("VISA\n");
    } else if ((doisPrimeiros == 34 || doisPrimeiros == 37) && cont == 15) {
        printf("AMEX\n");
    } else if ((doisPrimeiros >= 51 && doisPrimeiros <= 55) && cont == 16) {
        printf("MASTERCARD\n");
    } else {
        printf("INVÁLIDO\n");
    }
} else {
    printf("INVÁLIDO\n");
}

    }