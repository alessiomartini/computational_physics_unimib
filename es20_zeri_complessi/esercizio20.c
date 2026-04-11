/*
   g++ -o esercizio20.exe esercizio20.c && ./esercizio20.exe
*/

// #include <stdio.h>
// #include <math.h> // dovrebbe contenere pi e ...
// #include <stdlib.h>
// #include <time.h>

// #include <iostream>
#include <complex>

int main()
{
   FILE *fptr;
   fptr = fopen("data.txt", "w");

   const int N = 1000;                      // numero di punti per riga
   
   const int K = 10000;                    // numero massimo di iterazinoe

   int iterazioni[N][N];

   double min = -2;
   double max = 2;
   double h = (max - min) / (N - 1);
   const double epsilon = h/2; // precisione

   int contatore;

   // defines the complex numbers
   std::complex<double> z1;
   std::complex<double> z2;

   for (int a = 0; a < N; a++)
   {
      for (int b = 0; b < N; b++)
      {
         z1.real(min + a * h);
         z1.imag(max - b * h);

         z2 = z1 - (std::pow(z1, 3.) - 1.) / (3. * std::pow(z1, 2.)); // primo step
         contatore = 1;

         // ciclo di iterazione newton-rapson
         while (std::abs(z1 - z2) > epsilon && contatore < K)
         {
            z1 = z2;

            z2 = z1 - (std::pow(z1, 3.) - 1.) / (3. * std::pow(z1, 2.)); // ultima cosa da fare
            contatore++;
         }

         iterazioni[a][b] = contatore; // numero di iterazioni
      }
   }

   // PRINT 2D ARRAY ON FILE
   for (int a = 0; a < N; a++)
   {
      for (int b = 0; b < N; b++)
      {
         fprintf(fptr, "%d ", iterazioni[b][a]);
      }
      fprintf(fptr, "\n");
   }

   fclose(fptr);
   return 0;
}
