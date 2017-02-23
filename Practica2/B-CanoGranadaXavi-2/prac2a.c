/* CANO GRANADA XAVI 46793790Z */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "prac2funs.c"
#define PI 3.14159265358979323846

double f(double t) {

    double f;
    f = exp(sin(t) + cos(t));

    return f;
}

int main(void) {

    /*Creo les variables necesaries pel programa*/
    FILE * pFile;
    double *x = NULL, *y = NULL, t, funcio, poli;
    int n, i;

    /*Llegeixo el grau del polinomi*/
    printf("Grau del polinomi?:\n");
    if (scanf("%d", &n));

    /*Creo el vector un vector de nodes(x) y un altre on guardare les diferencies dividies(y)*/
    x = (double *) malloc((n + 1) * sizeof ( double));
    y = (double *) malloc((n + 1) * sizeof ( double));

    /*Calculo els valors de X[i],Y[i] en n+1 nodes equidistants entre [0,2pi]*/
    for (i = 0; i <= n; i++) {
        t = 0 + i * ((2 * PI) / n);
        x[i] = t;
        y[i] = f(t);
        printf("x:%f    y:%f\n", x[i], y[i]);
    }

    /*Truco a la funcio que fa les diferencies dividides i les guarda al mateix vector(y)*/
    dif_dividides(x, y, n);

    /*Creo un fitxer i escric en ell una capcelera per saber que es cada columna*/
    pFile = fopen("myfile.txt", "w");
    fprintf(pFile, "\n   t          f(t)        Pn(t)       Er(t)\n");
    fprintf(pFile, "---------------------------------------------\n");

    /*Evaluo la funcio f(t) entre [0,2pi] , el poinomi i calculo el seu error en 1001 punts*/
    for (i = 0; i <= 1000; i++) {
        t = 0 + i * ((2 * PI) / 1000);
        funcio = f(t);
        poli = aval(x, y, n, t);
        fprintf(pFile, "%f     %f    %f   %f\n", t, funcio, poli, ((funcio - poli) / funcio));

    }

    /*Llibero memoria*/
    fclose(pFile);
    free(x);
    free(y);


    return 0;
}
