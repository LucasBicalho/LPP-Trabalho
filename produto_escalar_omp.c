#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv)
{
	int n = 256;
	double a[n];
	double b[n];
	double sum = 0;
	double prod = 0;

	for (int i = 0; i < n; i++)
	{
		a[i] = i * 0.5;
		b[i] = i * 2.0;
	}

	sum = 0;
	#pragma omp parallel shared(a, b, n, sum, prod)
	{
		double temp = 0;
		double temp2 = 1;
		#pragma omp sections
		{
			#pragma omp section
			for (int i = 1; i < n; i++)
			{
				temp += a[i]*b[i];
			}

			#pragma omp section
			for (int i = 1; i < n; i++)
			{
				temp2 *= a[i]*b[i];
			}
		}

		#pragma omp critical
		sum += temp;
		prod += temp2;
	}

	/*
	#pragma omp parallel shared(a, b, n, sum)
	{
		double temp = 0;
		#pragma omp for
		for (int i = 1; i< n; i++)
		{
			temp += a[i]*b[i];
		}

		#pragma omp critical
		sum += temp;
	}
	*/

	/*
	#pragma omp parallel for shared(a, b, n) reduction(+:sum)
	for (int i = 1; i < n; i++)
	{
		sum += a[i]*b[i];
	}
	*/

	printf("sum = %f\n", sum);
	printf("prod = %f\n", prod);
}
