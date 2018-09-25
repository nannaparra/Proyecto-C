#include <stdio.h>
#include <stdlib.h>

#include "lista/lista.h"
#include "planificador/planificador.h"

int main() {
    TLista lista_ciudades = crear_lista();
    leer_archivo("archivo_texto.txt", lista_ciudades);
}
