#include <iostream>
#include "mpi.h"
#define n 3
#define m 5
#define TRUE 1
#define FALSE 0


int main(int argc,char* argv[])
{

	MPI_Init(&argc, &argv);
	int rank, numproc;
	MPI_Comm_size(MPI_COMM_WORLD, &numproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int dim[2], period[2], reorder;

	MPI_Comm newComm;
	//vrsta strukture
	dim[0] = n;
	//kolone strukture
	dim[1] = m;
	//prvi indeks da li imamo ciklicnu komunikaciju po vrstama
	period[0] =FALSE;
	//drugi indeks da li imamo ciklicnu komunikaciju po kolonama
	period[1] = TRUE;
	reorder = TRUE;

	int left, right;
	//int up,down;
	MPI_Cart_create(MPI_COMM_WORLD, 2, dim, period, reorder, &newComm);

	int cords[2];
	MPI_Cart_coords(newComm, rank, 2, cords);

	printf("\nProces %d, njegove koordinate u strukturi [%d,%d]\n", rank, cords[0], cords[1]);

	
	//1- levo desno
	//0-gore dole
	
	//2 jer se trazi na tom rastojanju
	MPI_Cart_shift(newComm, 1, 2, &left, &right);
	//MPI_Cart_shift(newComm, 0, 2, &up, &down);

	printf("Za proces %d njegovi susedi levo i desno na rastojanju 2 su %d i %d\n", rank,left, right);
	//printf("Za proces %d njegovi susedi gore i dole na rastojanju 2 su %d i %d\n", rank, up, down);


	

	MPI_Finalize();
	return 0;
  


}

