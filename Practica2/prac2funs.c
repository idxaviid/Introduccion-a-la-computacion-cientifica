/* CANO GRANADA XAVI 46793790Z */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void dif_dividides(double *x, double *y, int n) {

    int i, j;

    for (j = 1; j <= n; j++) {
        for (i = n; i >=j; i--) {
            y[i] = (y[i] - y[i - 1]) / (x[i] - x[i - j]);
        }
    }

}

double aval(double *x, double *z, int n, double t) {

    int i;
    double s = z[n];


    for (i = n - 1; i >= 0; i--) {
        s = s * (t - x[i]) + z[i];
    }

    return s;

}
