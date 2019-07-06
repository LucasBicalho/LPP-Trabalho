#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    double sum, produto;
    double a[256], b[256];
    int n = 256, i, aux, aux1, j;
    for(i=0; i<n; i++){
        a[i] = i*0.5;
        b[i] = i*2.0;
    }
    sum = 0;
    aux = 0;
    #pragma omp parallel shared(a,b,n,sum) private(i,aux)
    {
        #pragma omp sections 
        {       
            #pragma omp section
            for(i=1;i<n;i++){
                aux = aux+a[i]*b[i];
            }
        }    
            
            sum = sum+aux;
      }
        
    printf("A soma é: %2.f\n", sum);
}