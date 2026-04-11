#define LENGTH 20

typedef struct tagGLAW
{
   int n;
   long double *x;
   long double *w;
} GLAW;

// laguerre
#include "laguerre_data.h"
static GLAW lag[] = { // numero punti, punti, pesi
    {2, y2, z2},
    {3, y3, z3},
    {4, y4, z4},
    {5, y5, z5},
    {6, y6, z6},
    {7, y7, z7},
    {8, y8, z8},
    {9, y9, z9},
    {10, y10, z10},
    {12, y12, z12},
    {14, y14, z14},
    {16, y16, z16},
    {20, y20, z20},
    {32, y32, z32},
    {64, y64, z64}};
static const int LAGSIZE = sizeof(lag) / sizeof(lag[0]);

// legendre
#include "legendre_data.h"
static GLAW glaw[] = {
    {1, x1, w1},
    {2, x2, w2},
    {3, x3, w3},
    {4, x4, w4},
    {5, x5, w5},
    {6, x6, w6},
    {7, x7, w7},
    {8, x8, w8},
    {9, x9, w9},
    {10, x10, w10},
    {11, x11, w11},
    {12, x12, w12},
    {13, x13, w13},
    {14, x14, w14},
    {15, x15, w15},
    {16, x16, w16},
    {17, x17, w17},
    {18, x18, w18},
    {19, x19, w19},
    {20, x20, w20},
    {32, x32, w32},
    {64, x64, w64},
    {96, x96, w96},
    {100, x100, w100},
    {128, x128, w128},
    {256, x256, w256},
    {512, x512, w512},
    {1024, x1024, w1024}};
static const int GLAWSIZE = sizeof(glaw) / sizeof(glaw[0]);

// hermite
#include "hermite_data.h"
static GLAW her[] = {
    {2, x_Hermite2, w_Hermite2},
    {4, x_Hermite4, w_Hermite4},
    {5, x_Hermite5, w_Hermite5},
    {8, x_Hermite8, w_Hermite8},
    {100, x_Hermite100, w_Hermite100}};
static const int HERSIZE = sizeof(her) / sizeof(her[0]);

long double trapezio_est(long double min, long double max, int N, long double f(long double)) // trapezio esteso
{
   long double sum = 0.;
   long double h = (max - min) / (long double)(N - 1);

   sum += (f(min) + f(max)) / 2.;
   for (int i = 1; i < N - 1; i++)
   {
      sum += f(min + i * h);
   }
   return sum * h;
}

long double trapezio_open(long double f(long double), long double val, long double h) // formula aperta per trapezio
{                                                                                     // val e' il punto centrale
   long double y = 2 * h * f(val);
   return y;
}

long double trapezio_divergenza(long double min, long double max, int N, long double f(long double)) // formula trapezio nel caso di una singolarita' integabile
{                                                                                                    // almeno 6 punti
   //long double h = (max - min) / powl(N - 1, 1);
    long double h = (max - min) / powl(10, 3);
   //  h = powl(h,3);

   long double sum;
   sum = trapezio_open(f, min + h, h);
   sum += trapezio_open(f, max - h, h);
   N = N - 2;
   sum += trapezio_est(min + 2 * h, max - 2 * h, N, f);

   return sum;
}

long double simpson_est(long double min, long double max, int N, long double f(long double)) // simpson esteso
{
   if ((N - 1) % 2 != 0)
   {
      printf("Errore in simpson esteso: numero di punti pari\n");
      return 0;
   }

   long double sum = 0;
   long double h = (max - min) / (N - 1);

   for (int i = 1; i < N - 1; i++)
   {
      if (i % 2 == 0) // pari  (attenzione che il mio indice e' shiftato di -1 rispetto alle slide)
      {
         sum += 2 * f(min + i * h);
      }
      else if (i % 2 == 1) // dispari
      {
         sum += 4 * f(min + i * h);
      }
   }

   sum += f(min) + f(max);
   sum *= h / 3;

   return sum;
}

long double simpson_open(long double f(long double), long double min, long double max) // formula aperta per simpson
{
   long double y, h;
   h = (max - min) / 5;
   y = 11.0 * (f(min + h) + f(max - h));
   y += f(min + 2 * h) + f(max - 2 * h);
   y *= h * 5 / 24;

   return y;
}

long double simpson_divergenza(long double min, long double max, int N, long double f(long double)) // formula simpson nel caso di una singolarita' integabile
{                                                                                                   // almeno 11 punti
   // per rendere intuitivo che non conto il primo punto ma gli altri sono uguali a come se facessi le formule chiuse
   //long double h = (max - min) / powl(N - 1, 1);
    long double h = (max - min) / powl(10, 3);
   //  h = powl(h,5);

   long double sum;
   sum = simpson_open(f, min, min + 5 * h);
   sum += simpson_open(f, max - 5 * h, max);
   N = N - 8;
   sum += simpson_est(min + 5 * h, max - 5 * h, N, f);

   return sum;
}

void romberg(long double min, long double max, long double (*pippo)[LENGTH], long double f(long double)) // formula di romberb
{
   for (int r = 0; r < LENGTH; r++) // riempimento colonna 0 con trapezio
   {
      pippo[r][0] = trapezio_est(min, max, ((int)powl(2, r) + 1), f);
   }

   for (int c = 1; c < LENGTH; c++) // c: colonna
   {
      for (int r = c; r < LENGTH; r++) // r: riga
      {
         pippo[r][c] = (powl(4, c) * pippo[r][c - 1] - pippo[r - 1][c - 1]) / (powl(4, c) - 1); // formula di romberg
      }
   }
}

