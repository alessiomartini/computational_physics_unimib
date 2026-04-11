/*
   gcc -o esercizio17.exe esercizio17.c -lm && ./esercizio17.exe
*/

#include <stdio.h>
#include <math.h> // dovrebbe contenere pi e ...
#include <stdlib.h>
#include <time.h>

// #define _USE_MATH_DEFINES // for C

double f(double x, double y, double z);
double g(double x, double y, double z);
double l(double x, double y, double z);
double *step_Eulero(double h, double *p);
double *step_RK2(double h, double *p);
double *step_RK4(double h, double *p);

int main()
{
   FILE *fptr;
   fptr = fopen("data.txt", "w");

   double h = 0.01; // passo temporale

   double x_n = 0.1; // dato iniziale
   double y_n = 0.1; // dato iniziale
   double z_n = 0.1; // dato iniziale

   double Eul_n[3]; // 2 colonne: x e y; 3 righe: eulero runge2 runge4
   double R2_n[3];
   double R4_n[3];

   Eul_n[0] = x_n;
   Eul_n[1] = y_n;
   Eul_n[2] = z_n;

   R2_n[0] = x_n;
   R2_n[1] = y_n;
   R2_n[2] = z_n;

   R4_n[0] = x_n;
   R4_n[1] = y_n;
   R4_n[2] = z_n;

   int N_PUNTI = 2000;

   fprintf(fptr, "%f ", 0.); // tempo

   // funzione 1
   fprintf(fptr, "%f ", Eul_n[0]); // x eulero
   fprintf(fptr, "%f ", Eul_n[1]); // v eulero
   fprintf(fptr, "%f ", Eul_n[2]); // v eulero
   fprintf(fptr, "%f ", R2_n[0]);
   fprintf(fptr, "%f ", R2_n[1]);
   fprintf(fptr, "%f ", R2_n[2]);
   fprintf(fptr, "%f ", R4_n[0]);
   fprintf(fptr, "%f ", R4_n[1]);
   fprintf(fptr, "%f\n", R4_n[2]);

   for (int i = 1; i < N_PUNTI; i++)
   {
      fprintf(fptr, "%f ", i * h);

      // funzione 1
      step_Eulero(h, Eul_n);
      step_RK2(h, R2_n);
      step_RK4(h, R4_n);

      // eulero
      fprintf(fptr, "%f ", Eul_n[0]); // x eulero
      fprintf(fptr, "%f ", Eul_n[1]); // v eulero
      fprintf(fptr, "%f ", Eul_n[2]); // v eulero

      // range 2
      fprintf(fptr, "%f ", R2_n[0]);
      fprintf(fptr, "%f ", R2_n[1]);
      fprintf(fptr, "%f ", R2_n[2]);

      // range 4
      fprintf(fptr, "%f ", R4_n[0]);
      fprintf(fptr, "%f ", R4_n[1]);
      fprintf(fptr, "%f\n", R4_n[2]);
   }

   fclose(fptr);

   return 0;
}

double f(double x, double y, double z)
{
   return -10 * (x - y);
}

double g(double x, double y, double z) // t: tempo, x: posizione, v: velocita, g: coefficiente attrito viscoso
{
   return -x * z + 28 * x - y;
}

double l(double x, double y, double z)
{
   return x * y - z * 8. / 3;
}

double *step_Eulero(double h, double *p)
{
   double x_n = p[0];
   double y_n = p[1];
   double z_n = p[2];

   double k1x = h * f(x_n, y_n, z_n);
   double k1y = h * g(x_n, y_n, z_n);
   double k1z = h * l(x_n, y_n, z_n);

   p[0] = x_n + k1x;
   p[1] = y_n + k1y;
   p[2] = z_n + k1z;

   return (p);
}

double *step_RK2(double h, double *p)
{
   double x_n = p[0];
   double y_n = p[1];
   double z_n = p[2];

   double k1x = h * f(x_n, y_n, z_n);
   double k1y = h * g(x_n, y_n, z_n);
   double k1z = h * l(x_n, y_n, z_n);

   double k2x = h * f(x_n + k1x / 2, y_n + k1y / 2, z_n + k1z / 2);
   double k2y = h * g(x_n + k1x / 2, y_n + k1y / 2, z_n + k1z / 2);
   double k2z = h * l(x_n + k1x / 2, y_n + k1y / 2, z_n + k1z / 2);

   p[0] = x_n + k2x;
   p[1] = y_n + k2y;
   p[2] = z_n + k2z;

   return (p);
}

double *step_RK4(double h, double *p)
{
   double x_n = p[0];
   double y_n = p[1];
   double z_n = p[2];

   double k1x = h * f(x_n, y_n, z_n);
   double k1y = h * g(x_n, y_n, z_n);
   double k1z = h * l(x_n, y_n, z_n);

   double k2x = h * f(x_n + k1x / 2, y_n + k1y / 2, z_n + k1z / 2);
   double k2y = h * g(x_n + k1x / 2, y_n + k1y / 2, z_n + k1z / 2);
   double k2z = h * l(x_n + k1x / 2, y_n + k1y / 2, z_n + k1z / 2);

   double k3x = h * f(x_n + k2x / 2, y_n + k2y / 2, z_n + k2z / 2);
   double k3y = h * g(x_n + k2x / 2, y_n + k2y / 2, z_n + k2z / 2);
   double k3z = h * l(x_n + k2x / 2, y_n + k2y / 2, z_n + k2z / 2);

   double k4x = h * f(x_n + k3x, y_n + k3y, z_n + k3z);
   double k4y = h * g(x_n + k3x, y_n + k3y, z_n + k3z);
   double k4z = h * l(x_n + k3x, y_n + k3y, z_n + k3z);

   p[0] = x_n + (k1x + 2 * (k2x + k3x) + k4x) / 6;
   p[1] = y_n + (k1y + 2 * (k2y + k3y) + k4y) / 6;
   p[2] = z_n + (k1z + 2 * (k2z + k3z) + k4z) / 6;

   return (p);
}
