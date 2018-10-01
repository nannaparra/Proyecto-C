#include <stdio.h>
#include <stdlib.h>

#include "lista/lista.h"
#include "planificador/planificador.h"

int main() {
     TLista lista_ciudades = crear_lista();
    leer_archivo("archivo_texto.txt", &lista_ciudades);
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

    scanf("%i",&opcion);
    switch(opcion){
        case 1:{mostrar_ascendente(lista_ciudades);
                 break;}
        case 2:{mostrar_descendente(lista_ciudades);
                 break;}
    }
    return 0;
}
