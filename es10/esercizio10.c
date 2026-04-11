/*
   g++ -o esercizio10.exe esercizio10.c -std=c++1z && ./esercizio10.exe
*/

#define _USE_MATH_DEFINES // for C

#include <stdio.h>
#include <math.h> // dovrebbe contenere pi e ...
#include <stdlib.h>
#include <time.h>

#include <tuple>
#include <iostream>

std::tuple<int, int> divide(int dividend, int divisor)
{
   return {dividend / divisor, dividend % divisor};
}

double pdf_unif(double min, double max);
double f1(double x);
double f2(double x);
double f3(double x);
std::tuple<double, double> crude_montecarlo(double f(double), double min, double max, int N);
std::tuple<double, double> hitormiss(double f(double), double min, double max, int N, double ymin, double ymax);

int main()
{
   using namespace std;

   FILE *fptr;
   fptr = fopen("data.txt", "w");

   int N_PUNTI = 10000;

   for (int i = 2000; i <= N_PUNTI; i=i+100)
   {
      fprintf(fptr, "%d ", i);
      fprintf(fptr, "%f ", std::get<0>(crude_montecarlo(f1, 0., 5., i)));
      fprintf(fptr, "%f ", std::get<0>(crude_montecarlo(f2, 3., 8., i)));
      fprintf(fptr, "%f ", std::get<0>(crude_montecarlo(f3, -1., 8., i)));
      fprintf(fptr, "%f ", std::get<0>(hitormiss(f1, 0., 5., i, 0., f1(5.))));
      fprintf(fptr, "%f ", std::get<0>(hitormiss(f2, 3., 8., i, 0., f2(8.))));
      fprintf(fptr, "%f ", std::get<0>(hitormiss(f3, -1., 8., i, 0., f3(8.))));

      // Errori:
      fprintf(fptr, "%f ", std::get<1>(crude_montecarlo(f1, 0., 5., i)));
      fprintf(fptr, "%f ", std::get<1>(crude_montecarlo(f2, 3., 8., i)));
      fprintf(fptr, "%f ", std::get<1>(crude_montecarlo(f3, -1., 8., i)));
      fprintf(fptr, "%f ", std::get<1>(hitormiss(f1, 0., 5., i, 0., f1(5.))));
      fprintf(fptr, "%f ", std::get<1>(hitormiss(f2, 3., 8., i, 0., f2(8.))));
      fprintf(fptr, "%f\n", std::get<1>(hitormiss(f3, -1., 8., i, 0., f3(8.))));
   }

   fclose(fptr);

   return 0;
}

// FUNZIONI

double pdf_unif(double min, double max)
{
   return min + (max - min) * ((double)rand() / (double)RAND_MAX);
}

double f1(double x)
{
   return pow(x, 7) * pow(M_E, -x);
}

double f2(double x)
{
   return cosh(x);
}

double f3(double x)
{
   return pow(x, 2) + x * sin(4 * x);
}

std::tuple<double, double> crude_montecarlo(double f(double), double min, double max, int N)
{
   double sum = 0.; // prima somme e poi medie
   double sumSQ = 0.;
   double sigma = 0.;
   double x;
   ;

   for (int i = 0; i < N; i++)
   {
      x = pdf_unif(min, max);
      sum += f(x);
      sumSQ += pow(f(x), 2);
   }

   sum /= N;   // media
   sumSQ /= N; // media quadratica

   return {sum * (max - min), (max - min) * sqrt(sumSQ - pow(sum, 2)) / sqrt(N)};
}

std::tuple<double, double> hitormiss(double f(double), double min, double max, int N, double ymin, double ymax)
{
   //ymax += 100;      //esperimento per aumentare deviazione e punti rigettati

   double N_hit = 0;
   double N_hitSQ = 0; // non sarebbe necessario ma si mantiene per chiarezza e analogia con montecarlo
   double x, y;
   double V = (max - min) * (ymax - ymin);

   for (int i = 0; i < N; i++)
   {
      x = pdf_unif(min, max);
      y = pdf_unif(ymin, ymax);

      if (y <= f(x))
      {
         N_hit++;
         N_hitSQ++; // sarebbe piu 1 al quadrato
      }
   }

   N_hit /= N; // media
   N_hitSQ /= N;

   return {V * N_hit, V  * sqrt(N_hitSQ - pow(N_hit, 2))/sqrt(N)};
}