#include <stdio.h>

void DAXPY(int N, double A, double* X, double* Y, double* Z) {

    for (int i = 0; i < N; i++)
    {
        Z[i] = A * X[i] + Y[i];
    }
}

