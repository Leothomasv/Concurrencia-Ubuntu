#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_INTS = 5;

int main(void){

    char array[MAX_INTS];
    int processes;
    int my_id;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

    if (my_id == 0)
    {
        array[0] = 1;
        array[1] = 2;
        array[2] = 3;
        array[3] = 4;
        array[4] = 5;

        MPI_Send(array, MAX_INTS, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }else{
        MPI_Recv(array,MAX_INTS, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 0; i < MAX_INTS; i++)
        {
            printf("%d\n", array[i]);
        }
        
    }
    
    
    MPI_Finalize();
    return 0;

}

//para compilar mpicc -g -Wall -o hello_world hello_world.c
//para ejecutar mpiexec -n 3 ./hello_world