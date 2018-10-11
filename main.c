#include <stdio.h>
#include <stdlib.h>

#include "lista/lista.h"
#include "planificador/planificador.h"

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("No se puede ejecutar el programa\n");
        printf("Para ejecutarlo use la siguiente sintaxis\n");
        printf("./planificador <archivo_texto>\n");
    } else {
        TLista *lista = (TLista *) malloc(sizeof(TLista *));
        crear_lista(lista);

        leer_archivo(argv[1], lista);

        int opcion, salir = FALSE;

        while (!salir) {
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
                    mostrar_ascendente(*lista);
                    break;
                }
                case 2: {
                    mostrar_descendente(*lista);
                    break;
                }
                case 3: {
                    reducir_horas_manejo(*lista);
                    break;
                }
                case 4: {
                    salir = TRUE;
                    break;
                }
                default:
                    printf("Era una opcion entre 1-4");
                    break;
            }
        }

        destruir_lista_ciudad(lista);
    }

    return EXIT_SUCCESS;
}
