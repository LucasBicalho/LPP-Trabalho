#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[])
{
    int n = 262144;
    double sum, aux;
    double a[n], b[n];

    for (int i = 0; i < n; i++)
    {
        a[i] = i * 0.5;
        b[i] = i * 2.0;
    }
    
    sum = 0;
    
    #pragma omp parallel shared(a, b, n, sum) private(aux)
	{
        aux = 0;
        
        #pragma omp for
        for (int i = 1; i < n; i++)
        {
            aux += a[i] * b[i];
        }

        #pragma omp critical
        sum += aux;
	}

    printf("A soma é: %2.f", sum);
}