void romberg_divergenza_trap(long double min, long double max, long double (*pippo)[LENGTH], long double f(long double)) // formula romberg nel caso di una singolarita' integabile partendo da trapezio
{
   for (int r = 3; r < LENGTH; r++)
   {
      pippo[r][0] = trapezio_divergenza(min, max, ((int)powl(2, r) + 1), f);
   }

   for (int c = 1; c < LENGTH; c++) // c: colonna
   {
      for (int r = c + 3; r < LENGTH; r++) // r: riga
      {
         pippo[r][c] = (powl(4, c) * pippo[r][c - 1] - pippo[r - 1][c - 1]) / (powl(4, c) - 1); // formula di romberg
      }
   }
}

void romberg_divergenza_sim(long double min, long double max, long double (*pippo)[LENGTH], long double f(long double)) // formula romberg nel caso di una singolarita' integabile partendo da simpson
{
   for (int j = 4; j < LENGTH; j++)
   {
      pippo[j][1] = simpson_divergenza(min, max, ((int)powl(2, j) + 1), f);
   }

   for (int c = 2; c < LENGTH; c++) // c: colonna
   {
      for (int r = c + 4; r < LENGTH; r++) // r: riga
      {
         pippo[r][c] = (powl(4, c) * pippo[r][c - 1] - pippo[r - 1][c - 1]) / (powl(4, c) - 1); // formula di romberg
      }
   }
}

long double gauss_legendre(int k, long double f(long double), long double min, long double max) // n: num punti
{
   long double *punto = NULL; // puntatori in cui copio i valori dei punti e pesi, x: punti, w: pesi
   long double *peso = NULL;
   long double A, B, Ax, s; // A: intervallo integr/2 ; B: centro interv ; Ax: dove calc funz ; s: sommatoria
   int m;

   m = (k + 1) >> 1; // m = n >> l = n*s^(-l) ; nel nostro caso m=(n+1)/2 approx per eccesso.

   /* Load appropriate predefined table */
   for (int i = 0; i < GLAWSIZE; i++)
   {
      if (k == glaw[i].n)
      {
         punto = glaw[i].x;
         peso = glaw[i].w;
         break;
      }
   }

   A = 0.5 * (max - min); // lunghezza di mezz'intervallo
   B = 0.5 * (max + min); // centro dell'intervallo

   s = 0.0;

   if (k & 1) /* n - odd */
   {
      s = peso[0] * f(B); // valore x = 0;
      for (int i = 1; i < m; i++)
      {
         Ax = A * punto[i]; // punto dove calcolare la funzione
         s += peso[i] * (f(B + Ax) + f(B - Ax));
      }
   }
   else
   { /* n - even */
      for (int i = 0; i < m; i++)
      {
         Ax = A * punto[i];
         s += peso[i] * (f(B + Ax) + f(B - Ax));
      }
   }

   return A * s; // sarebbe (2*A)*(s/2)
                 // attenz s e' calcolata su intervallo di lungh 2
}

long double gauss_laguerre(int k, long double f(long double), long double min) // con traslazione integrata
{
   long double *punto = NULL; // puntatori in cui copio i valori dei punti e pesi, x: punti, w: pesi
   long double *peso = NULL;
   long double s; // A: intervallo integr/2 ; B: centro interv ; Ax: dove calc funz ; s: sommatoria

   for (int i = 0; i < LAGSIZE; i++)
   {
      if (k == lag[i].n)
      {
         punto = lag[i].x;
         peso = lag[i].w;
         break;
      }
   }

   s = 0.0;

   for (int i = 0; i < k; i++)
   {
      s += peso[i] * f(punto[i] + min); // gli do in pasto solo la funzione f, non W
   }
   return s * expl(-min);
}

long double gauss_laguerre_finito(int k, long double f(long double), long double min, long double max)
{
   return gauss_laguerre(k, f, min) - gauss_laguerre(k, f, max);
}

long double gauss_hermite(int k, long double f(long double))
{
   long double *punto = NULL; // puntatori in cui copio i valori dei punti e pesi, x: punti, w: pesi
   long double *peso = NULL;
   long double Ax, s; // A: intervallo integr/2 ; B: centro interv ; Ax: dove calc funz ; s: sommatoria

   for (int i = 0; i < HERSIZE; i++) // questo e' un secondo controllo, non servirebbe
   {
      if (k == her[i].n)
      {
         punto = her[i].x;
         peso = her[i].w;
         break;
      }
   }

   s = 0.0;

   for (int i = 0; i < k; i++)
   {
      Ax = punto[i]; // punto dove calcolare la funzione
      s += peso[i] * f(Ax);// * expl(powl(punto[i], 2));
   }

   return s;
}

long double gauss_hermite_min(int k, long double f(long double), long double min) // dominio (min,+inf)
{
   long double *punto = NULL; // puntatori in cui copio i valori dei punti e pesi, x: punti, w: pesi
   long double *peso = NULL;
   long double Ax, s; // A: intervallo integr/2 ; B: centro interv ; Ax: dove calc funz ; s: sommatoria

   for (int i = 0; i < HERSIZE; i++) // questo e' un secondo controllo, non servirebbe
   {
      if (k == her[i].n)
      {
         punto = her[i].x;
         peso = her[i].w;
         break;
      }
   }

   s = 0.0;

   for (int i = 0; i < k; i++)
   {
      Ax = fabsl(punto[i]) + min;                                       // punto dove calcolare la funzione
      s += peso[i] * f(Ax) * expl(-min * (min + 2. * fabsl(punto[i]))); // viene contato il contributo di e^-x^2 dato dalla traslazione
   }

   return s * 0.5;
}
