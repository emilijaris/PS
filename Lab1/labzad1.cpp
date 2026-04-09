#include <iostream>
#include "mpi.h"
#define n 32
#define m 4

int main(int argc,char* argv[])
{
   
    int rank, numproc;
    
    int prethodni = 0;
    int buffer[m];
    int sum = 0;
    int number = 0;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    srand(time(NULL) + rank);

    for (int i = 0;i < m;i++)
    {
        buffer[i] = rand() % 10+1;
    }
    printf("Proc: %d ",rank);
    for (int i = 0;i < m;i++)
    {
        printf(" buffer : %d ", buffer[i]);
    }

    for (int i = 0;i < m;i++)
        sum += buffer[i];

    printf("suma za proc %d je %d", rank, sum);
   
    if (rank == numproc-1)
    {
      
        if (sum % 2 == 0)
            number = (1 << rank);
        MPI_Send(&number, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
    }
    else {
        if (rank > 0)
        {
            MPI_Recv(&prethodni, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &status);
            if (sum % 2 == 0)
                number = (1 << rank);
            number = number | prethodni;
            MPI_Send(&number, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);

        }
        else if (rank == 0)
        {
            MPI_Recv(&prethodni, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &status);
            if (sum % 2 == 0)
                number = (1 << rank);
            number = number | prethodni;

            printf("Identifikatori procesa ciji je suma poataka parna\n");
            for (int i = 0;i < 32;i++)
            {
                if ((number & (1 << i))!=0)
                    printf("%d ", i);
            }

            
        }
    }


    MPI_Finalize();

}
