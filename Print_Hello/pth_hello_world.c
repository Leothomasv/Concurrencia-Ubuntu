#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void * Hello(void *rank);

int thread_count;

int main(int argc, char * argv[])
{
    long thread;
    pthread_t * threads;

    thread_count = strtol(argv[1], NULL, 10);

    threads = malloc(thread_count * sizeof(pthread_t));

    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_create(&threads[thread], NULL, Hello, (void*)thread);
    }

    printf("Hola desde el thread principal. \n");

    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_join(threads[thread], NULL);
    }

    free(threads);

    return 0;
}

void * Hello(void * rank){
    long my_rank = (long)rank;
    
    printf("Hola desde el hilo %ld");
}