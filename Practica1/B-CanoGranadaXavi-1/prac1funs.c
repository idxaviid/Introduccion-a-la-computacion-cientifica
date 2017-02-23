/* CANO GRANADA XAVI 46793790Z */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int resoltrisup(int n, double **A, double *b, double *x, double tol) {
    int j, k;
    double sum = 0;

    for (j = n - 1; j >= 0; j--) {
        for (k = j + 1; k < n; k++)
            sum = sum + (A[j][k] * x[k]);
        /*Casen que dividim per 0*/
        if (A[j][j] == 0) {
            return 1;
        }
        x[j] = (b[j] - sum) / A[j][j];
        /*¿Tolerancia? */
        if (fabs(x[j]) < tol) {
            x[j] = 0;
        }
        /*Reinicialitzo el sumatori*/
        sum = 0;
    }

    return 0;
}

void prodMatVec(int n, double **A, double *x, double *y) {

    int i, j;

    for (i = 0; i < n; i++) {
        y[i] = 0.f;
        for (j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    printf("\nEl resultat de la matriu (A) pel vector (b) es:\n");
    for (i = 0; i < n; i++)
        printf("%f \n", y[i]);

}

void prodMatMat(int n, double **A, double **B, double **C) {

    int i, j, k;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            C[i][j] = 0;
            for (k = 0; k < n; k++) {
                C[i][j] = (C[i][j] + (A[i][k] * B[k][j]));
            }
        }
    }
}

