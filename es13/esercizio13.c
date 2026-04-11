/*
   gcc -o esercizio13.exe esercizio13.c -lm && ./esercizio13.exe
*/

// IMPORTANCE SAMPLING

#define _USE_MATH_DEFINES // for C

#include <stdio.h>
#include <math.h> // dovrebbe contenere pi e ...
#include <stdlib.h>
#include <time.h>

double pdf_zero()
{
   return ((double)rand() / (double)RAND_MAX);
}

double pdf_unif(double min, double max)
{
   return min + (max - min) * pdf_zero();
}

int main()
{
   FILE *fptr;
   fptr = fopen("data.txt", "w");

   int N_PUNTI = 1000;
   double I1;
   double I2;
   double esatto1 = 0.5 * (-2 * M_PI);
   double esatto2 = M_PI;

   for (int N = 1; N < N_PUNTI; N++)
   {
      I1 = 0.;
      I2 = 0.;

      for (int i = 1; i <= N; i++)
      {
         I1 += asin(pdf_unif(0., 1.));
         I2 += acos(pdf_unif(-1., 1.)); // definizione di acos??
      }

      fprintf(fptr, "%d ", N);
      fprintf(fptr, "%f ", I1 / N);
      fprintf(fptr, "%f ", I2 * 2. / N);
      fprintf(fptr, "%f ", fabs(I1 / N - esatto1));
      fprintf(fptr, "%f\n", fabs(I2 * 2. / N - esatto2));
   }

   fclose(fptr);

   return 0;
}