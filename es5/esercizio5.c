/*
   gcc -o esercizio5.exe esercizio5.c -lm && ./esercizio5.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../integration.h"

long double min = -1;
long double max = 8;

long double f(long double x); // integranda
long double f_laguerre(long double x);

int main()
{
   long double exact = (1. / 16.) * (2736. - 4. * cos(4.) - 32. * cos(32.) + sinl(4.) + sinl(32.));

   FILE *fptr_trap;
   FILE *fptr_simp;
   FILE *fptr_romb;
   FILE *fptr_lege;

   fptr_trap = fopen("data_trapezio.txt", "w");
   fptr_simp = fopen("data_simpson.txt", "w");
   fptr_romb = fopen("data_romberg.txt", "w");
   fptr_lege = fopen("data_legendre.txt", "w");

   int pti_max = 600;

   long double sum_trap;              // Trapezio
   long double sum_simp;              // Simpson
   long double pippo[LENGTH][LENGTH]; // riga-colonna   // Romberg
   long double legendre;

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

   fclose(fptr_trap);
   fclose(fptr_simp);
   fclose(fptr_romb);
   fclose(fptr_lege);
   return 0;
}

long double f(long double x) // esponenziale
{
   long double y = powl(x, 2) + x * sinl(4 * x);
   return y;
}
