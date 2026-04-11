/*
   gcc -o esercizio12.exe esercizio12.c -lm && ./esercizio12.exe
*/

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

double pdf_doppietto(double n1, double n2)
{
   double sel = pdf_unif(-1, 1);

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

double g(double x)
{
   if (x <= 1 && x >= -1)
   {
      return 1. / sqrt(M_PI);
   }
   else
   {
      return x * exp(1 - pow(x, 2))/ sqrt(M_PI);
   }
}

double f(double x)
{
   return exp(-pow(x, 2)) / sqrt(M_PI);
}

double pdf_f() // metodo esatto
{
   double r = sqrt(-log(1 - pdf_zero())); // guardare relazione
   double x = r * cos(pdf_unif(0, 2 * M_PI));
   return x;
}

double pdf_g() 
{
   double y; // valore secondo g
   double segno = pdf_doppietto(-1, 1);
   y = pdf_unif(0, 1);
   if (y <= 2. / 3.)
   {
      return (3. / 2.) * y ;//* segno;
   }
   else
   {
      return sqrt(1 - log(3 * (1 - y)));// * segno;
   }
}

double pdf_f_ar()
{
   double x;
   double y;
   int check = 0;

   while (check == 0)
   {
      x = pdf_g();   // giusta
      y = pdf_unif(0, g(x));

      if (y <= f(x))
      {
         //printf("y: %f -- f(x): %f -- x: %f \n",y,f(x),x);
         check = 1;
      }
   }
   return x;
}

int main()
{
   FILE *fptr;
   fptr = fopen("data.txt", "w");

   // BISOGNA FARE ISTOGRAMMA

   int N_PUNTI = 50000;

   for (int i = 0; i < N_PUNTI; i++)
   {
      fprintf(fptr, "%d ", i);
      fprintf(fptr, "%f ", pdf_f());
      fprintf(fptr, "%f\n", pdf_f_ar());
      //printf("doppietto: %f  \n",pdf_doppietto(-1,1));
   }
   for (int i = 0; i < N_PUNTI; i++)
   {
      fprintf(fptr, "%d ", i);
      fprintf(fptr, "%f ", pdf_f());
      fprintf(fptr, "%f\n", - pdf_f_ar());
      //printf("doppietto: %f  \n",pdf_doppietto(-1,1));
   }

   fclose(fptr);

   return 0;
}