#include <stddef.h>

#include "prev.h"

void asignarPrev(Nodo *t, Nodo **pprev) {
  //Primero revisamos el caso base que es cuando el árbol está vacío.
    if (t == NULL) {
        return; 
    }

    //En caso de que el árbol no sea vacío, recorremos recurvisamente el arbol izq.
    asignarPrev(t->izq, pprev);

    //Asignamos los nodos previos y los próximos quedan en NULL para asegurarnos que no queden residuos de memoria.
    t->prev = *pprev;
    t->prox = NULL;
    
    //Se asigna el nodo próximo .
    if (*pprev != NULL) {
        (*pprev)->prox = t;
    }

    //Antes de continuar el recorrido, asignamos t a *pprev
    *pprev = t;

    //Luego, llamamos recursivamente al subárbol derecho y repetimos el algoritmo
    asignarPrev(t->der, pprev);
}

