

#include <iostream>
#include"mpi.h"
#define SIZE 30


int main(int argc,char* argv[])
{

		srand(time(NULL));
		MPI_Init(&argc, &argv);
		int rank, numproc;
		int root = 0;
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		MPI_Comm_size(MPI_COMM_WORLD, &numproc);

		//dimenzija kvadratne matrice procesa
		int q = (int)sqrt(numproc);
		
		int irow = rank / q;
		int jcol = rank % q;

		int* members = (int*)malloc(sizeof(int) * q);

		for (int i = 0;i < q;i++)
			members[i] = i*(q+1);



		if (rank == root)
		{
			printf("members: \n");
			for (int i = 0;i < q;i++)
				printf("%d ", members[i]);
			printf("\n");
		}



		MPI_Group oldGroup,newGroup;
		MPI_Comm newComm;
		MPI_Comm_group(MPI_COMM_WORLD, &oldGroup);
		MPI_Group_incl(oldGroup, q, members, &newGroup);
		MPI_Comm_create(MPI_COMM_WORLD, newGroup, &newComm);

		

		if (newComm != MPI_COMM_NULL)
		{
			int newSize, newRank;
			MPI_Comm_size(newComm, &newSize);
			MPI_Comm_rank(newComm, &newRank);
			printf("Proces %d u starom komunikatoru, %d u novom\n", rank, newRank);

			if (newRank == root)
			{
				char poruka[SIZE];
				sprintf(poruka, "Ovo je neka poruka");

				for (int i = 1;i < newSize;i++)
					MPI_Send(poruka, SIZE, MPI_CHAR, i, 0, newComm);

			}
			else {
				MPI_Status status;
				char poruka[SIZE];
				MPI_Recv(poruka, SIZE, MPI_CHAR, root, 0, newComm, &status);


				printf("Proces %d primio poruku %s u novom komunikatoru \n", newRank, poruka);

			}


		}






		free(members);
		MPI_Finalize();
		return 0;
	
}

