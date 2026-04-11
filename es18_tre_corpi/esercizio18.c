/*
   g++ -o esercizio18.exe esercizio18.c && ./esercizio18.exe
*/

// VERSIONE COMPLETA

//
//    EQUAZIONE DIFFERENZIALE VETTORIALE DI SECONDO GRADO
//

#include <stdio.h>
#include <math.h> // dovrebbe contenere pi e ...
#include <stdlib.h>
#include <time.h>

struct part // particella
{
   double x[3]; // posizione
   double v[3]; // velocita
   double m;    // massa
};

double f(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double m2, double m3, int coord);
void step_Eulero(double h, struct part *A, struct part *B, struct part *C); // passate per puntatori
void step_RK2(double h, struct part *A, struct part *B, struct part *C);
void step_RK4(double h, struct part *A, struct part *B, struct part *C);

double ENERGIA_cinetica(struct part *A, struct part *B, struct part *C);
double ENERGIA_potenziale(struct part *A, struct part *B, struct part *C);
double ENERGIA(struct part *A, struct part *B, struct part *C);

int main()
{
   FILE *fptr;
   fptr = fopen("data.txt", "w");

   double h = 0.02; // passo temporale
   int N_PUNTI =2000;

   // DATI INIZIALI
// SET 1: h=0.015 N=400
   /*struct part P1eul = {{1, 0, 0}, {0, 0.15, -0.15}, 0.3};
   struct part P2eul = {{-1, 0, 0}, {0, -0.15, 0.15}, 0.3};
   struct part P3eul = {{0, 0, 0}, {0, 0, 0}, 0.3};*/

// SET 2: h=0.01 N=600
   
   struct part P1eul = {{1, 0, 0}, {0, 0.4, 0}, 1.6};
   struct part P2eul = {{-1, 0, 0}, {0, -0.8, 0.7}, 0.4};
   struct part P3eul = {{0, 0, 0}, {0, -0.8, -0.7}, 0.4};
   

   struct part P1run2 = P1eul;
   struct part P2run2 = P2eul;
   struct part P3run2 = P3eul;

   struct part P1run4 = P1eul;
   struct part P2run4 = P2eul;
   struct part P3run4 = P3eul;

   for (int i = 0; i < N_PUNTI; i++)
   {
      fprintf(fptr, "%f ", i * h);

      // EULERO
      fprintf(fptr, "%f ", P1eul.x[0]); // x eulero
      fprintf(fptr, "%f ", P1eul.x[1]); // y eulero
      fprintf(fptr, "%f ", P1eul.x[2]); // z eulero
      fprintf(fptr, "%f ", P2eul.x[0]);
      fprintf(fptr, "%f ", P2eul.x[1]);
      fprintf(fptr, "%f ", P2eul.x[2]);
      fprintf(fptr, "%f ", P3eul.x[0]);
      fprintf(fptr, "%f ", P3eul.x[1]);
      fprintf(fptr, "%f ", P3eul.x[2]);

      // RUNGE2
      fprintf(fptr, "%f ", P1run2.x[0]); // x
      fprintf(fptr, "%f ", P1run2.x[1]); // y
      fprintf(fptr, "%f ", P1run2.x[2]); // z
      fprintf(fptr, "%f ", P2run2.x[0]);
      fprintf(fptr, "%f ", P2run2.x[1]);
      fprintf(fptr, "%f ", P2run2.x[2]);
      fprintf(fptr, "%f ", P3run2.x[0]);
      fprintf(fptr, "%f ", P3run2.x[1]);
      fprintf(fptr, "%f ", P3run2.x[2]);

      // RUNGE4
      fprintf(fptr, "%f ", P1run4.x[0]); // x
      fprintf(fptr, "%f ", P1run4.x[1]); // y
      fprintf(fptr, "%f ", P1run4.x[2]); // z
      fprintf(fptr, "%f ", P2run4.x[0]);
      fprintf(fptr, "%f ", P2run4.x[1]);
      fprintf(fptr, "%f ", P2run4.x[2]);
      fprintf(fptr, "%f ", P3run4.x[0]);
      fprintf(fptr, "%f ", P3run4.x[1]);
      fprintf(fptr, "%f ", P3run4.x[2]);

      // ENERGIA
      fprintf(fptr, "%f ", ENERGIA_cinetica(&P1eul, &P2eul, &P3eul));
      fprintf(fptr, "%f ", ENERGIA_potenziale(&P1eul, &P2eul, &P3eul));
      fprintf(fptr, "%f ", ENERGIA(&P1eul, &P2eul, &P3eul));
      fprintf(fptr, "%f ", ENERGIA_cinetica(&P1run2, &P2run2, &P3run2));
      fprintf(fptr, "%f ", ENERGIA_potenziale(&P1run2, &P2run2, &P3run2));
      fprintf(fptr, "%f ", ENERGIA(&P1run2, &P2run2, &P3run2));
      fprintf(fptr, "%f ", ENERGIA_cinetica(&P1run4, &P2run4, &P3run4));
      fprintf(fptr, "%f ", ENERGIA_potenziale(&P1run4, &P2run4, &P3run4));
      fprintf(fptr, "%f\n", ENERGIA(&P1run4, &P2run4, &P3run4));

      // funzione 1
      step_Eulero(h, &P1eul, &P2eul, &P3eul);
      step_RK2(h, &P1run2, &P2run2, &P3run2);
      step_RK4(h, &P1run4, &P2run4, &P3run4);
   }

   fclose(fptr);
   return 0;
}

