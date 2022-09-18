#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING = 100;

int main(void){

    char message[MAX_STRING];
    int processes;
    int my_id;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

    if (my_id != 0)
    {
        MPI_Recv(message, MAX_STRING, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Mensaje: %s\n", message); 
    }else{
        for (int i = 1; i < processes; i++)
        {
            sprintf(message, "Saludos desde el proceso %d de %d", i, processes);
            MPI_Send(message, strlen(message) + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    }
    
    MPI_Finalize();
    return 0;

}

//para compilar mpicc -g -Wall -o hello_world hello_world.c
//para ejecutar mpiexec -n 3 ./hello_world