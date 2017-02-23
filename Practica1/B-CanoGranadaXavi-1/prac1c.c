/* CANO GRANADA XAVI 46793790Z */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "prac1funs.c"

int inversaA(int n, double **A, double **B, double tol) {
    /*Comptadors*/
    int k, l, j;
    double Mul;

    /*Metode de Gauss*/
    for (k = 0; k < n; k++) {

        if (fabs(A[k][k]) == 0) {
            return 1;
        }

        for (l = k + 1; l < n; l++) {
            Mul = -A[l][k] / A[k][k];
      
            /*Tolerancia*/
            if (fabs(Mul) < tol) {
                Mul = 0;
            }
            for (j = k; j < n; j++) {
                A[l][j] += Mul * A[k][j];
                
            }
            B[k][l] += Mul * B[k][k];
            
        }
    }

    return 0;
}

int main(void) {

    int n, i, j, f, c;
    double **A = NULL, **AA = NULL, **B = NULL, **C = NULL, tol;

    printf("Numero de files y columnes de la matriu ? \n");
    scanf("%d", &n);

    A = (double**) malloc(n * sizeof ( double *));
    AA = (double**) malloc(n * sizeof ( double *));
    B = (double**) malloc(n * sizeof ( double *));
    C = (double**) malloc(n * sizeof ( double *));

    for (i = 0; i < n; i++) {
        A[i] = (double *) malloc(n * sizeof (double));
        AA[i] = (double *) malloc(n * sizeof (double));
        B[i] = (double *) malloc(n * sizeof (double));
        C[i] = (double *) malloc(n * sizeof (double));
    }


    printf("Doneu els( %d x %d ) elements de la matriu A : \n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("A[%d][%d]:\n", i, j);
            scanf("%lf", &A[i][j]);
        }
    }

    printf("Doneu els( %d x %d ) elements de la matriu identitat B : \n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("B[%d][%d]:\n", i, j);
            scanf("%lf", &B[i][j]);
        }
    }

    printf("Doneu una tolerancia per al zero : \n");
    scanf("%lf", &tol);

    printf("\nMatriu A:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf(" %f ", A[i][j]);
        printf("\n");
    }

    printf("\nMatriu identitat B:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf(" %f ", B[i][j]);
        printf("\n");
    }

    for (f = 0; f < n; f++) {
        for (c = 0; c < n; c++)
            AA[f][c] = A[f][c];
        printf("\n");
    }

    inversaA(n, AA, B, tol);

    printf("\nMatriu triangular superior A:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf(" %f ", AA[i][j]);
        printf("\n");
    }

    printf("\nMatriu inversa:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf(" %f ", B[i][j]);
        printf("\n");
    }

    prodMatMat(n, A, B, C);

    printf("\nMatriu C:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf(" %f ", C[i][j]);
        printf("\n");
    }

    for (i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}