double f(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double m2, double m3, int coord)
{
   double dx12 = x1 - x2;
   double dy12 = y1 - y2;
   double dz12 = z1 - z2;

   double dx13 = x1 - x3;
   double dy13 = y1 - y3;
   double dz13 = z1 - z3;

   double modulo12 = sqrt(pow(dx12, 2) + pow(dy12, 2) + pow(dz12, 2));
   double modulo13 = sqrt(pow(dx13, 2) + pow(dy13, 2) + pow(dz13, 2));

   if (coord == 0)
   {
      return -dx12 * m2 / pow(modulo12, 3) - dx13 * m3 / pow(modulo13, 3);
   }
   else if (coord == 1)
   {
      return -dy12 * m2 / pow(modulo12, 3) - dy13 * m3 / pow(modulo13, 3);
   }
   else if (coord == 2)
   {
      return -dz12 * m2 / pow(modulo12, 3) - dz13 * m3 / pow(modulo13, 3);
   }
}

void step_Eulero(double h, struct part *A, struct part *B, struct part *C) // passate per puntatori
{
   double k1P1[2][3]; // posizione (x y z), velocita (x y z)
   double k1P2[2][3];
   double k1P3[2][3];

   for (int i = 0; i < 3; i++)
   {
      k1P1[1][i] = h * f(A->x[0], A->x[1], A->x[2], B->x[0], B->x[1], B->x[2], C->x[0], C->x[1], C->x[2], B->m, C->m, i);
      k1P2[1][i] = h * f(B->x[0], B->x[1], B->x[2], A->x[0], A->x[1], A->x[2], C->x[0], C->x[1], C->x[2], A->m, C->m, i);
      k1P3[1][i] = h * f(C->x[0], C->x[1], C->x[2], A->x[0], A->x[1], A->x[2], B->x[0], B->x[1], B->x[2], A->m, C->m, i);

      k1P1[0][i] = h * A->v[i];
      k1P2[0][i] = h * B->v[i];
      k1P3[0][i] = h * C->v[i];
   }

   for (int i = 0; i < 3; i++)
   {
      A->v[i] += k1P1[1][i];
      B->v[i] += k1P2[1][i];
      C->v[i] += k1P3[1][i];

      A->x[i] += k1P1[0][i];
      B->x[i] += k1P2[0][i];
      C->x[i] += k1P3[0][i];
   }
}

