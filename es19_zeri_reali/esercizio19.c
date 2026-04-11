/*
   gcc -o esercizio19.exe esercizio19.c -lm && ./esercizio19.exe
*/

#include <stdio.h>
#include <math.h> // dovrebbe contenere pi e ...
#include <stdlib.h>
#include <time.h>

double f0(double x);
double p0(double x);
double f1(double x);
double p1(double x);

void intervalli(double f(double), double a, double b, double epsilon);
void bisezione(double f(double), double a, double b, double epsilon);
void newton(double f0(double), double f1(double), double zero, double epsilon);

int main()
{
   double epsilon = 0.000001;
   double delta = 0.1;

   // PRIMA FUNZOINE
   printf("\nPrima funzinoe\n");
   intervalli(f0, -3, 3, delta);

   printf("Bisezione:\n");
   bisezione(f0, 0.4, 0.5, epsilon);
   bisezione(f0, 0.9, 1.1, epsilon);

   printf("Newton-Rapson:\n");
   newton(f0, f1, 0.5, epsilon);
   newton(f0, f1, 1.1, epsilon);

   // SECONDA FUNZINOE
   printf("\nSeconda funzione\n");
   intervalli(p0, -10, 10, delta);

   printf("Bisezione:\n");
   bisezione(p0, -1, -0.9, epsilon);
   bisezione(p0, -0.9, -0.8, epsilon);
   bisezione(p0, -0.7, -0.6, epsilon);
   bisezione(p0, -0.5, -0.4, epsilon);
   bisezione(p0, -0.2, -0.1, epsilon);
   bisezione(p0, 0.1, 0.2, epsilon);
      bisezione(p0, 0.4, 0.5, epsilon);
   bisezione(p0, 0.6, 0.7, epsilon);
   bisezione(p0, 0.8, 0.9, epsilon);
   bisezione(p0, 0.9, 1, epsilon);

   printf("Newton-Rapson:\n");
   newton(p0, p1, -0.973906, epsilon);
   newton(p0, p1, -0.865062, epsilon);
   newton(p0, p1, -0.679408, epsilon);
   newton(p0, p1, -0.433397, epsilon);
   newton(p0, p1, -0.148875, epsilon);
   newton(p0, p1, 0.148875, epsilon);
      newton(p0, p1, 0.433397, epsilon);
   newton(p0, p1, 0.679408, epsilon);
   newton(p0, p1, 0.865062, epsilon);
   newton(p0, p1, 0.973906, epsilon);

   return 0;
}

double f0(double x)
{
   return 2 * pow(x, 2) - 3 * x + 1;
}

double p0(double x)
{
   return (46189 * pow(x, 10) - 109395 * pow(x, 8) + 90090 * pow(x, 6) - 30030 * pow(x, 4) + 3465 * pow(x, 2) - 63) / 256;
}

double f1(double x)
{
   return 4 * x - 3;
}

double p1(double x)
{
   return (461890 * pow(x, 9) - 875160 * pow(x, 7) + 540540 * pow(x ,5) - 120120 * pow(x, 3) + 6930 * x) / 256;
}

void intervalli(double f(double), double a, double b, double epsilon)
{
   printf("Zeri presenti negli intervalli:\n");
   for (double i = a; i < b + epsilon; i += epsilon) // scansione con finezza epsilon
   {

      if (f(i) * f(i + epsilon) <= 0)
      {
         printf("[%f, %f]\n", i, i + epsilon);
      }
      /*
      else if (f(i) * f(i + epsilon) == 0.0)   // !!! non funziona !!!
      {
         printf("[%f, %f]\n", i, i + epsilon);
      }
      */
   }
   return;
}

void bisezione(double f(double), double a, double b, double epsilon)
{
   double min = a;
   double max = b;
   double media = (max + min) / 2;

   if (f(min) * f(max) > 0)
   {
      printf("Intervallo non corretto\n");
      return;
   }
   else
   {
      printf("Zero in: ");

      if (f(min) * f(max) == 0)
      {
         if (f(min) == 0)
         {
            printf("%f esattamente\n", min);
         }
         if (f(max) == 0)
         {
            printf("%f esattamente\n", max);
         }
         return;
      }
      else if (f(min) * f(max) < 0)
      {
         while (max - min >= 2 * epsilon) // ciclo bisezione
         {
            media = (max + min) / 2;
            // printf("max: %f -- min: %f\n", max, min);

            if (f(min) * f(media) < 0)
            {
               max = media;
            }
            else if (f(max) * f(media) < 0)
            {
               min = media;
            }
            else if (f(media) == 0)
            {
               printf("%f esattamente\n", media);
               return;
            }
         }
         printf("%f +- %f\n", media, epsilon);
         return;
      }
   }
}

void newton(double f0(double), double f1(double), double zero, double epsilon)
{
   // zero = circa dove c'e' lo zero
   double delta1, delta2;
   double x = zero;

   int error = 0;

   printf("Zero in: ");
   do
   {
      if (error == 1000)
      {
         printf("%f +- ?\n", x);
         return;
      }

      delta2 = delta1; // per tener traccia dello step

      delta2 = -f0(x) / f1(x);
      x += delta2;
      error++;

   } while (abs(delta2 + delta1) > epsilon); // spostamento avanti indietro piu piccolo di epsilon

   printf("%f +- %f\n", x, epsilon);

   return;
}