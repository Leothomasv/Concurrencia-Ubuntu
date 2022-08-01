#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void create_arrays(int dimension, int *x, int **A);
void multiply(int dimension, int *x, int *y, int ** A);
void print_result(int dimension, int *y);

int main(int argc, char *argv[])
{
    int *x, *y;
    time_t t;
    srand((unsigned)time(&t));
    int dimension = strtol(argv[1], NULL, 10);

    int** A = (int **)malloc(dimension * sizeof(int *)); 
    for (int i = 0; i < dimension; i++)
    {
       A[i] = (int *)malloc(dimension * sizeof(int)); 
    }

    x = malloc(dimension * sizeof(int));
    y = malloc(dimension * sizeof(int));

    create_arrays(dimension, x, A);
    multiply(dimension, x, y, A);
    print_result(dimension, y);

    long thread;
    pthread_t * threads;

    int thread_count;
    thread_count = strtol(argv[1], NULL, 10);

    threads = malloc(thread_count * sizeof(pthread_t));

    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_create(&threads[thread], NULL, create_arrays, NULL);
        pthread_create(&threads[thread], NULL, multiply, NULL);
    }

    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_join(threads[thread], NULL);
    }

    free(A);
    free(x);
    free(y);
    free(threads);
    return 0;
}

void create_arrays(int dimension, int *x, int ** A)
{
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            A[i][j] = rand() % 50;
            printf("A[%d][%d] = %d\n", i, j, A[i][j]);
        }
        x[i] = rand() % 50;
        printf("x[%d] = %d\n", i, x[i]);
    }
}

void multiply(int dimension, int *x, int *y, int ** A)
{
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            y[i] += A[i][j] * x[j];
        }
    }
}

void print_result(int dimension, int *y)
{
    printf("printing result\n");
    for (int i = 0; i < dimension; i++)
    {
        printf("y[%d]=%d\n",i, y[i]);
    }
}

//gcc -g -Wall -o matriz-vector matriz-vector.c -lpthread
