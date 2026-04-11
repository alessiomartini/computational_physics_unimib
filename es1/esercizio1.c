/*
    gcc -o esercizio1.exe esercizio1.c && ./esercizio1.exe
*/

#include <stdlib.h>
#include <stdio.h>

#define _USE_MATH_DEFINES // for C
#include <math.h>

int main()
{
   FILE *fptr;
   fptr = fopen("data.txt", "w");

   // le seguenti 4 variabili sono il valore della sommatoria finita
   float Sp = 0; // somma piu (diretta)
   float Sm = 0; // somma meno (inversa)

   // Precisione doppia
   double Dp = 0; // diretta
   double Dm = 0;

   double val_vero = M_PI * M_PI / 6;

   int max = 7000;
   int start = 1000; // max - 10;
   // max += 1;   // PER IL CICLO

   for (int N = start; N <= max; N += 1) // ciclo da 1 a max
   {

      for (int i = 1; i < N; i++) // somma da 1 a N-1 (ATTENZIONE!) ALTRIMENTI COMPARE 1/0
      {
         if (i == 0 || N - i == 0)
         {
            printf("i :%d --- N-i :%d\n", i, N - i);
         }

         Sp += 1.0 / (1.0 * i * i); // 1.0 e' necessario altrimenti la funzione restituisce un int
         Sm += 1.0 / (1.0 * (N - i) * (N - i));

         Dp += 1.0 / (1.0 * i * i);
         Dm += 1.0 / (1.0 * (N - i) * (N - i));
      }
      fprintf(fptr, "%3d %10.12f %10.12f %10.12f %10.12f %10.20f %10.20f %10.20f %10.20f\n", N - 1, Sp, Sm, Dp, Dm, val_vero - Sp, val_vero - Sm, val_vero - Dp, val_vero - Dm); // scrivere nel file
      

      Sp = 0;
      Sm = 0;
      Dp = 0;
      Dm = 0;
   }

   fclose(fptr);
   return 0;
}