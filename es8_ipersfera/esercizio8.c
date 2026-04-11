/*
   gcc -o esercizio8.exe esercizio8.c -lm && ./esercizio8.exe
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// #include <sys/time.h>
// #include <chrono.h>

#define DIMENSIONE_DOMININO 2
#define N_PUNTI 20

double sommatoria(int array[]); // dei termini al quadrato

double unif_rand_norm(); // pdf uniforme {0,1}

int main()
{
   struct timespec start, end;
   clock_gettime(CLOCK_MONOTONIC_RAW, &start);

   // do stuff
   // int N_PUNTI = 200;   // prima era define ...

   unsigned long long int delta_us;

   int dimensione[DIMENSIONE_DOMININO];          // vettore principale su cui faccio contachilometri
   for (int i = 0; i < DIMENSIONE_DOMININO; i++) // azzeriamo tutto
   {
      dimensione[i] = 0;
   }

   double somma = 0;                                            //  valori della funzione
   double base = pow(1. / (float)N_PUNTI, DIMENSIONE_DOMININO); // misura dell'intervallo di integrazione
   double raggio_sq = 0;                                        // modulo quadro del vettore che vive nel dominio di integrazione

   int check = 1; // variabile che interrompera' il while

   while (check == 1)
   {
      raggio_sq = sommatoria(dimensione);

      if (raggio_sq < 1) // tengo solo i punti del dominio che mi interessa
      {
         somma += sqrt(1 - raggio_sq); // valore della funzione in quel quadrato
      }
      else if (dimensione[1] < N_PUNTI - 1)
      {
         // ESPERIMENTO per fare un po meno punti
         // COSA SUCCEDE QUA? NOI STIAMO SPANNANDO PER ES UN QUATRO DI CERCHIO, SE UN PUNTO CADE FUORI DAL DOMINIO, SICURAMENTE ANCHE QUELLO DOPO SARA' FUORI, QUINDI EVITO DI CONTROLLARE TUTTI I SUCCESSIVI (AL VARIARE DI UNA SINGOLA DIMENSIONE)
         dimensione[0] = 0;
         dimensione[1]++;
         continue; // salta l'incremento contachilometri
      }

      // printf("%d - %d - %d\n",dimensione[0],dimensione[1],dimensione[2]);

      for (int d = 0; d < DIMENSIONE_DOMININO; d++) // spanna le dimensioni --- questo for serve soltanto a fare il 'contachilometri'
      {
         if (dimensione[d] < N_PUNTI - 1)
         {
            dimensione[d]++;
            // basta - ho incrementato la cifra piu 'piccola'
            break;
         }
         else if (dimensione[d] == N_PUNTI - 1)
         {
            dimensione[d] = 0;
            // dimensione[d+1]++;
            continue;
         }
      }

      for (int i = DIMENSIONE_DOMININO - 1; i >= 0; i--) // controllo se ho finito contachilometri
      {
         if (dimensione[i] == N_PUNTI - 1) // appena una dimensione non e' 'finita' ...
         {
            check = 0;
            continue;
         }
         else
         {
            check = 1;
            break;
         }
      }
   }

   somma *= base;
   somma *= pow(2, DIMENSIONE_DOMININO + 1);

   clock_gettime(CLOCK_MONOTONIC_RAW, &end);
   delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;

   printf("Sfera %d-dimensionale:\n - Volume DETERMINISTICO = %.12f --- Tempo: %lld\n", DIMENSIONE_DOMININO + 1, somma, delta_us);

   // **************************************************************************************************************************
   //  ---  // INIZIO MONTE CARLO //  ---  // **********************************************************************************
   // **************************************************************************************************************************

   clock_gettime(CLOCK_MONOTONIC_RAW, &start);

   srand(time(NULL)); // randomize seed
   int punti_rand = pow(10,5);
   somma = 0;

   for (int i = 0; i < punti_rand; i++)
   {
      raggio_sq = 0;
      for (int t = 0; t < DIMENSIONE_DOMININO; t++)
      {
         raggio_sq += pow(unif_rand_norm(), 2); // norma quadra del vettore appartenente al dominio
      }
      if (raggio_sq < 1)
      {
         somma += sqrt(1. - raggio_sq); // valore della funzione in quel punto
      }                                 // altrimenti dovrebbe sommare zero
   }

   somma = somma / (float)punti_rand;
   somma *= pow(2, DIMENSIONE_DOMININO + 1);

   clock_gettime(CLOCK_MONOTONIC_RAW, &end);
   delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;

   printf(" - Volume MONTECARLO = %.12f --- Tempo: %lld\n", somma, delta_us);

   return 0;
}

double sommatoria(int array[]) // dei termini al quadrato
{
   double shift = 1. / (N_PUNTI * 2);
   double sum = 0;
   for (int i = 0; i < DIMENSIONE_DOMININO; i++)
   {
      sum += pow((array[i] + shift) / N_PUNTI, 2); // qua avviene la trasformazione che rinormalizza i vettori posizione
   }
   return sum;
}

double unif_rand_norm() // pdf uniforme {0,1}
{
   return (double)rand() / (double)RAND_MAX;
}
