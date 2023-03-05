#include <iostream>
#include <stdio.h>
#include <omp.h>

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// Optimized partition function using Hoare's partition scheme
int partition(int array[], int low, int high)
{
    // select the rightmost element as pivot
    int pivot = array[high];

    // pointer for greater element
    int i = (low - 1);

    #pragma omp parallel for shared(array, pivot) reduction(+:i)
    for (int j = low; j < high; j++)
    {
        if (array[j] <= pivot)
        {
            i++;
            swap(&array[i], &array[j]);
        }
    }

    // swap the pivot element with the greater element at i
    swap(&array[i + 1], &array[high]);

    // return the partition point
    return (i + 1);
}



// void quickSort(int array[], int low, int high)
// {
//     if (low < high)
//     {
//         int pi = partition(array, low, high);
//         #pragma omp task shared(array)
//         quickSort(array, low, pi - 1);
//         #pragma omp task shared(array)
//         quickSort(array, pi + 1, high);
//         #pragma omp taskwait
//     }
// }

void quickSort(int array[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(array, low, high);
        #pragma omp parallel
        {
            #pragma omp sections
            {
                #pragma omp section
                quickSort(array, low, pi - 1);
                #pragma omp section
                quickSort(array, pi + 1, high);
            }
        }
    }
}

void printArray(int array[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d  ", array[i]);
    }
    printf("\n");
}
//  0.088581

