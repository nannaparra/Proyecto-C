#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../lista/lista.h"
#include "../colacp/colacp.h"
#include "../constantes.h"

typedef struct ciudad {
    char *nombre;
    float pos_x;
    float pos_y;
} *TCiudad;

/**
 * Lee el archivo pasado por parametro y lo carga a la lista por parametro
 * @param Direccion del archivo
 * @param Lista para los ciudades
 */
void leer_archivo(char *, TLista *);

/**
 * Muestra la lista de forma ascendente en funcion de la distancia de la ciudad a la actual
 * @param Lista de las ciudades
 */
void mostrar_ascendente(TLista);

/**
 * Muestra la lista de forma descendente en funcion de la distancia de la ciudad a la actual
 * @param Lista de las ciudades
 */
void mostrar_descendente(TLista);

/**
 * Muestra la lista de forma de la ciudad mas cercana a la mas lejana a la actual
 * @param Lista de las ciudades
 */
void reducir_horas_manejo(TLista);

/**
 * Destruye la ciudades y la lista
 */
void destruir_lista_ciudad(TLista *);