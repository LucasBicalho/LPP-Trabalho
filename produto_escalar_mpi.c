#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv)
{
	int n = 259;
	double a[n], b[n];
	double sum;

	int rank;
	int p;
	double local_a;
	double local_b;
	int local_n;
	int source;
	int dest = 0;
	int tag = 200;

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   	MPI_Comm_size(MPI_COMM_WORLD, &p);

   	//printf("rank = %d\n", rank);
   	local_n = n / p;
   	//printf("local_n = %d\n", local_n);
   	int resto = n % p;
   	//printf("resto = %d\n", resto);
   	if (rank < resto)
   	{
   		local_n++;
   		//local_a = 
   	}

	for (int i = 0; i < n; i++)
	{
		a[i] = i * 0.5;
		b[i] = i * 2.0;
	}

	sum = 0;
	for (int i = 1; i < n; i++)
	{
		sum += a[i]*b[i];
	}

	//printf("sum = %f\n", sum);

	MPI_Finalize();
}
