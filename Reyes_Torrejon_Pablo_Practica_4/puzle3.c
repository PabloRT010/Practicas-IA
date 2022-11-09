#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"puzle3.h"


tEstado *crearEstado(int puzle[N][N], int fil[N_PIEZAS], int col[N_PIEZAS])
{
   tEstado *estado = (tEstado *) malloc(sizeof(tEstado));
   int i, j, k;

   for (i=0;i<N;i++)
      for (j=0;j<N;j++){
         estado->celdas[i][j] = puzle[i][j];
        }
    for(k = 0; k <= N_PIEZAS; k++){
        estado->filas[i] = fil[i];
        estado->cols[i] = col[i];
    }
   return estado;
}


tEstado *estadoInicial()
{
   return crearEstado(puzle_inicial, filas_inicial, cols_inicial);
}


tEstado *estadoObjetivo()
{
   return crearEstado(puzle_final, filas_final, cols_final);
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
   switch(op){
      case ARRIBA_A:    printf("Movimiento ARRIBA A:\n"); break;
      case ABAJO_A:     printf("Movimiento ABAJO A:\n"); break;
      case IZQUIERDA_A: printf("Movimiento IZQUIERDA A:\n"); break;
      case DERECHA_A:   printf("Movimiento DERECHA A:\n"); break;
      case ARRIBA_B:   printf("Movimiento ARRIBA B:\n"); break;
      case ABAJO_B:    printf("Movimiento ABAJO B:\n"); break;
      case IZQUIERDA_B:     printf("Movimiento IZQUIERDA B:\n"); break;
      case DERECHA_B: printf("Movimiento DERECHA B:\n"); break;
      case ARRIBA_C:   printf("Movimiento ARRIBA C:\n"); break;
      case ABAJO_C:   printf("Movimiento ABAJO C:\n"); break;
      case IZQUIERDA_C:    printf("Movimiento IZQUIERDA C:\n"); break;
      case DERECHA_C:     printf("Movimiento DERECHA C:\n"); break;

   }
}

// FUNCIONES QUE SE HAN DE IMPLEMENTAR EN LA PRACTICA 4

// Funci�n auxiliar para comprobar si dos puzles tienen las fichas colocadas en el mismo orden en el tablero
//para ello, compara las posiciones de los centros de las piezas
int iguales(tEstado *s, tEstado *t) {

   int i = 0, j = 0, igualf = 1, igualc = 1;

   while (i < N_PIEZAS && igualf && igualc){
        igualf = s->filas[i] == t->filas[i];
        igualc = s->cols[i] == t->cols[i];
        i++;
   }
   return (igualf && igualc);
}


int testObjetivo(tEstado *estado){
   tEstado* final = estadoObjetivo();

   return iguales(estado, final);
}

//incompeto
int esValido(unsigned op, tEstado *estado){
   int valido=0, auxf, auxc;

   switch(op){
   case ABAJO_A: 
        auxf = estado->filas[A-1]; //posicion del centro de la ficha fila
        auxc = estado->cols[A-1]; //posicion del centro de la ficha columna
        
        if(auxf + 1 <= N)
            valido = estado->celdas[auxf + 2][auxc] == 0 &&  estado->celdas[auxf + 1][auxc + 1] == 0 && estado->celdas[auxf + 1][auxc - 1] == 0 ;
        break;
   case ABAJO_C: 
        auxf = estado->filas[C-1];
        auxc = estado->cols[C-1];

        if(auxf + 1 <= N)
            valido = estado->celdas[auxf + 1][auxc] == 0;
        break;
   case DERECHA_C: 
        auxf = estado->filas[C-1];
        auxc = estado->cols[C-1];
        if(auxc + 1 <= N)
            valido = estado->celdas[auxf - 1][auxc + 1] == 0 && estado->celdas[auxf][auxc + 1] == 0 && estado->celdas[auxf + 1][auxc + 1] == 0;
        break;
   case ABAJO_B: 
        auxf = estado->filas[B-1];
        auxc = estado->cols[B-1];

        if(auxf + 1 <= N)
            valido = estado->celdas[auxf + 1][auxc + 1] == 0 &&  estado->celdas[auxf + 1][auxc] == 0 && estado->celdas[auxf + 1][auxc - 1] == 0 ;
        break;
    case IZQUIERDA_B:
        auxf = estado->filas[B-1];
        auxc = estado->cols[B-1];
        if(auxc - 1 >= N)
            valido = estado->celdas[auxf - 1][auxc - 1] == 0 && estado->celdas[auxf][auxc - 2] == 0;
        break;    
   default: 
      valido=0;
   }
   return valido;

}


