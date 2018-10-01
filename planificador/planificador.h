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

void leer_archivo(char *path_archivo, TLista *lista_ciudades);

void mostrar_ascendente(TLista lista_ciudades );

void mostrar_descendente(TLista lista_ciudades);
