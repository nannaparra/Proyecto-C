#include <stdio.h>
#include <stdlib.h>

#include "lista/lista.h"
#include "planificador/planificador.h"

int main(int argc, char *argv[]) {
    if (argc < 1) {
        printf("No se puede ejecutar el programa\n");
        printf("Para ejecutarlo use la siguiente sintaxis\n");
        printf("./planificador <archivo_texto>\n");
    } else {
        TLista *lista=NULL;
        TLista lista_ciudades=crear_lista(lista);
        leer_archivo(argv[1], &lista_ciudades);
        int opcion;
        printf("**************************************************\n");
        printf("|                                                |\n");
        printf("| MENU:                                          |\n");
        printf("| 1-Mostrar Ascendente.                          |\n");
        printf("| 2-Mostrar Descendente.                         |\n");
        printf("| 3-Reducir horas de manejo.                     |\n");
        printf("| 4-Salir.                                       |\n");
        printf("|                                                |\n");
        printf("**************************************************\n");

        printf("Ingrese una opcion entre (1-4) ");
        scanf("%i", &opcion);
        switch (opcion) {
            case 1: {
                mostrar_ascendente(lista_ciudades);
                break;
            }
            case 2: {
                mostrar_descendente(lista_ciudades);
                break;
            }
            case 3: {
                reducir_horas_manejo(lista_ciudades);
                break;
            }
            case 4: {
                l_destruir(&lista_ciudades);
                exit(EXIT_SUCCESS);
            }
            default:
                printf("Era una opcion entre 1-4");
                break;
        }

        l_destruir(&lista_ciudades);
    }
    return 0;
}
