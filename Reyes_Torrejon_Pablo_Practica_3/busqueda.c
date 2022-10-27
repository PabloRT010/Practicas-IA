/*******************************************/
/* 		    BUSQUEDA.C                     */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "listaia.h"
#include "busqueda.h"


void solucionFin(int res){
   printf("\nFin de la busqueda\n");
    if (res)
      printf("Se ha llegado al objetivo\n");
   else
      printf("No se ha llegado al objetivo\n");
}
void dispNodo(tNodo *nodo){
    dispEstado(nodo->estado);
    printf("\n");
}
void dispCamino(tNodo *nodo){
    if (nodo->padre==NULL){
        printf("\n Desde el inicio\n");
        dispEstado(nodo->estado);
    }
    else {
        dispCamino(nodo->padre);
         dispOperador(nodo->operador);
        dispEstado(nodo->estado);
    }
}

void dispSolucion(tNodo *nodo){
   printf("Profundidad=%d\n",nodo->profundidad);
   printf("Coste=%d\n",nodo->costeCamino);
   dispCamino(nodo);
}


/* Crea el nodo ra�z. */
tNodo *nodoInicial(){
   tNodo *inicial=(tNodo *) malloc(sizeof(tNodo));
   inicial->estado=estadoInicial();
   inicial->padre=NULL;
   inicial->costeCamino=0;
   inicial->profundidad=0;
   return inicial;
}

LISTA expandir(tNodo *nodo){
    unsigned op;
    LISTA sucesores=VACIA;
    tNodo *nuevo=calloc(1,sizeof(tNodo));
    tEstado *s;
    for (op=1; op<=NUM_OPERADORES;op++){
      if (esValido(op,nodo->estado)){
                        //s=(tEstado *)calloc(1,sizeof(tEstado));
          s=aplicaOperador(op,nodo->estado);
          nuevo->estado=s;
          nuevo->padre=nodo;
          nuevo->operador=op;
          nuevo->costeCamino=nodo->costeCamino + coste(op,nodo->estado);
          nuevo->profundidad=nodo->profundidad+1;
          InsertarUltimo(&sucesores,  (tNodo *) nuevo, (sizeof (tNodo)));
      }
  }
return sucesores;
}

int busquedaProf(){
    int objetivo=0, visitados=0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Sucesores= VACIA;
    LISTA Cerrados= VACIA;
    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo){
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        visitados++;
        objetivo=testObjetivo(Actual->estado);
        if (!objetivo && !buscaRepe(Actual, Cerrados)){
            Sucesores = expandir(Actual);
            //InsertarPrimero(&Cerrados,(tNodo*) Actual, sizeof(tNodo));
            Abiertos=Concatenar(Sucesores, Abiertos); //PROFUNDIDAD
            InsertarUltimo(&Cerrados,(tNodo*) Actual, sizeof(tNodo));
      }
   }//while
   
    printf("\nVisitados= %d\n", visitados);
    if (objetivo)
        dispSolucion(Actual);
    //free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

int busquedaAnch(){
    int objetivo=0, visitados=0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Sucesores= VACIA;
    LISTA Cerrados= VACIA;
    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo){
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        visitados++;
        objetivo=testObjetivo(Actual->estado);
        if (!objetivo && !buscaRepe(Actual, Cerrados)){
            Sucesores = expandir(Actual);
            //InsertarPrimero(&Cerrados,(tNodo*) Actual, sizeof(tNodo));
            Abiertos=Concatenar(Abiertos, Sucesores); //ANCHURA
            InsertarUltimo(&Cerrados,(tNodo*) Actual, sizeof(tNodo));
      }
   }//while
   
    printf("\nVisitados= %d\n", visitados);
    if (objetivo)
        dispSolucion(Actual);
    //free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

int busquedaProfLim(int lim){
    int objetivo=0, visitados=0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;
    LISTA Sucesores= VACIA;
    LISTA Cerrados= VACIA;
    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo){
        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        visitados++;
        objetivo=testObjetivo(Actual->estado);
        if (!objetivo && Actual->profundidad < lim && !buscaRepe(Actual, Cerrados)){
            Sucesores = expandir(Actual);
            //InsertarPrimero(&Cerrados,(tNodo*) Actual, sizeof(tNodo));
            Abiertos=Concatenar(Sucesores, Abiertos); //PROFUNDIDAD
            InsertarUltimo(&Cerrados,(tNodo*) Actual, sizeof(tNodo));
      }
   }//while
   
    printf("\nVisitados= %d\n", visitados);
    if (objetivo)
        dispSolucion(Actual);
    //free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

int busquedaProfLimIter(int lim){
    int objetivo = 0, i = 0;

    while(!objetivo && i <= lim){
        objetivo = busquedaProfLim(i);
        i++;
    }

    return objetivo;
}

int buscaRepe(tNodo* s, LISTA C){
   int rep = 0;
    tNodo *n = (tNodo *)calloc(1, sizeof(tNodo));
    LISTA p = C;
    while (p != NULL && !rep){
        ExtraerPrimero(p, n, sizeof(tNodo));
        rep = iguales(s->estado, n->estado);
        p = p->next;
    }

    return rep;
}