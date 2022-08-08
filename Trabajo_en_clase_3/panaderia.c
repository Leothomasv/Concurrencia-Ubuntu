#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>



int Cantidad_Pasteles = 0;
void hornear(); //hornear incrementa la cantidad de pasteles disponibles
void comprar(); //comprar disminuye la cantidad de pasteles disponibles
pthread_mutex_t lock;


int main(int argc, char *argv[]){
    pthread_t * thread_panadero;
    pthread_t * thread_cliente;

    long thread;
    int thread_count = 10;

    thread_panadero = malloc(sizeof(pthread_t) * thread_count);
    thread_cliente = malloc(sizeof(pthread_t) * thread_count);

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("Fallo mutex");
        return 1;
    }

    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_create(&thread_panadero[thread], NULL, hornear, NULL);
        pthread_create(&thread_cliente[thread], NULL, comprar, NULL);
    }

    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_join(thread_panadero[thread], NULL);
        pthread_join(thread_cliente[thread], NULL);
    }

    pthread_mutex_destroy(&lock);
    
}


void hornear(){
    pthread_mutex_lock(&lock);
    printf("Pastelero horneando mas pasteles. \n");
    if(Cantidad_Pasteles < 50){
        Cantidad_Pasteles++;
        sleep(2);
    }
    printf("Pasteles disponibles: %d \n" , Cantidad_Pasteles);
    pthread_mutex_unlock(&lock);
}

void comprar(){
    if(Cantidad_Pasteles == 0){
        printf("No hay pasteles para comprar. \n");
        return;
    }else{
         pthread_mutex_lock(&lock);
         printf("Cliente comprando pastel. \n");
         Cantidad_Pasteles --;
         sleep(2);
         printf("Pasteles disponibles: %d \n" , Cantidad_Pasteles);
         pthread_mutex_unlock(&lock);
    }
}