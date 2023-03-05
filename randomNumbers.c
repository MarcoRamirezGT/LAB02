#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int randomNumbers(int n)
{
    // Declaramos el puntero al archivo
    FILE *filePointer;
    int i;
    // asignamos la funcion del tiempo para poder obtener distintos numeros aleatorios en base al tiempo.
    time_t t;
    // Abrimos el archivo en modo escritura
    filePointer = fopen("randomNumbers.txt", "w");

    if (filePointer == NULL)
    {
        printf("El archivo randomNumbers.txt no se pudo abrir. \n");
    }
    else
    {
        srand((unsigned)time(&t));

        // Este for generara numeros aleatorios del 0 al 100
        for (i = 0; i < n; i++)
        {
            if (i == n - 1)
                fprintf(filePointer, "%d", rand() % 100);
            else
            {
                fprintf(filePointer, "%d,", rand() % 100);
            }
        }

        fclose(filePointer);
        printf("Numeros aleatorios guardados correctamente en el archivo *randomNumbers.txt*\n");
    }
    return 0;
}