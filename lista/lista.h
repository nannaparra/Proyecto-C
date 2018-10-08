#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

#include "../constantes.h"

typedef void * TElemento;
typedef struct celda * TLista;
typedef struct celda * TPosicion;

struct celda {
TElemento elemento;
struct celda * celda_anterior;
struct celda * celda_siguiente;
};


TLista crear_lista(TLista *lista); //Crea y retorna una lista vacía.

int l_insertar(TLista * lista, TPosicion pos, TElemento elem); /*Agrega el elemento elem en la posición pos,
dentro de la lista. Si pos es POS_NULA, insertar el elemento en la primera posición de la lista. Retorna
verdadero si procede con éxito, falso en caso contrario.*/

int l_eliminar(TLista * lista, TPosicion pos); /*Elimina el elemento en la posición pos. Reacomoda
la lista adecuadamente. Retorna verdadera si procede con éxito, falso en caso contrario.*/

TPosicion l_primera(TLista lista); /*Retorna la primera posición de la lista. Si la lista es vacía,
retorna POS_NULA. */

TPosicion l_ultima(TLista lista); /*Retorna la última posición de la lista. Si la lista es vacía,
retorna POS_NULA. */

TPosicion l_anterior(TLista lista, TPosicion pos); /*Retorna la posición anterior a pos en la lista lista.
Si pos es la primera posición de la lista, retorna POS_NULA.*/

TPosicion l_siguiente(TLista lista, TPosicion pos); /*Retorna la posición siguiente a pos en la lista lista.
Si pos es la última posición de la lista, retorna POS_NULA.*/

TElemento l_recuperar(TLista lista, TPosicion pos);/*Retorna el elemento correspondiente a la posición
pos. Si la posición es POS_NULA, retorna ELE_NULO.*/

int l_size(TLista lista); //Retorna la cantidad de elementos de la lista.

int l_destruir(TLista * lista); /*Elimina todos los elementos y liberta toda la memoria utilizada
pr la lista lista. Retorna verdadero si procede con éxito, falso en caso contrario.*/

#endif
