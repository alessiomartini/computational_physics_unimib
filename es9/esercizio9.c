/*
   gcc -o esercizio9.exe esercizio9.c -lm && ./esercizio9.exe
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define M 6    // numero di momenti che calcolo
#define L 1000 // numero di medie che genero (ognuna tramite N_PUNTI punti)

long double pdf_unif(long double min, long double max);
long double pdf_doppietto(long double n1, long double n2);

int main()
{
   FILE *fptr;
   fptr = fopen("data.txt", "w");

   int N_PUNTI_MAX = 8000; // limite max di punti per singola media

   long double cont[M]; // vettori dei momenti
   long double disc[M];

   long double mean_cont[L]; // vettori delle medie
   long double mean_disc[L];

   for (int N_PUNTI = 100; N_PUNTI <= N_PUNTI_MAX; N_PUNTI += 100) // ciclo al variare del numero di punti per media
   {
      // azzero i vettori delle medie
      for (int i = 0; i < L; i++)
      {
         mean_cont[i] = 0;
         mean_disc[i] = 0;
      }

      for (int i = 0; i < L; i++) // vettori con dentro le medie
      {
         for (int N = 0; N < N_PUNTI; N++) // N_PUNTI: numero di punti per ogni media
         {
            mean_cont[i] += pdf_unif(-1., 1.);
            mean_disc[i] += pdf_doppietto(-1., 1.);
         }
         mean_cont[i] /= N_PUNTI;
         mean_disc[i] /= N_PUNTI;
      } // ora ho i vettori delle medie

      // CALCOLO I MOMENTI
      for (int a = 0; a < M; a++)
      {
         for (int i = 0; i < L; i++) // L : numero di medie
         {
            cont[a] += powl(mean_cont[i], a + 1);
            disc[a] += powl(mean_disc[i], a + 1);
         }
      }

      for (int t = 0; t < M; t++)
      {
         cont[t] /= (long double)L;
         disc[t] /= (long double)L;
      } // ora ho i momenti

      // STAMPA RISULTATI
      fprintf(fptr, "%.50Lf ", (long double)N_PUNTI);//1. / (long double)N_PUNTI);

      for (int t = 0; t < M; t++)
      {
         fprintf(fptr, "%.50Lf %.50Lf ", cont[t], disc[t]);
      }

      fprintf(fptr, "%.50Lf %.50Lf ", cont[3] / cont[1], disc[3] / disc[1]);
      fprintf(fptr, "%.50Lf %.50Lf\n", cont[5] / cont[3], disc[5] / disc[3]);
   }

   fclose(fptr);
   return 0;
}

long double pdf_unif(long double min, long double max)
{
   long double num = ((long double)rand() / (long double)RAND_MAX) * (max - min) + min;
   if (num == max || num == min)
   {
      return pdf_unif(min, max);
   }
   else
   {
      return num;
   }
}

long double pdf_doppietto(long double n1, long double n2)
{
   long double sel = ((long double)rand() / (long double)RAND_MAX) - 0.5;

   if (sel > 0)
   {
      return n1;
   }
   else if (sel < 0)
   {
      return n2;
   }
   else
   {
      return pdf_doppietto(n1, n2);
   }
}