void step_RK2(double h, struct part *A, struct part *B, struct part *C)
{
   double k1P1[2][3]; // posizione (x y z), velocita (x y z)
   double k1P2[2][3];
   double k1P3[2][3];

   double k2P1[2][3]; // posizione (x y z), velocita (x y z)
   double k2P2[2][3];
   double k2P3[2][3];

   for (int i = 0; i < 3; i++)
   {
      k1P1[1][i] = h * f(A->x[0], A->x[1], A->x[2], B->x[0], B->x[1], B->x[2], C->x[0], C->x[1], C->x[2], B->m, C->m, i);
      k1P2[1][i] = h * f(B->x[0], B->x[1], B->x[2], A->x[0], A->x[1], A->x[2], C->x[0], C->x[1], C->x[2], A->m, C->m, i);
      k1P3[1][i] = h * f(C->x[0], C->x[1], C->x[2], A->x[0], A->x[1], A->x[2], B->x[0], B->x[1], B->x[2], A->m, C->m, i);

      k1P1[0][i] = h * A->v[i];
      k1P2[0][i] = h * B->v[i];
      k1P3[0][i] = h * C->v[i];
   }

   for (int i = 0; i < 3; i++)
   {
      k2P1[1][i] = h * f(A->x[0] + k1P1[0][0] / 2, A->x[1] + k1P1[0][1] / 2, A->x[2] + k1P1[0][2] / 2, B->x[0] + k1P2[0][0] / 2, B->x[1] + k1P2[0][1] / 2, B->x[2] + k1P2[0][2] / 2, C->x[0] + k1P3[0][0] / 2, C->x[1] + k1P3[0][1] / 2, C->x[2] + k1P3[0][2] / 2, B->m, C->m, i);
      k2P2[1][i] = h * f(B->x[0] + k1P2[0][0] / 2, B->x[1] + k1P2[0][1] / 2, B->x[2] + k1P2[0][2] / 2, A->x[0] + k1P1[0][0] / 2, A->x[1] + k1P1[0][1] / 2, A->x[2] + k1P1[0][2] / 2, C->x[0] + k1P3[0][0] / 2, C->x[1] + k1P3[0][1] / 2, C->x[2] + k1P3[0][2] / 2, A->m, C->m, i);
      k2P3[1][i] = h * f(C->x[0] + k1P3[0][0] / 2, C->x[1] + k1P3[0][1] / 2, C->x[2] + k1P3[0][2] / 2, A->x[0] + k1P1[0][0] / 2, A->x[1] + k1P1[0][1] / 2, A->x[2] + k1P1[0][2] / 2, B->x[0] + k1P2[0][0] / 2, B->x[1] + k1P2[0][1] / 2, B->x[2] + k1P2[0][2] / 2, A->m, C->m, i);

      k2P1[0][i] = h * (A->v[i] + k1P1[1][i] / 2);
      k2P2[0][i] = h * (B->v[i] + k1P2[1][i] / 2);
      k2P3[0][i] = h * (C->v[i] + k1P3[1][i] / 2);
   }

   for (int i = 0; i < 3; i++)
   {
      A->v[i] += k2P1[1][i];
      B->v[i] += k2P2[1][i];
      C->v[i] += k2P3[1][i];

      A->x[i] += k2P1[0][i];
      B->x[i] += k2P2[0][i];
      C->x[i] += k2P3[0][i];
   }
}

