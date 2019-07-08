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
    aux = 0;

    #pragma omp parallel for shared(a, b, n, sum) private(aux)
    for (int i = 1; i < n; i++)
    {
        #pragma omp atomic
        sum += a[i] * b[i];
    }

    printf("A soma é: %2.f", sum);
}
