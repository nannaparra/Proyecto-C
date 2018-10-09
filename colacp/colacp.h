#ifndef COLA_CP_H
#define COLA_CP_H

#include <stdio.h>
#include <stdlib.h>

#include "../lista/lista.h"
#include "../constantes.h"

/**
 * @file
 */

/**
 * Clave
 */
typedef void * TClave;

/**
 * Valor
 */
typedef void * TValor;

/**
 * Entrada
 */
typedef struct entrada {
    /**
     * Clave de la entrada
     */
    TClave clave;

    /**
     * Valor de la entrada
     */
    TValor valor;
} * TEntrada;

/**
 * Nodo
 */
typedef struct nodo {
    /**
     * Entrada del nodo
     */
    TEntrada entrada;

    /**
     * Nodo padre
     */
    struct nodo * padre;

    /**
     * Hijo izquierdo
     */
    struct nodo * hijo_izquierdo;

    /**
     * Hijo derecho
     */
    struct nodo * hijo_derecho;
} * TNodo;

/**
 * Cola con prioridad
 */
typedef struct cola_con_prioridad {
    /**
     * Cantidad de elementos
     */
    unsigned int cantidad_elementos;

    /**
     * Nodo raiz
     */
    TNodo raiz;
} * TColaCP;

/**
 * Referencia a la funcion con prioridad
 * @return 1 si la primera entrada tiene mayor prioridad, 0 si tiene la misma prioridad,
 * -1 si tiene menos prioridad
 */
int (*funcion_prioridad)(TEntrada, TEntrada);

/**
 * Crea la cola con prioridad en la referencia pasada por parametro
 * @param cola Referencia a la cola
 * @param f Funcion de prioridad
 */
void crear_cola_CP(TColaCP *cola, int (*f)(TEntrada, TEntrada));

/**
 * Inserta un elemento a la cola pasada por parametro
 * @param cola Cola en donde insertar el elemento
 * @param entr Entrada del nodo a agregar
 * @return int Si se inserto el elemento correctamente TRUE sino FALSE
 */
int cp_insertar(TColaCP cola, TEntrada entr);

/**
 * Elimina un elemento de la cola pasa por parametro y devuelve la entrada del elemento eliminado
 * @param cola Cola de la cual eliminar un elemento
 * @return TEntrada entrada del elemento eliminado
 */
TEntrada cp_eliminar(TColaCP cola);

/**
 * Devuelve la cantidad de elementos de una cola
 * @param cola Cola de la cual devuelve la cantidad de elementos
 * @return int Cantidad de elementos de una cola
 */
int cp_size(TColaCP cola);

/**
 * Destruye la cola con prioridad
 * @param cola Cola a destruir
 * @return int Si se destruyo correctamente TRUE sino FALSE
 */
int cp_destruir(TColaCP cola);

#endif