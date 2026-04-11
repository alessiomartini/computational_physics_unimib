/*
   gcc -o esercizio11.exe esercizio11.c -lm && ./esercizio11.exe
*/

#define _USE_MATH_DEFINES // for C

#include <stdio.h>
#include <math.h> // dovrebbe contenere pi e ...
#include <stdlib.h>
#include <time.h>

double pdf_zero(); // uniforme tra 0 e 1
double pdf_a();
double pdf_b();
double pdf_c();

int main()
{
   FILE *fptr;
   fptr = fopen("data.txt", "w");

   // BISOGNA FARE ISTOGRAMMA
   int N_PUNTI = 10000;

   for (int i = 0; i < N_PUNTI; i++)
   {
      fprintf(fptr, "%d ", i);
      fprintf(fptr, "%f ", pdf_a());
      fprintf(fptr, "%f ", pdf_b());
      fprintf(fptr, "%f\n", pdf_c());
   }

   fclose(fptr);
   return 0;
}

double pdf_zero() // uniforme tra 0 e 1
{
   return ((double)rand() / (double)RAND_MAX);
}

double pdf_a()
{
   double y = pdf_zero();
   return -log(1 - y*(1-pow(M_E,-2)));
}

double pdf_b()
{
   double y = pdf_zero();
   return -log((1.-y)/M_E);
}

double pdf_c()
{
   double y = pdf_zero();
   return sqrt(-log(1 - y));
}