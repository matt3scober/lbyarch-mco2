#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "daxpy.h"

extern void DAXPYASM(int N, double A, double* X, double* Y, double* Z_ASM);

void intialize_vector(int N, double* X, double* Y) {
    for (int i = 0; i < N; i++)
    {
        X[i] = (double)rand() / RAND_MAX;
        Y[i] = (double)rand() / RAND_MAX;
    }
}



int main(int argc, char* argv[]) {
    // variables for time 
    clock_t start_c, end_c, start_asm, end_asm;
    double time_c = 0, time_asm = 0;

    int N = 1 << 30;
    double A = (double)rand() / RAND_MAX;


    double* X;
    X = (double*)malloc(N * sizeof(double));
    double* Y;
    Y = (double*)malloc(N * sizeof(double));
    double* Z_C;
    Z_C = (double*)malloc(N * sizeof(double));
    double* Z_ASM;
    Z_ASM = (double*)malloc(N * sizeof(double));

    intialize_vector(N, X, Y);

    for (int i = 0; i < 30; i++) {
        // C Program 
        start_c = clock();
        DAXPY(N, A, X, Y, Z_C);
        end_c = clock();

        time_c += ((double)(end_c - start_c)) / CLOCKS_PER_SEC;

        // ASM Program
        start_asm = clock();
        DAXPYASM(N, A, X, Y, Z_ASM);
        end_asm = clock();

        time_asm += ((double)(end_asm - start_asm)) / CLOCKS_PER_SEC;
    }
    double ave_c = time_c / 30;
    double ave_asm = time_asm / 30;

    printf("Average CPU time used by C program: %lf seconds\n\n", ave_c);
    printf("Average CPU time used by ASM program: %lf seconds\n\n", ave_asm);


    // Correctness Check 
    printf("%-12s%-12s%-8s\n", "C Output", "ASM Output", "Result");

    for (int i = 0; i < 10; i++) {
        printf("%-12lf%-12lf", Z_C[i], Z_ASM[i]);
        if (Z_C[i] == Z_ASM[i]) {
            printf("%-8s\n", "Pass");
        }
        else {
            printf("%-8s\n", "Fail");
        }
    }

    free(X);
    free(Y);
    free(Z_C);
    free(Z_ASM);

    return 0;
}