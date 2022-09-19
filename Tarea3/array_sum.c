#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_DIGITS = 10;
struct Load
{
    int start;
    int end;
};

struct Load balance(int cantProcesses, int cantNumbers, int process, int* array){
    double quotient = cantNumbers / cantProcesses;
    double remainder = cantNumbers % cantProcesses;
    int count = 0;
    int sumaParcial = 0;
    double promedioTotal = 0;
    int range;

    struct Load load;

    if (process < remainder)
    {
        count =  quotient + 1;
        load.start = process * count;
    }else{
        count = quotient;
        load.start = process * count + remainder;
    }

    load.end = load.start + count;

    range = load.end - load.start;

    array[0] = 1;
    array[1] = 36;
    array[2] = 6;
    array[3] = 65;
    array[4] = 15;
    array[4] = 6;

    if (process == 0)
    {
        for (int i = 1; i < cantProcesses; i++)
        {
            MPI_Recv(&sumaParcial, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            sumaParcial += sumaParcial;
        } 

        promedioTotal = sumaParcial / cantProcesses;

        printf("Promedio total: %f\n" , promedioTotal);

    }else{

        for (int x = load.start; x < range; x++)
        {
            sumaParcial += array[x];
        }

        sumaParcial += sumaParcial / range;
        MPI_Send(&sumaParcial, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    return load;
}

int main(void){

    int array[MAX_DIGITS];
    int processes;
    int my_id;

    int cantNum = sizeof(array) / sizeof(int);

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    
    balance(processes, cantNum , my_id, array);
    
    MPI_Finalize();
    return 0;

}

//para compilar mpicc -g -Wall -o hello_world hello_world.c
//para ejecutar mpiexec -n 3 ./hello_world