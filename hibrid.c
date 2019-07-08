#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <mpi.h>

int main(int argc, char** argv){
   double sum;
   int rank;                         //rank do processo
   int p;                             //número de processos
   double a[256], b[256];
   int n = 256, i;
   int begin, end;                   //inicio e final de uma parte
   int tam;                         //tamanho de uma parte
   int source;                      //remetente da integral
   int dest = 0;                    //destino das integrais (no 0)
   int tag = 200;                   //tipo de mensagem(unico)
   double total;
   MPI_Status status;
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &p);

   tam = n / p;
   int resto = n % p;

   if(resto > 0 && rank < resto){
       tam = tam + 1;
       begin = rank*tam;
   }
   else{
       begin = resto*(tam + 1) + (rank - resto)*tam;
   }
   end = begin + tam;


   #pragma omp parallel for shared(a, b, n) private(i)
   for(i = 0; i < n; i++){
      a[i] = i * 0.5;
      b[i] = i * 2.0;
   }
   sum = 0;
   
   #pragma omp parallel for shared(a,b) reduction(+:sum) private(i)
   for(i = begin; i < end; i++){
      sum = sum + a[i]*b[i];
   }


   //printf("sum local = %f\n", sum);
   if(rank == 0){
      total = sum;
      for(source=1; source<p;source++){
         MPI_Recv(&sum, 1, MPI_DOUBLE, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
         total += sum;
      }
   }
   
   else MPI_Send(&sum, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
   printf("begin: %d, end: %d e tam: %d\n",begin, end, tam);
   if(rank == 0) printf("Resultado: %f\n", total);
   MPI_Finalize();
   return 0;
}