void step_RK4(double h, struct part *A, struct part *B, struct part *C)
{
   double k1P1[2][3]; // posizione (x y z), velocita (x y z)
   double k1P2[2][3];
   double k1P3[2][3];

   double k2P1[2][3]; // posizione (x y z), velocita (x y z)
   double k2P2[2][3];
   double k2P3[2][3];

   double k3P1[2][3]; // posizione (x y z), velocita (x y z)
   double k3P2[2][3];
   double k3P3[2][3];

   double k4P1[2][3]; // posizione (x y z), velocita (x y z)
   double k4P2[2][3];
   double k4P3[2][3];

   for (int i = 0; i < 3; i++)
   {
      k1P1[1][i] = h * f(A->x[0], A->x[1], A->x[2], B->x[0], B->x[1], B->x[2], C->x[0], C->x[1], C->x[2], B->m, C->m, i);
      k1P2[1][i] = h * f(B->x[0], B->x[1], B->x[2], A->x[0], A->x[1], A->x[2], C->x[0], C->x[1], C->x[2], A->m, C->m, i);
      k1P3[1][i] = h * f(C->x[0], C->x[1], C->x[2], A->x[0], A->x[1], A->x[2], B->x[0], B->x[1], B->x[2], A->m, C->m, i);

      k1P1[0][i] = h * A->v[i];
      k1P2[0][i] = h * B->v[i];
      k1P3[0][i] = h * C->v[i];
   }

   for (int i = 0; i < 3; i++)
   {
      k2P1[1][i] = h * f(A->x[0] + k1P1[0][0] / 2, A->x[1] + k1P1[0][1] / 2, A->x[2] + k1P1[0][2] / 2, B->x[0] + k1P2[0][0] / 2, B->x[1] + k1P2[0][1] / 2, B->x[2] + k1P2[0][2] / 2, C->x[0] + k1P3[0][0] / 2, C->x[1] + k1P3[0][1] / 2, C->x[2] + k1P3[0][2] / 2, B->m, C->m, i);
      k2P2[1][i] = h * f(B->x[0] + k1P2[0][0] / 2, B->x[1] + k1P2[0][1] / 2, B->x[2] + k1P2[0][2] / 2, A->x[0] + k1P1[0][0] / 2, A->x[1] + k1P1[0][1] / 2, A->x[2] + k1P1[0][2] / 2, C->x[0] + k1P3[0][0] / 2, C->x[1] + k1P3[0][1] / 2, C->x[2] + k1P3[0][2] / 2, A->m, C->m, i);
      k2P3[1][i] = h * f(C->x[0] + k1P3[0][0] / 2, C->x[1] + k1P3[0][1] / 2, C->x[2] + k1P3[0][2] / 2, A->x[0] + k1P1[0][0] / 2, A->x[1] + k1P1[0][1] / 2, A->x[2] + k1P1[0][2] / 2, B->x[0] + k1P2[0][0] / 2, B->x[1] + k1P2[0][1] / 2, B->x[2] + k1P2[0][2] / 2, A->m, C->m, i);

      k2P1[0][i] = h * (A->v[i] + k1P1[1][i] / 2);
      k2P2[0][i] = h * (B->v[i] + k1P2[1][i] / 2);
      k2P3[0][i] = h * (C->v[i] + k1P3[1][i] / 2);
   }

   for (int i = 0; i < 3; i++)
   {
      k3P1[1][i] = h * f(A->x[0] + k2P1[0][0] / 2, A->x[1] + k2P1[0][1] / 2, A->x[2] + k2P1[0][2] / 2, B->x[0] + k2P2[0][0] / 2, B->x[1] + k2P2[0][1] / 2, B->x[2] + k2P2[0][2] / 2, C->x[0] + k2P3[0][0] / 2, C->x[1] + k2P3[0][1] / 2, C->x[2] + k2P3[0][2] / 2, B->m, C->m, i);
      k3P2[1][i] = h * f(B->x[0] + k2P2[0][0] / 2, B->x[1] + k2P2[0][1] / 2, B->x[2] + k2P2[0][2] / 2, A->x[0] + k2P1[0][0] / 2, A->x[1] + k2P1[0][1] / 2, A->x[2] + k2P1[0][2] / 2, C->x[0] + k2P3[0][0] / 2, C->x[1] + k2P3[0][1] / 2, C->x[2] + k2P3[0][2] / 2, A->m, C->m, i);
      k3P3[1][i] = h * f(C->x[0] + k2P3[0][0] / 2, C->x[1] + k2P3[0][1] / 2, C->x[2] + k2P3[0][2] / 2, A->x[0] + k2P1[0][0] / 2, A->x[1] + k2P1[0][1] / 2, A->x[2] + k2P1[0][2] / 2, B->x[0] + k2P2[0][0] / 2, B->x[1] + k2P2[0][1] / 2, B->x[2] + k2P2[0][2] / 2, A->m, C->m, i);

      k3P1[0][i] = h * (A->v[i] + k2P1[1][i] / 2);
      k3P2[0][i] = h * (B->v[i] + k2P2[1][i] / 2);
      k3P3[0][i] = h * (C->v[i] + k2P3[1][i] / 2);
   }

   for (int i = 0; i < 3; i++)
   {
      k4P1[1][i] = h * f(A->x[0] + k3P1[0][0], A->x[1] + k3P1[0][1], A->x[2] + k3P1[0][2], B->x[0] + k3P2[0][0], B->x[1] + k3P2[0][1], B->x[2] + k3P2[0][2], C->x[0] + k3P3[0][0], C->x[1] + k3P3[0][1], C->x[2] + k3P3[0][2], B->m, C->m, i);
      k4P2[1][i] = h * f(B->x[0] + k3P2[0][0], B->x[1] + k3P2[0][1], B->x[2] + k3P2[0][2], A->x[0] + k3P1[0][0], A->x[1] + k3P1[0][1], A->x[2] + k3P1[0][2], C->x[0] + k3P3[0][0], C->x[1] + k3P3[0][1], C->x[2] + k3P3[0][2], A->m, C->m, i);
      k4P3[1][i] = h * f(C->x[0] + k3P3[0][0], C->x[1] + k3P3[0][1], C->x[2] + k3P3[0][2], A->x[0] + k3P1[0][0], A->x[1] + k3P1[0][1], A->x[2] + k3P1[0][2], B->x[0] + k3P2[0][0], B->x[1] + k3P2[0][1], B->x[2] + k3P2[0][2], A->m, C->m, i);

      k4P1[0][i] = h * (A->v[i] + k3P1[1][i]);
      k4P2[0][i] = h * (B->v[i] + k3P2[1][i]);
      k4P3[0][i] = h * (C->v[i] + k3P3[1][i]);
   }

   for (int i = 0; i < 3; i++)
   {
      A->v[i] += (k1P1[1][i] + 2 * k2P1[1][i] + 2 * k3P1[1][i] + k4P1[1][i]) / 6;
      B->v[i] += (k1P2[1][i] + 2 * k2P2[1][i] + 2 * k3P2[1][i] + k4P2[1][i]) / 6;
      C->v[i] += (k1P3[1][i] + 2 * k2P3[1][i] + 2 * k3P3[1][i] + k4P3[1][i]) / 6;

      A->x[i] += (k1P1[0][i] + 2 * k2P1[0][i] + 2 * k3P1[0][i] + k4P1[0][i]) / 6;
      B->x[i] += (k1P2[0][i] + 2 * k2P2[0][i] + 2 * k3P2[0][i] + k4P2[0][i]) / 6;
      C->x[i] += (k1P3[0][i] + 2 * k2P3[0][i] + 2 * k3P3[0][i] + k4P3[0][i]) / 6;
   }
}

