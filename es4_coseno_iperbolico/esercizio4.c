/*
   gcc -o esercizio4.exe esercizio4.c -lm && ./esercizio4.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../integration.h"

long double min = 3; // estremi integrazione
long double max = 8;

long double f(long double x); // integranda
long double f_laguerre(long double x);

int main()
{
   long double exact = -sinh(3) + sinh(8);

   FILE *fptr_trap;
   FILE *fptr_simp;
   FILE *fptr_romb;
   FILE *fptr_lagu;
   FILE *fptr_lege;

   fptr_trap = fopen("data_trapezio.txt", "w");
   fptr_simp = fopen("data_simpson.txt", "w");
   fptr_romb = fopen("data_romberg.txt", "w");
   fptr_lagu = fopen("data_laguerre.txt", "w");
   fptr_lege = fopen("data_legendre.txt", "w");

   int pti_max = 600;

   long double sum_trap;              // Trapezio
   long double sum_simp;              // Simpson
   long double pippo[LENGTH][LENGTH]; // riga-colonna   // Romberg
   long double legendre, laguerre;

   for (int r = 0; r < LENGTH; r++)
   {
      for (int c = 0; c < LENGTH; c++)
      {
         pippo[r][c] = 0;
      }
   }

   // trapezio e simpson
   for (int i = 2; i <= pti_max; i++)
   {
      sum_trap = trapezio_est(min, max, i, f);
      fprintf(fptr_trap, "%d %.50Lg %.50Lf %.50Lf\n", i, powl(i, -1), sum_trap, fabsl(exact - sum_trap));

      if ((i - 1) % 2 == 0)
      {
         sum_simp = simpson_est(min, max, i, f);
         fprintf(fptr_simp, "%d %.50Lg %.50Lf %.50Lf\n", i, powl(i, -1), sum_simp, fabsl(exact - sum_simp));
      }
   }

   // romberg
   romberg(min, max, pippo, f);
   for (int r = 0; r < LENGTH; r++) // stampo in coda ai vecchi dati quelli di romberg
   {
      fprintf(fptr_romb, "%.50Lf ", 1. / (powl(2, r) + 1));
      for (int c = 0; c < LENGTH; c++) // stampo in coda ai vecchi dati quelli di romberg
      {
         if (c <= r)
         {
            fprintf(fptr_romb, "%.50Lf ", fabsl(exact - pippo[r][c]));
         }
      }
      fprintf(fptr_romb, "\n");
   }

   // gauss - legendre
   for (int i = 0; i < GLAWSIZE; i++) // spanno solo gl'indici di cui ho calcolato i polinomi
   {
      legendre = gauss_legendre(glaw[i].n, f, min, max);
      fprintf(fptr_lege, "%d %.50Lf %.50Lg\n", glaw[i].n, legendre, fabsl(exact - legendre));
   }

   // gauss - laguerre
   for (int i = 0; i < LAGSIZE; i++) // spanno solo gl'indici di cui ho calcolato i polinomi
   {
      laguerre = gauss_laguerre(lag[i].n, f_laguerre, -max);
      laguerre -= gauss_laguerre(lag[i].n, f_laguerre, -min);
      laguerre += gauss_laguerre(lag[i].n, f_laguerre, min);
      laguerre -= gauss_laguerre(lag[i].n, f_laguerre, max);

      fprintf(fptr_lagu, "%d %.50Lf %.50Lg\n", lag[i].n, laguerre, fabsl(exact - laguerre));
   }

   fclose(fptr_trap);
   fclose(fptr_simp);
   fclose(fptr_romb);
   fclose(fptr_lege);
   fclose(fptr_lagu);

   return 0;
}

long double f(long double x) // esponenziale
{
   long double y = coshl(x);
   return y;
}

long double f_laguerre(long double x)
{
   long double y = 0.5;
   return y;
}
