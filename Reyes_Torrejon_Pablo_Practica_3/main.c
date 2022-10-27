/*******************************************/
/*             MAIN.C                      */
/*                                         */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "listaia.h"
#include "busqueda.h"

int main(){
    int lim;
    printf("EN PROFUNDIDAD:\n");
    solucionFin(busquedaProf());

    printf("EN ANCHURA:\n");
    solucionFin(busquedaAnch());
    
    printf("EN PROFUNDIDAD LIMITADA\n");
    printf("Seleccione un limite:\n");
    scanf("%d", &lim);
    solucionFin(busquedaProfLim(lim));

    printf("EN PROFNDIDAD LIMITADA ITERATIVA\n");
    printf("Seleccione un limite:\n");
    scanf("%d", &lim);
    solucionFin(busquedaProfLimIter(lim));
    return 0;
}

/*El programa está realizando la búsqueda en profundidad, y las únicas veces en las que comprueba si los estados son iguales
es comparandolo con el estado final, no se estudian aquellos estados que ya se han repetido, por tanto, como la búsqueda es 
en profundidad y no se miran por los estados repetidos, el programa entra en un bucle infinito.

La solución más adecuada sería aplicar en profundidad controlando la repeticion de los estados*/