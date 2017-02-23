/* CANO GRANADA XAVI 46793790Z */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "prac1funs.c"



int gausspivot(int n, double **A, double tol, double *v) {
    /*Comptadors*/
    int k, l, j;
    double  Mul;

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
            v[l] += Mul * v[k];
        }
    }
    return 0;
}

int main(void) {

    double **A = NULL, **AA = NULL, *x = NULL, *b = NULL, *bb = NULL, tol, *fila;
    int n, i, j;
    int f = 0, c = 0;
    fila = 0;


    printf("Numero de files y columnes de la matriu ? \n");
    scanf("%d", &n);


    A = (double **) malloc(n * sizeof (double *));
    AA = (double **) malloc(n * sizeof (double *));

    for (f = 0; f < n; f++) {
        A[f] = (double *) malloc(n * sizeof (double));
        AA[f] = (double *) malloc(n * sizeof (double));
    }

    x = (double *) malloc(n * sizeof ( double));
    b = (double *) malloc(n * sizeof ( double));
    bb = (double *) malloc(n * sizeof ( double));
    fila = (double *) malloc(n * sizeof ( double));

    printf("Doneu els( %d x %d ) elements de la matriu A : \n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("A[%d][%d]:\n", i, j);
            scanf("%lf", &A[i][j]);
        }
    }

    /*Imprimim la matriu*/
    printf("Matriu A:\n");
    for (f = 0; f < n; f++) {
        for (c = 0; c < n; c++)
            printf(" %f ", A[f][c]);
        printf("\n");
    }
    
    /*Termes independets*/
    printf("\nDoneu els %d elements del vector b : \n", n);
    for (i = 0; i < n; i++)
        scanf("%lf", &b[i]);


    /*Tolerancia*/
    printf("\nDoneu una tolerancia per al zero : \n");
    scanf("%lf", &tol);

    /*Faig una copia de A y b*/
    for (f = 0; f < n; f++) {
        bb[f] = b[f];
        for (c = 0; c < n; c++)
            AA[f][c] = A[f][c];
        printf("\n");
    }
    if (gausspivot(n, A, tol, b) == 0) {

        if (resoltrisup(n, AA, bb, x, tol) == 0) {

            printf("Les solucions del sistema son : \n");
            for (f = 0; f < n; f++)
                printf("x%d-->%f\n", f, x[f]);

            /* Ax-b*/
            for (f = 0; f < n; f++) {
                for (c = 0; c < n; c++) {
                    fila[f] = fila[f] + A[f][c] * x[f];
                }
            }
        } else {
            printf("No es pot resoldre el sistema\n");
        }
    } else {
        printf("No es pot resoldre el sistema\n");
    }

    
    /*Lliberem la memoria*/
    for (f = 0; f < n; f++)
        free(A[f]);
    free(A);
    free(b);
    free(x);
    free(fila);
    return 0;
}

