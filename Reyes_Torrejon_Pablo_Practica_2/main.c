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
    solucionFin(busqueda());
    return 0;
}

/*El programa está realizando la búsqueda en profundidad, y las únicas veces en las que comprueba si los estados son iguales
es comparandolo con el estado final, no se estudian aquellos estados que ya se han repetido, por tanto, como la búsqueda es 
en profundidad y no se miran por los estados repetidos, el programa entra en un bucle infinito.

La solución más adecuada sería aplicar en profundidad controlando la repeticion de los estados*/