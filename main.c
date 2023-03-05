#include "randomNumbers.c"
#include "quicksort.c"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{
    int n;
    printf("Ingrese la cantidad de numeros aleatorios que desea generar: ");
    scanf("%d", &n);
    // Mandamos a llamara la clase de random numbers
    randomNumbers(n);

    FILE *f = fopen("randomNumbers.txt", "r");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    else
    {
        int data[n];
        int numbers[n];
        // For para almacenar los numeros en un array
        // Otro for para poder paralelizar
        for (int i = 0; i < n; i++)
        {
            fscanf(f, "%d,", &data[i]);
            numbers[i] = data[i];
        }
        // For para mostrar los numeros en el array
        for (int i = 0; i < n; i++)
        {
            printf("%d ", data[i]);
        }
        int da = sizeof(data) / sizeof(data[0]);
        quickSort(numbers, 0, da - 1);
        printf("\nArray ordenado por Quicksort: \n");
        printArray(numbers, da);
        // Guardar numeros ya ordenados
        FILE *filePointer;
        filePointer = fopen("sortedNumbers.txt", "w");
        if (filePointer == NULL)
        {
            printf("El archivo sortedNumbers.txt no se pudo abrir. \n");
        }
        else
        {
            // For para parelilizar, se me ocurre pragma parallel for
            for (int i = 0; i < n; i++)
            {
                if (i == n - 1)
                    fprintf(filePointer, "%d", numbers[i]);
                else
                {
                    fprintf(filePointer, "%d,", numbers[i]);
                }
            }
            fclose(filePointer);
            printf("Numeros ordenados guardados correctamente en el archivo *sortedNumbers.txt*\n");
        }
    }
}
