#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

#include "../constantes.h"

/**
 * @file
 */

/**
 * Elemento
 */
typedef void * TElemento;

/**
 * Lista
 */
typedef struct celda * TLista;

/**
 * Posicion
 */
typedef struct celda * TPosicion;

/**
 * Celda
 */
struct celda {
    /**
     * Elemento de la celda
     */
    TElemento elemento;

    /**
     * Celda anterior
     */
    struct celda * celda_anterior;

    /**
     * Celda siguiente
     */
    struct celda * celda_siguiente;
};

/**
 * Crea una lista vacia en el puntero pasado por parametro
 * @param lista Puntero de la lista
 */
void crear_lista(TLista *lista); //Crea y retorna una lista vacía.

/**
 * Inserta un elemento dentro de la lista
 * @param lista Lista en la cual insertar el elemento
 * @param pos Posicion donde insertar, si es POS_NULA se inserta en la primera posicion
 * @param elem Elemento a insertar
 * @return Verdadero si se inserto con exito sino falso
 */
int l_insertar(TLista * lista, TPosicion pos, TElemento elem);

/**
 * Elimina la posicion pasada por parametro
 * @param lista Lista de la cual eliminar la posicion
 * @param pos Posicion a eliminar
 * @return Verdadero si se elimina con exito sino falso
 */
int l_eliminar(TLista * lista, TPosicion pos);

/**
 * Retorna la primera posicion de la lista
 * @param lista Lista de la cual obtener la posicion
 * @return Primera posicion de la lista
 */
TPosicion l_primera(TLista lista);

/**
 * Retorna la ultima posicion de la lista
 * @param lista Lista de la cual obtener la posicion
 * @return Ultima posicion de la lista
 */
TPosicion l_ultima(TLista lista);

/**
 * Retorna la posicion anterior de la posicion pasada por parametro
 * @param lista Lista de la cual obtener la posicion
 * @param pos Posicion de referencia
 * @return Posicion anterior a la pasada por parametro si es la primera posicion retorna POS_NULA
 */
TPosicion l_anterior(TLista lista, TPosicion pos);

/**
 * Retorna la posicion siguiente de la posicion pasada por parametro
 * @param lista Lista de la cual obtener la posicion
 * @param pos Posicion de referencia
 * @return Posicion siguiente a la pasada por parametro si es la ultima posicion retorna POS_NULA
 */
TPosicion l_siguiente(TLista lista, TPosicion pos);

/**
 * Retorna el elemento en la posicion pasada por parametro
 * @param lista Lista de la cual obtener la posicion
 * @param pos Posicion de la cual obtener el elemento
 * @return Elemento de la posicion, si la posicion es nula retorna ELE_NULO
 */
TElemento l_recuperar(TLista lista, TPosicion pos);

/**
 * Retorna la cantidad de elementos de la lista
 * @param lista Lista de la cual contar los elementos
 * @return Cantidad de elementos de la lista
 */
int l_size(TLista lista);

/**
 * Elimina la lista y todas sus posiciones para liberar la memoria
 * @param lista Lista a eliminar
 * @return Verdadero si la elimina con exito sino falso
 */
int l_destruir(TLista * lista); /*Elimina todos los elementos y liberta toda la memoria utilizada
pr la lista lista. Retorna verdadero si procede con éxito, falso en caso contrario.*/

#endif
