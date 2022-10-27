/*******************************************/
/* 		      PUZLE.C                      */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "puzle.h"



tEstado *crearEstado(int puzle[N][N])
{
   tEstado *estado = (tEstado *) malloc(sizeof(tEstado));
   int i, j, ficha;

   for (i=0;i<N;i++)
      for (j=0;j<N;j++)
      {
         estado->celdas[i][j] = puzle[i][j];

         if(estado->celdas[i][j] == 0){
            estado->fila = i;
            estado->col = j;
         }
      }
   return estado;
}


tEstado *estadoInicial()
{
   return crearEstado(puzle_inicial);
}


tEstado *estadoObjetivo()
{
   return crearEstado(puzle_final);
}

int coste(unsigned op, tEstado *estado)
{
   return 1;
}

/* VISUALIZACI�N DE ESTADOS Y OPERADORES*/


void dispEstado(tEstado *estado)
{
   int i,j;

   for (i=0; i<N; i++)
   {
      for (j=0; j<N; j++)
         printf("%d",estado->celdas[i][j]);
      printf("\n");
   }
   printf("\n");
}


void dispOperador(unsigned op)
{
   switch(op)
   {
      case ARRIBA:    printf("Movimiento ARRIBA:\n"); break;
      case ABAJO:     printf("Movimiento ABAJO:\n"); break;
      case IZQUIERDA: printf("Movimiento IZQUIERDA:\n"); break;
      case DERECHA:   printf("Movimiento DERECHA:\n"); break;
   }
}

// FUNCIONES QUE SE HAN DE IMPLEMENTAR EN LA PRACTICA 1

// Funci�n auxiliar para comprobar si dos puzles tienen las fichas colocadas en el mismo orden en el tablero
int iguales(tEstado *s, tEstado *t) {

   int i = 0, j = 0, igual = 1;

   while (i < N && igual){
     while (j < N && igual){
         if (s->celdas[i][j] != t->celdas[i][j]){
            igual = 0;
         }
         j++;
      }
      j = 0;
      i++;
   }
   return igual;//si igual es > 0 significa que los estados no son iguales
}


int testObjetivo(tEstado *estado){
   tEstado* final = estadoObjetivo();

   return iguales(estado, final);
}


int esValido(unsigned op, tEstado *estado){
   int valido=0;
   switch(op){
   case ARRIBA: 
      valido = (estado->fila > 0);
      break;
   case ABAJO: 
      valido = (estado->fila < N-1);
      break;
   case IZQUIERDA: 
      valido = (estado->col > 0);
      break;
   case DERECHA: 
      valido = (estado->col < N-1);
      break;
   default: 
      valido=0;
   }
   return valido;

}


tEstado *aplicaOperador(unsigned op, tEstado *estado){
   tEstado *nuevo= (tEstado *) malloc(sizeof(tEstado));
   memcpy(nuevo, estado,sizeof(tEstado));  // Hace una copia del estado

   switch (op){
   case ARRIBA:
      nuevo->celdas[nuevo->fila][nuevo->col] = nuevo->celdas[nuevo->fila - 1][nuevo->col];
      nuevo->celdas[nuevo->fila - 1][nuevo->col] = 0;
      nuevo->fila--;
      break;
   case ABAJO:
      nuevo->celdas[nuevo->fila][nuevo->col] = nuevo->celdas[nuevo->fila + 1][nuevo->col];
      nuevo->celdas[nuevo->fila + 1][nuevo->col] = 0;
      nuevo->fila++;
      break;
   case IZQUIERDA:
      nuevo->celdas[nuevo->fila][nuevo->col] = nuevo->celdas[nuevo->fila][nuevo->col - 1];
      nuevo->celdas[nuevo->fila][nuevo->col - 1] = 0;
      nuevo->col--;
      break;
   case DERECHA:
      nuevo->celdas[nuevo->fila][nuevo->col] = nuevo->celdas[nuevo->fila][nuevo->col + 1];
      nuevo->celdas[nuevo->fila][nuevo->col + 1] = 0;
      nuevo->col++;
      break;
   default:
      break;
   }
   
   return nuevo;
}



/*tEstado *aplicaOperador(unsigned op, tEstado *estado)
{
    tEstado *nuevoEstado = (tEstado *)malloc(sizeof(tEstado));
    memcpy(nuevoEstado, estado, sizeof(tEstado));
    int inifil = estado->fila;
    int inicol = estado->col;
    switch (op)
    {
    case ARRIBA:
        nuevoEstado->fila--;
        break;
    case ABAJO:
        nuevoEstado->fila++;
        break;
    case DERECHA:
        nuevoEstado->col++;
        break;
    case IZQUIERDA:
        nuevoEstado->col--;
        break;
    }

    nuevoEstado->celdas[nuevoEstado->fila][nuevoEstado->col] = 0;
    nuevoEstado->celdas[inifil][inicol] = estado->celdas[nuevoEstado->fila][nuevoEstado->col];
    return nuevoEstado;
}*/

