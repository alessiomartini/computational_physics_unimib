/*
   gcc -o esercizio7.exe esercizio7.c -lm && ./esercizio7.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../integration.h"

long double f_laguerre(long double x);
long double f_hermite(long double x);

int main()
{
   long double exact = 135135. * sqrtl(3.1415926535897932384626433) / 256.;

   FILE *fptr_lagu;
   FILE *fptr_herm;

   fptr_lagu = fopen("data_laguerre.txt", "w");
   fptr_herm = fopen("data_hermite.txt", "w");

   long double min_laguerre = 0;

   long double laguerre;
   long double hermite;

   // gauss - laguerre
   for (int i = 0; i < LAGSIZE; i++) // spanno solo gl'indici di cui ho calcolato i polinomi
   {
      laguerre = gauss_laguerre(lag[i].n, f_laguerre, min_laguerre);
      fprintf(fptr_lagu, "%d %.50Lf %.50Lg\n", lag[i].n, laguerre, fabsl(exact - laguerre));
   }

   // gauss - hermite
   for (int i = 0; i < HERSIZE; i++) // spanno solo gl'indici di cui ho calcolato i polinomi
   {
      hermite = gauss_hermite(her[i].n, f_hermite);
      fprintf(fptr_herm, "%d %.50Lf %.50Lg\n", her[i].n, hermite, fabsl(exact - hermite));
   }

   fclose(fptr_lagu);
   fclose(fptr_herm);
   return 0;
}

long double f_laguerre(long double x)
{
   long double y = 0.5 * powl(x, 13. / 2.);
   return y;
}

long double f_hermite(long double x)
{
   long double y = 0.5 * powl(x, 14.);
   return y;
}