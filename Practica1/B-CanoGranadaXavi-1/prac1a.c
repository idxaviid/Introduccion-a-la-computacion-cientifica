/* CANO GRANADA XAVI 46793790Z */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "prac1funs.c"

int main(void) {

    double **A = NULL, *x = NULL, *b = NULL, *y = NULL, tol;
    int n, i, j;
    int f = 0, c = 0;


    printf("Numero de files y columnes de la matriu ? \n");
    scanf("%d", &n);

    A = (double **) malloc(n * sizeof (double *));

    for (f = 0; f < n; f++) {
        A[f] = (double *) malloc(n * sizeof (double));
    }

    x = (double *) malloc(n * sizeof ( double));
    b = (double *) malloc(n * sizeof ( double));
    y = (double *) malloc(n * sizeof ( double));

    printf("Doneu els( %d x %d ) elements de la matriu A : \n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("A[%d][%d]:\n", i, j);
            scanf("%lf", &A[i][j]);
        }
    }


    printf("\nMatriu A:\n");
    for (f = 0; f < n; f++) {
        for (c = 0; c < n; c++)
            printf(" %f", A[f][c]);
        printf("\n");
    }

    printf("\nDoneu els %d elements del vector b : \n", n);
    for (i = 0; i < n; i++)
        scanf("%lf", &b[i]);

    printf("\nDoneu una tolerancia per al zero : \n");
    scanf("%lf", &tol);

    resoltrisup(n, A, b, x, tol);

    printf("\nLes solucions del sistema son : \n");
    for (j = 0; j < n; j++)
        printf("x%d-->%f\n", j, x[j]);

    prodMatVec(n, A, b, y);

    for (f = 0; f < n; f++) {
        free(A[f]);
    }
    free(A);
    free(x);
    free(b);
    free(y);

    return 0;

}
