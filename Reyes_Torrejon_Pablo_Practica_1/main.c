#include<stdio.h>
#include<stdlib.h>
#include"puzle.h"

int main(){
    int op;
    tEstado *n,*a;
    a=estadoInicial();
    for (op=1; op<=NUM_OPERADORES && !testObjetivo(a); op++) {
        if (esValido(op, a)){
        n=aplicaOperador(op,a);
        dispOperador(op);
        dispEstado(n);
        }
    } 
}