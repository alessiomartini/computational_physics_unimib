/*
   gcc -o esercizio6.exe esercizio6.c -lm && ./esercizio6.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../integration.h"

long double min = 0;
long double max = expl(-9);

long double min_laguerre = 9;
long double min_hermite = 3;

long double f(long double x); // integranda
long double f_laguerre(long double x);
long double f_hermite(long double x);

int main()
{
   long double exact = 101. / (2. * expl(9));

   FILE *fptr_trap;
   FILE *fptr_simp;
   FILE *fptr_romb_trap;
   FILE *fptr_romb_simp;
   FILE *fptr_lagu;
   FILE *fptr_herm;

   fptr_trap = fopen("data_trapezio.txt", "w");
   fptr_simp = fopen("data_simpson.txt", "w");
   fptr_romb_trap = fopen("data_romberg_trap.txt", "w");
   fptr_romb_simp = fopen("data_romberg_simp.txt", "w");
   fptr_lagu = fopen("data_laguerre.txt", "w");
   fptr_herm = fopen("data_hermite.txt", "w");

   int pti_max = 1000;

   long double trapezio;              // Trapezio
   long double simpson;               // Simpson
   long double pippo[LENGTH][LENGTH]; // riga-colonna   // Romberg
   long double laguerre;
   long double hermite;

   for (int r = 0; r < LENGTH; r++)
   {
      for (int c = 0; c < LENGTH; c++)
      {
         pippo[r][c] = 0;
      }
   }

   // trapezio
   for (int i = 6; i <= pti_max; i++)
   {
      trapezio = trapezio_divergenza(min, max, i, f);
      fprintf(fptr_trap, "%d %.50Lg %.50Lf %.50Lf\n", i, powl(i, -1), trapezio, fabsl(-exact + trapezio));
   }

   // simpson
   for (int i = 11; i <= pti_max; i = i + 2)
   {
      simpson = simpson_divergenza(min, max, i, f);
      fprintf(fptr_simp, "%d %.50Lg %.50Lf %.50Lf\n", i, powl(i, -1), simpson, fabsl(-exact + simpson));
   }

   // romberg_trapezio
   romberg_divergenza_trap(min, max, pippo, f);
   for (int r = 3; r < LENGTH; r++) // stampo in coda ai vecchi dati quelli di romberg
   {
      fprintf(fptr_romb_trap, "%.50Lf ", 1. / (powl(2, r) + 1));
      for (int c = 0; c < LENGTH; c++) // stampo in coda ai vecchi dati quelli di romberg
      {
         if (c <= r - 3)
         {
            fprintf(fptr_romb_trap, "%.50Lf ", fabsl(exact - pippo[r][c]));
         }
      }
      fprintf(fptr_romb_trap, "\n");
   }

   for (int r = 0; r < LENGTH; r++)
   {
      for (int c = 0; c < LENGTH; c++)
      {
         pippo[r][c] = 0;
      }
   }
   // romberg_simpson
   romberg_divergenza_sim(min, max, pippo, f);
   for (int r = 4; r < LENGTH; r++) // stampo in coda ai vecchi dati quelli di romberg
   {
      fprintf(fptr_romb_simp, "%.50Lf ", 1. / (powl(2, r) + 1));
      for (int c = 0; c < LENGTH; c++) // stampo in coda ai vecchi dati quelli di romberg
      {
         if (c <= r - 4)
         {
            fprintf(fptr_romb_simp, "%.50Lf ", fabsl(exact - pippo[r][c]));
         }
      }
      fprintf(fptr_romb_simp, "\n");
   }

   // gauss - laguerre
   for (int i = 0; i < LAGSIZE; i++) // spanno solo gl'indici di cui ho calcolato i polinomi
   {
      laguerre = gauss_laguerre(lag[i].n, f_laguerre, min_laguerre);
      fprintf(fptr_lagu, "%d %.50Lf %.50Lg\n", lag[i].n, laguerre, fabsl(exact - laguerre));
   }

   // gauss - hermite
   for (int i = 0; i < HERSIZE; i++) // spanno solo gl'indici di cui ho calcolato i polinomi
   {
      hermite = gauss_hermite_min(her[i].n, f_hermite, min_hermite);
      fprintf(fptr_herm, "%d %.50Lf %.50Lg\n", her[i].n, hermite, fabsl(exact - hermite));
   }

   fclose(fptr_trap);
   fclose(fptr_simp);
   fclose(fptr_romb_trap);
   fclose(fptr_romb_simp);
   fclose(fptr_lagu);
   fclose(fptr_herm);
   return 0;
}

long double f(long double x) // 0.5*(log t)^2 tra 0 ed e^-9
{
   long double y = 0.5 * powl((logl(x)), 2);
   return y;
}

long double f_laguerre(long double x) // 0.5 * t^2 e^-t tra 9 e +inf con x= sqrt(t)
{
   long double y = 0.5 * powl(x, 2);
   return y;
}

long double f_hermite(long double x)
{
   long double y = powl(x, 5);
   return y;
}
