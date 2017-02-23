/* CANO GRANADA XAVI 46793790Z */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include "prac2funs.c"
#define MAX 100

double datajuliana(int dia, int mes, int any) {

    int a, m, y;
    double juliana;

    a = (14 - mes) / 12;
    m = mes + (12 * a) - 3;
    y = any + 4800 - a;

    juliana = ((dia) + (int) (((153 * m) + 2) / 5)+(int) (365 * y)+(int) (y / 4)-(int) (y / 100)+(int) (y / 400) - 32045) - 0.5;

    return juliana;
}

int main(void) {

    /*Creo les variables necesaries pel programa*/
    double *temps = NULL, *x = NULL, *y = NULL, *z = NULL,
            tempstemps, xx, yy, zz,
            tempstempstemps, xxx, yyy, zzz,
            copitemps[8], copix[8], copiy[8], copiz[8],
            t = 2462225.5, aval1, aval2, aval3;
    int n, i, numlineas = 0, cnt = 0;
    char line[MAX], line2[MAX], c,
            *ptr, *ptr2, *ptr3, *ptr4,
            *ptrr, *ptrr2, *ptrr3, *ptrr4;

    /*Declaro i obro el fitxer apophis.dat*/
    FILE * fp = fopen("dades_apophis.dat", "r"), *fp2;

    /*Llegeixo el grau del polinomi*/
    printf("Escolliu el grau del polinomi[6,9,12,15]:\n");
    if (scanf("%d", &n));

    /*Creo els vectors corresponents que necesitare*/
    temps = (double *) malloc((n + 1) * sizeof ( double));
    x = (double *) malloc((n + 1) * sizeof ( double));
    y = (double *) malloc((n + 1) * sizeof ( double));
    z = (double *) malloc((n + 1) * sizeof ( double));

    /*Calculo el numero de lineas del fitxer apophis.dat*/
    for (c = getc(fp); c != EOF; c = getc(fp)) {
        if (c == '\n') {
            numlineas = numlineas + 1;
        }
    }

    /*Tanco el fitxer*/
    fclose(fp);

    /*Obro fixtxer i per cada linea del fitxer apophis.dat*/
    fp = fopen("dades_apophis.dat", "r");
    for (i = 0; i < numlineas; i++) {
        /*Mentre hi hagi mes caracters a la linea agafo a partir de les darreres n+1 lineas*/
        while ((fgets(line, sizeof (line), fp) != NULL) && i >= (numlineas - (n + 1))) {
            ptr = strtok(line, " "); /*Separo fins al espai*/
            tempstemps = atof(ptr); /*Converteixo a double*/
            temps[cnt] = tempstemps; /*Guardo la dataJuliana*/
            ptr2 = strtok(NULL, " ");
            xx = atof(ptr2);
            x[cnt] = xx; /*Guardo la coordenada x*/
            ptr3 = strtok(NULL, " ");
            yy = atof(ptr3);
            y[cnt] = yy; /*Guardo la coordenada y*/
            ptr4 = strtok(NULL, " ");
            zz = atof(ptr4);
            z[cnt] = zz; /*Guardo la coordenada z*/

            cnt = cnt + 1;
        }
    }
    fclose(fp);

    /*Calcul de la interpolacio en t0 amb les n+1 darreres lineas*/
    fp2 = fopen("myfile2.txt", "w+");
    fprintf(fp, "(1)\n\n               Interpolacio en t0 amb les %d+1 darreres lineas\n\n", n);
    fprintf(fp, "   t0                 x                       y                        z\n");
    fprintf(fp, "----------------------------------------------------------------------------------\n");
    for (i = 0; i <= n; i++) {
        dif_dividides(temps, x, n);
        dif_dividides(temps, y, n);
        dif_dividides(temps, z, n);
        aval1 = aval(temps, x, n, t);
        aval2 = aval(temps, y, n, t);
        aval3 = aval(temps, z, n, t);
        fprintf(fp, "%.1f  %.16e  %.16e  %.16e\n", t, aval1, aval2, aval3);
    }
    
    /*Mostro les dades del jugador i equip escollit i la data juliana obtinguda*/
    fprintf(fp, "\n\n(2)\n\n\n- El club estranger escollit es: Arsenal Fc, de la lliga anglesa\n");
    fprintf(fp, "- El jugador d'aquest equip que porta el dorsal que coincideix amb la "
            "data del meu anivesari(27) es: Serge Gnabry, nascut el 14 de Juliol de 1995\n");
    fprintf(fp, "- La data juliana del 14 de Juliol de 1995 es: %.1f\n", datajuliana(14, 7, 2020));
    fprintf(fp, "- La data juliana obtinguda es troba entre les lineas t1 (254) = 2459059.5 y t-1 (253) = 2459039.5\n");

    /*Torno a obrir el fitxer per guardar les 4 lineas anteriors i posteriors a la data juliana obtinguda*/
    fp = fopen("dades_apophis.dat", "r");
    cnt = 0;
    for (i = 0; i < numlineas; i++) {
        /*Mentre hi hagi mes caracters a la linea agafo les t-4 i t+4 lineas anteriors i posteriors a la data juliana obtinguda*/
        while ((fgets(line2, sizeof (line2), fp) != NULL) && i >= 250 && cnt <= 7) {
            ptrr = strtok(line2, " "); /*Separo fins al espai*/
            tempstempstemps = atof(ptrr); /*Converteixo a double*/
            copitemps[cnt] = tempstempstemps; /*Guardo la dataJuliana*/
            ptrr2 = strtok(NULL, " ");
            xxx = atof(ptrr2);
            copix[cnt] = xxx; /*Guardo la coordenada x*/
            ptrr3 = strtok(NULL, " ");
            yyy = atof(ptrr3);
            copiy[cnt] = yyy; /*Guardo la coordenada y*/
            ptrr4 = strtok(NULL, " ");
            zzz = atof(ptrr4);
            copiz[cnt] = zzz; /*Guardo la coordenada z*/

            cnt = cnt + 1;
        }
    }
    fclose(fp);

    /*Mostro les 4 lineas anteriors i posteriors a la data juliana obtinguda i calculo els polinomis i la distancia al sol de l'asteroide*/
    fprintf(fp2, "\n                            Les 4 lineas anteriors y posteriors a la data juliana obtinguda:\n\n");
    fprintf(fp2, "   t0                 x                       y                        z                "
            "  distancia al sol de l'asteroide a temps t0\n");
    fprintf(fp2, "-----------------------------------------------------------------------------"
            "-------------------------------------------------------------------\n");
    for (i = 0; i <= 7; i++) {
        dif_dividides(copitemps, copix, 7);
        dif_dividides(copitemps, copiy, 7);
        dif_dividides(copitemps, copiz, 7);
        aval1 = aval(copitemps, copix, 7, datajuliana(14, 7, 2020));
        aval2 = aval(copitemps, copiy, 7, datajuliana(14, 7, 2020));
        aval3 = aval(copitemps, copiz, 7, datajuliana(14, 7, 2020));
        fprintf(fp2, "%.1f  %.16e  %.16e  %.16e            %.16e\n", copitemps[i], aval1, aval2, aval3,sqrt(pow(aval1,2)+pow(aval2,2)+pow(aval3,2)));
    }
    
    fclose(fp2);
  
    /*Llibero memoria*/
    free(temps);
    free(x);
    free(y);
    free(z);
    return 0;
}
