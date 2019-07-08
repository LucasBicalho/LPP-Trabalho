#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[])
{
    int n = 16;
    double sum, produto, aux_s, aux_p;
    double a[n], b[n];

    for (int i = 0; i < n; i++)
    {
        a[i] = i * 0.5;
        b[i] = i * 2.0;
    }

    sum = 0;
    aux_s = 0;
    produto = 1;
    aux_p = 1;
    
    #pragma omp parallel shared(a, b, n, sum, produto) firstprivate(aux_s, aux_p)
    {
        #pragma omp sections 
        {
            #pragma omp section
            for (int i = 1; i < n; i++)
            {
                aux_s += a[i] * b[i];
            }

            #pragma omp section
            for (int i = 1; i < n; i++)
            {
                aux_p *= a[i] * b[i];
            }
        }
        
        sum += aux_s;
        produto *= aux_p;
    }

    printf("A soma é: %2.f\n", sum);
    printf("O produto é: %2.f\n", produto);
    
}
