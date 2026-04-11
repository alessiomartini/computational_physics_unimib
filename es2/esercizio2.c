/*
    gcc -o esercizio2.echi_n1e esercizio2.c -lm && ./esercizio2.echi_n1e
*/

#include <stdio.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES // for C
#include <math.h>

int main()
{
    FILE *fptr;
    fptr = fopen("data.txt", "w");

    int N = 150; // potenza massima

    long double exact; // valore esatto
    long double phi1 = (sqrtl(5) - 1) / 2;
    long double phi2 = -(sqrtl(5) + 1) / 2;

    //float fphi1 = (sqrtl(5) - 1) / 2;
    //double dphi1 = (sqrtl(5) - 1) / 2;

    //printf("%.50Lg\n", fphi1 - phi1); // some compilers print 8
    //printf("%.50Lg\n", dphi1 - phi1); // some compilers print 16
    //printf("%.50Lg\n", phi1); // some compilers print 16
    //printf("%.50Lg\n", phi2); // some compilers print 16

    // SINGLE
    float S_n0 = 1;
    float S_n1 = phi1;
    float S_n2;

    // DOUBLE
    double D_n0 = 1;
    double D_n1 = phi1;
    double D_n2;

    // QUADRUPLE
    long double Q_n0 = 1;
    long double Q_n1 = phi1;
    long double Q_n2;

    // QUADRUPLE CON ERRORE
    long double Qerr_n0 = 1;
    long double Qerr_n1 = phi1 - powl(10, -8) * phi2;
    long double Qerr_n2;

    long double S_Delta = 0;
    long double D_Delta = 0;
    long double Q_Delta = 0;

    // FINE INIZIALIZZAZIONE VARIABILI

    // Inizio programma
    // fprintf(fptr, "%d %Lf %f %Lf %f %Lf %Lf %Lf %Lf\n", 0, powl(phi1, 0), S_n0, S_Delta, D_n0, D_Delta, Q_n0, Q_Delta, Qerr_n0);
    // fprintf(fptr, "%d %Lf %f %Lf %f %Lf %Lf %Lf %Lf\n", 1, powl(phi1, 1), S_n1, S_Delta, D_n1, D_Delta, Q_n1, Q_Delta, Qerr_n1);
    // ordine potenza, exact, single, delta sing, double, delta doub, quadruple, delta duad, quadruple err

    for (int i = 2; i <= N; i++)
    {
        exact = powl(phi1, i);

        // S_n1I
        S_n2 = S_n0 - S_n1; // n2
        S_n0 = S_n1;        // n1
        S_n1 = S_n2;        // n0

        D_n2 = D_n0 - D_n1; // n2
        D_n0 = D_n1;        // n1
        D_n1 = D_n2;        // n0

        Q_n2 = Q_n0 - Q_n1; // n2
        Q_n0 = Q_n1;        // n1
        Q_n1 = Q_n2;        // n0

        Qerr_n2 = Qerr_n0 - Qerr_n1; // n2
        Qerr_n0 = Qerr_n1;        // n1
        Qerr_n1 = Qerr_n2;        // n0

        // differenza
        S_Delta = fabsl(exact - S_n2);
        D_Delta = fabsl(exact - D_n2);
        Q_Delta = fabsl(exact - Q_n2);

        fprintf(fptr, "%d %Lf %f %Lf %f %Lf %Lf %Lf %Lf %Lf\n", i, exact, S_n2, S_Delta, D_n2, D_Delta, Q_n2, Q_Delta, Qerr_n2, fabsl(Qerr_n2 - S_n2));
        // ordine potenza, exact, single, delta sing, double, delta doub, quadruple, delta duad, quadruple err
    }

    fclose(fptr);
    return 0;
}