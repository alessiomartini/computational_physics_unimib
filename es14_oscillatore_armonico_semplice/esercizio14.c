/*
   g++ -o esercizio14.exe esercizio14.c && ./esercizio14.exe
*/

#include <stdio.h>
#include <math.h> // dovrebbe contenere pi e ...
#include <stdlib.h>
#include <time.h>

// #define _USE_MATH_DEFINES // for C

double f(double t, double x)
{
   return -x;
}

double fx(double t, double x)
{
   return x;
}

double step_Eulero(double x_n, double v_n, double h, double f(double, double), double i)
{
   return x_n + h * f(i*h, v_n);
}

double * step_RK2(double i,double h, double *p,  double f(double, double))
{
   double x_n = p[0];
   double v_n = p[1];

   double k1x = h * v_n;
   double k1v = h * f(i*h, x_n);

   double k2x = h * (v_n + k1v / 2);
   double k2v = h * f(i*h + h/2, x_n + k1x / 2);

   p[0] = x_n + k2x;
   p[1] = v_n + k2v;

   return (p);
}


double * step_RK4(double i,double h, double *p,  double f(double, double))
{
   double x_n = p[0];
   double v_n = p[1];

   double k1x = h * v_n;
   double k1v = h * f(i*h, x_n);

   double k2x = h * (v_n + k1v / 2);
   double k2v = h * f(i*h + h/2, x_n + k1x / 2);

   double k3x = h * (v_n + k2v / 2);
   double k3v = h * f(i*h + h/2, x_n + k2x / 2);

   double k4x = h * (v_n + k3v);
   double k4v = h * f(i*h + h, x_n + k3x);

   p[0] = x_n + (k1x + 2 * (k2x + k3x) + k4x) / 6;
   p[1] = v_n + (k1v + 2 * (k2v + k3v) + k4v) / 6;

   return (p);
}

int main()
{
   FILE *fptr;
   fptr = fopen("data.txt", "w");

   double h = 0.2;

   double v_n = 1; // dato iniziale
   double x_n = 0; // dato iniziale
   // poi le uso anche come variabili

   double R2_n[2]; 
   R2_n[0] = x_n;
   R2_n[1] = v_n;

   double R4_n[2]; 
   R4_n[0] = x_n;
   R4_n[1] = v_n;

   double x_true = 0;
   double v_true = 1;

   double x_n1;

   int N_PUNTI = 100;

   fprintf(fptr, "%f ", 0.);
   fprintf(fptr, "%f ", x_n);
   fprintf(fptr, "%f ", v_n);
   fprintf(fptr, "%f ", R2_n[0]);
   fprintf(fptr, "%f ", R2_n[1]);
   fprintf(fptr, "%f ", R4_n[0]);
   fprintf(fptr, "%f ", R4_n[1]);
   fprintf(fptr, "%f ", 0.);
   fprintf(fptr, "%f ", 0.);
   fprintf(fptr, "%f ", 0.);
   fprintf(fptr, "%f ", 0.);
   fprintf(fptr, "%f ", 0.);
   fprintf(fptr, "%f ", 0.);
   fprintf(fptr, "%f ", x_true);
   fprintf(fptr, "%f\n", v_true);

   for (int i = 1; i < N_PUNTI; i++)
   {
      x_true = sin(h * i);
      v_true = cos(h * i);

      x_n1 = step_Eulero(x_n, v_n, h, fx, i);
      v_n = step_Eulero(v_n, x_n, h, f, i);
      x_n = x_n1;

      step_RK2(i, h , R2_n, f);

      step_RK4(i, h , R4_n, f);

      fprintf(fptr, "%f ", i * h);  // tempo

      // eulero
      fprintf(fptr, "%f ", x_n);
      fprintf(fptr, "%f ", v_n);

      // range 2
      fprintf(fptr, "%f ", R2_n[0]);
      fprintf(fptr, "%f ", R2_n[1]);

      // range 4
      fprintf(fptr, "%f ", R4_n[0]);
      fprintf(fptr, "%f ", R4_n[1]);

      // eulero
      fprintf(fptr, "%f ", x_n - x_true);
      fprintf(fptr, "%f ", v_n - v_true);

      // range 2
      fprintf(fptr, "%f ", R2_n[0] - x_true);
      fprintf(fptr, "%f ", R2_n[1] - v_true);

      // range 4
      fprintf(fptr, "%f ", R4_n[0] - x_true);
      fprintf(fptr, "%f ", R4_n[1] - v_true);

      fprintf(fptr, "%f ", x_true);
      fprintf(fptr, "%f\n", v_true);
   }

   fclose(fptr);

   return 0;
}