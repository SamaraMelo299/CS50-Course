#include <cs50.h>
#include <stdio.h>

int main(void)
{
     // Solicita um caracter para o usuário
     char c = get_char("Do you agree?");

     // Verifica se concordou
     if (c == 'y' || c == 'Y')
     {
         printf("Agreed.\n");
     }
     else if (c == 'n' || c == 'N')
     {
        printf("Not agreed.\n");
     }
}