double ENERGIA_cinetica(struct part *A, struct part *B, struct part *C)
{
   double energia;

   double moduloSQ1 = pow(A->v[0], 2) + pow(A->v[1], 2) + pow(A->v[2], 2);
   double moduloSQ2 = pow(B->v[0], 2) + pow(B->v[1], 2) + pow(B->v[2], 2);
   double moduloSQ3 = pow(C->v[0], 2) + pow(C->v[1], 2) + pow(C->v[2], 2);

   energia = 0.5 * (A->m * moduloSQ1 + B->m * moduloSQ2 + C->m * moduloSQ3);

   return energia;
}

double ENERGIA_potenziale(struct part *A, struct part *B, struct part *C)
{
   double energia;

   double dx12 = A->x[0] - B->x[0];
   double dy12 = A->x[1] - B->x[1];
   double dz12 = A->x[2] - B->x[2];

   double dx13 = A->x[0] - C->x[0];
   double dy13 = A->x[1] - C->x[1];
   double dz13 = A->x[2] - C->x[2];

   double dx23 = B->x[0] - C->x[0];
   double dy23 = B->x[1] - C->x[1];
   double dz23 = B->x[2] - C->x[2];

   double modulo12 = sqrt(pow(dx12, 2) + pow(dy12, 2) + pow(dz12, 2));
   double modulo13 = sqrt(pow(dx13, 2) + pow(dy13, 2) + pow(dz13, 2));
   double modulo23 = sqrt(pow(dx23, 2) + pow(dy23, 2) + pow(dz23, 2));

   energia = -((A->m * B->m / modulo12) + (B->m * C->m / modulo23) + (C->m * A->m / modulo13));

   return energia;
}

double ENERGIA(struct part *A, struct part *B, struct part *C)
{
   return ENERGIA_potenziale(A, B, C) + ENERGIA_cinetica(A, B, C);
}