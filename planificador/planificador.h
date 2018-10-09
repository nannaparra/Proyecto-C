#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../lista/lista.h"
#include "../colacp/colacp.h"
#include "../constantes.h"
/**
 * @file
 */

/**
 * Ciudad
 */
typedef struct ciudad {
    /**
     * Nombre de la ciudad
     */
    char *nombre;
    /**
     * Posicion en x de la ciudad
     */
    float pos_x;
    /**
     * Posicion en y de la ciudad
     */
    float pos_y;
} *TCiudad;

/** Lee el archivo pasado por parametro y lo carga a la lista por parametro
 * @param path_archivo Direccion del archivo
 * @param lista_ciudades Lista para los ciudades
 */
void leer_archivo(char *path_archivo, TLista *lista_ciudades);

/**
 * Muestra la lista de forma ascendente en funcion de la distancia de la ciudad a la actual
 * @param lista_ciudades Lista de las ciudades
 */
void mostrar_ascendente(TLista lista_ciudades);

/**
 * Muestra la lista de forma descendente en funcion de la distancia de la ciudad a la actual
 * @param lista_ciudades Lista de las ciudades
 */
void mostrar_descendente(TLista lista_ciudades);

/**
 * Muestra la lista de forma de la ciudad mas cercana a la mas lejana a la actual
 * @param lista_ciudades Lista de las ciudades
 */
void reducir_horas_manejo(TLista lista_ciudades);

/**
 * Destruye la ciudades y la lista
 * @param lista Lista a destruir
 */
void destruir_lista_ciudad(TLista* lista);