tEstado *aplicaOperador(unsigned op, tEstado *estado){
   tEstado *nuevo= (tEstado *) malloc(sizeof(tEstado));
   memcpy(nuevo, estado,sizeof(tEstado));  // Hace una copia del estado
    int auxf, auxc;
   switch (op){
    case ABAJO_A:
      auxf = nuevo->filas[A-1]; //posicion del centro de la ficha fila
      auxc = nuevo->cols[A-1]; //posicion del centro de la ficha columna
      //rellenar
      nuevo->celdas[auxf + 2][auxc] = 1;
      nuevo->celdas[auxf + 1][auxc + 1] = 1;
      nuevo->celdas[auxf + 1][auxc - 1] = 1;
      //vaciar
      nuevo->celdas[auxf][auxc + 1] = 0;
      nuevo->celdas[auxf][auxc - 1] = 0;
      nuevo->celdas[auxf - 1][auxc] = 0;
      //incremento fila
      nuevo->filas[A-1]++;

      break;
   case ABAJO_C:
      auxf = estado->filas[C-1];
      auxc = estado->cols[C-1];
      //rellenar
      nuevo->celdas[auxf + 1][auxc] = 3;
      //vaciar
      nuevo->celdas[auxf - 1][auxc] = 0;
      //incremento fila
      nuevo->filas[C-1]++;

      break;
   case DERECHA_C:
      auxf = estado->filas[C-1];
      auxc = estado->cols[C-1];
      //rellenar
      nuevo->celdas[auxf - 1][auxc + 1] = 3;
      nuevo->celdas[auxf + 1][auxc + 1] = 3;
      nuevo->celdas[auxf][auxc + 1] = 3;
      //vaciar
      nuevo->celdas[auxf - 1][auxc] = 0;
      nuevo->celdas[auxf][auxc] = 0;
      nuevo->celdas[auxf + 1][auxc] = 0;
      //incremento fila
      nuevo->cols[C-1]++;
      break;
   case ABAJO_B:
      auxf = estado->filas[B-1];
      auxc = estado->cols[B-1];
      //rellenar
      nuevo->celdas[auxf + 1][auxc] = 2;
      nuevo->celdas[auxf + 1][auxc + 1] = 2;
      nuevo->celdas[auxf - 1][auxc - 1] = 2;
      //vaciar
      nuevo->celdas[auxf][auxc + 1] = 0;
      nuevo->celdas[auxf][auxc - 1] = 0;
      nuevo->celdas[auxf - 1][auxc] = 0;
      //incremento fila
      nuevo->filas[B-1]++;
      break;
    case IZQUIERDA_B:
      auxf = estado->filas[B-1];
      auxc = estado->cols[B-1];
      //rellenar
      nuevo->celdas[auxf][auxc - 1] = 2;
      nuevo->celdas[auxf - 1][auxc - 1] = 2;
      //vaciar
      nuevo->celdas[auxf - 1][auxc] = 0;
      nuevo->celdas[auxf][auxc + 1] = 0;
      //incremento fila
      nuevo->cols[B-1]--;
      break;
   default:
      break;
   }
   
   return nuevo;
}

