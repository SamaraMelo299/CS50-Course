#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main (int argc, char *argv[])
{
    // Verifica se a contagem de argumentos é 2
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Abre o arquivo para leitura
    FILE *input_file = fopen(argv[1], "r");

    // Verifica se o input_file é válido
    if (input_file == NULL)
    {
        printf("Could not open file");
        return 2;
    }

    // Armazena blocos de 512 bytes em um array
    unsigned char buffer[512];

    // Rastrear o número de imagens geradas
    int count_image = 0;

    // Executa o ponteiro do arquivo para as imagens recuperadas
    FILE *output_file = NULL;

    // char filename[8]
    char *filename = malloc(8 * sizeof(char));

    // Lê os blocos de 512 bytes
    while (fread(buffer, sizeof(char), 512, input_file))
    {
        // Verifica se os bytes indicam o início do JPEG
        if (buffer [0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Escreve o nome do arquivo JPEG
            sprintf(filename, "%03i.jpg", count_image);

            // Abre o arquivo para escrevermos
            output_file = fopen(filename, "w");

            // Conta o número de imagens encontradas
            count_image++;
        }

        // Verifica se a saída foi usada para entrada válida
        if (output_file != NULL)
        {
            fwrite(buffer, sizeof(char), 512, output_file);
        }
    }
    free(filename);
    fclose(output_file);
    fclose(input_file);

    return 0;
}
