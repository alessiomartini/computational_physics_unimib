/*
   g++ -o esercizio15.exe esercizio15.c && ./esercizio15.exe
*/

#include <stdio.h>
#include <math.h> // dovrebbe contenere pi e ...
#include <stdlib.h>
#include <time.h>

#define MU 1   // gamma
#define A 1

// #define _USE_MATH_DEFINES // for C

double f1(double t, double x, double v)
{
   return -sin(x);
}

double f2(double t, double x, double v) // t: tempo, x: posizione, v: velocita, g: coefficiente attrito viscoso
{
   return -sin(x) - MU * v;
}

double f3(double t, double x, double v)
{
   return -sin(x) - MU * v + A * sin(t * 2 / 3);
}

double *step_Eulero(double i, double h, double *p, double f(double, double, double))
{
   double x_n = p[0];
   double v_n = p[1];

   double k1x = h * v_n;
   double k1v = h * f(i * h, x_n, v_n);

   p[0] = x_n + k1x;
   p[1] = v_n + k1v;

   return (p);
}

double *step_RK2(double i, double h, double *p, double f(double, double, double))
{
   double x_n = p[0];
   double v_n = p[1];

   double k1x = h * v_n;
   double k1v = h * f(i * h, x_n, v_n);

   double k2x = h * (v_n + k1v / 2);
   double k2v = h * f(i * h + h / 2, x_n + k1x / 2, v_n + k1v / 2);

   p[0] = x_n + k2x;
   p[1] = v_n + k2v;

   return (p);
}

double *step_RK4(double i, double h, double *p, double f(double, double, double))
{
   double x_n = p[0];
   double v_n = p[1];

   double k1x = h * v_n;
   double k1v = h * f(i * h, x_n, v_n);

   double k2x = h * (v_n + k1v / 2);
   double k2v = h * f(i * h + h / 2, x_n + k1x / 2, v_n + k1v / 2);

   double k3x = h * (v_n + k2v / 2);
   double k3v = h * f(i * h + h / 2, x_n + k2x / 2, v_n + k2v / 2);

   double k4x = h * (v_n + k3v);
   double k4v = h * f(i * h + h, x_n + k3x, v_n + k3v);

   p[0] = x_n + (k1x + 2 * (k2x + k3x) + k4x) / 6;
   p[1] = v_n + (k1v + 2 * (k2v + k3v) + k4v) / 6;

   return (p);
}

int main()
{
   FILE *fptr;
   fptr = fopen("data.txt", "w");

   double h = 0.2;   // passo temporale

   double v_n = 1; // dato iniziale
   double x_n = 0; // dato iniziale

   double Eul_n[3][2];  // 2 colonne: x e y; 3 righe: eulero runge2 runge4
   double R2_n[3][2];
   double R4_n[3][2];

   for (int i = 0; i<3; i++)  // inietto condizioni iniziali
   {
      Eul_n[i][0] = x_n;
      Eul_n[i][1] = v_n;

      R2_n[i][0] = x_n;
      R2_n[i][1] = v_n;

      R4_n[i][0] = x_n;
      R4_n[i][1] = v_n;
   }

   double x_true = x_n;
   double v_true = v_n;

   int N_PUNTI = 150;

   for (int i = 0; i < N_PUNTI; i++)
   {
      fprintf(fptr, "%f ", i * h);

// funzione 1
      // eulero
      fprintf(fptr, "%f ", Eul_n[0][0]);
      fprintf(fptr, "%f ", Eul_n[0][1]);

      // range 2
      fprintf(fptr, "%f ", R2_n[0][0]);
      fprintf(fptr, "%f ", R2_n[0][1]);

      // range 4
      fprintf(fptr, "%f ", R4_n[0][0]);
      fprintf(fptr, "%f ", R4_n[0][1]);

// funzione 2
      // eulero
      fprintf(fptr, "%f ", Eul_n[1][0]);
      fprintf(fptr, "%f ", Eul_n[1][1]);

      // range 2
      fprintf(fptr, "%f ", R2_n[1][0]);
      fprintf(fptr, "%f ", R2_n[1][1]);

      // range 4
      fprintf(fptr, "%f ", R4_n[1][0]);
      fprintf(fptr, "%f ", R4_n[1][1]);
 
// funzione 3
      // eulero
      fprintf(fptr, "%f ", Eul_n[2][0]);
      fprintf(fptr, "%f ", Eul_n[2][1]);

      // range 2
      fprintf(fptr, "%f ", R2_n[2][0]);
      fprintf(fptr, "%f ", R2_n[2][1]);

      // range 4
      fprintf(fptr, "%f ", R4_n[2][0]);
      fprintf(fptr, "%f\n", R4_n[2][1]);

      step_Eulero(i, h, Eul_n[0], f1);
      step_RK2(i, h, R2_n[0], f1);
      step_RK4(i, h, R4_n[0], f1);

      step_Eulero(i, h, Eul_n[1], f2);
      step_RK2(i, h, R2_n[1], f2);
      step_RK4(i, h, R4_n[1], f2);

      step_Eulero(i, h, Eul_n[2], f3);
      step_RK2(i, h, R2_n[2], f3);
      step_RK4(i, h, R4_n[2], f3);
   }

   fclose(fptr);

   return 0;
}