#ifndef COLA_CP_H
#define COLA_CP_H

#include <stdio.h>
#include <stdlib.h>

#include "../lista/lista.h"
#include "../constantes.h"

/**
*   Definicion de tipos
**/
typedef void * TClave;
typedef void * TValor;

typedef struct entrada {
    TClave clave;
    TValor valor;
} * TEntrada;

typedef struct nodo {
    TEntrada entrada;
    struct nodo * padre;
    struct nodo * hijo_izquierdo;
    struct nodo * hijo_derecho;
} * TNodo;

typedef struct cola_con_prioridad {
    unsigned int cantidad_elementos;
    TNodo raiz;
} * TColaCP;

/**
* Variables
**/
int (*funcion_prioridad)(TEntrada, TEntrada);

/**
 * Crea la cola con prioridad
 * @param f Funcion de prioridad
 * @return TColaCP Retorna una cola con prioridad
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