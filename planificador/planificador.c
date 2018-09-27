#include "planificador.h"
TCiudad ciudad_actual;

int distancia(TCiudad ciudad1, TCiudad ciudad2) {
    return abs(ciudad2->pos_x - ciudad1->pos_x) + abs(ciudad2->pos_y - ciudad1->pos_y);
}

int prioridad_descendente(TEntrada entrada1, TEntrada entrada2) {
    if (distancia(entrada1->clave, ciudad_actual) < distancia(entrada2->clave, ciudad_actual)) {
        return 1;
    } else if (distancia(entrada1->clave, ciudad_actual) > distancia(entrada2->clave, ciudad_actual)) {
        return -1;
    } else {
        return 0;
    }
}

void leer_nombre(TCiudad ciudad, FILE *archivo) {
    char nombre_final[100];
    int caracter_leido = fgetc(archivo);
    unsigned int contador = 0;

    while (caracter_leido != ';' && contador < 100) {
        nombre_final[contador] = (char) caracter_leido;

        contador++;
        caracter_leido = fgetc(archivo);
    }

    ciudad->nombre = (char *) malloc(contador + 1);

    memcpy(ciudad->nombre, nombre_final, contador);
    ciudad->nombre[contador + 1] = '\0';
}

void leer_archivo(char *path_archivo, TLista *lista_ciudades) {
    FILE *archivo_ciudades = fopen(path_archivo, "r");
    boolean primera_linea = TRUE;
    TCiudad ciudad_leida;

    while(!feof(archivo_ciudades)) {
        if (primera_linea) {
            ciudad_actual = (TCiudad) malloc(sizeof(TCiudad));

            fscanf(archivo_ciudades, "%f;%f\n", &ciudad_actual->pos_x, &ciudad_actual->pos_y);

            primera_linea = FALSE;
        } else {
            ciudad_leida = (TCiudad) malloc(sizeof(TCiudad));

            leer_nombre(ciudad_leida, archivo_ciudades);

            fscanf(archivo_ciudades, "%f;%f\n", &ciudad_leida->pos_x, &ciudad_leida->pos_y);

            l_insertar(lista_ciudades, POS_NULA, ciudad_leida);
        }
    }

    fclose(archivo_ciudades);
}

void mostrar_descendente(TLista lista_ciudades) {
    TColaCP colaCP = crear_cola_CP(&prioridad_descendente);
    TPosicion actual = l_primera(lista_ciudades);

    while (actual != l_ultima(lista_ciudades)) {
        TEntrada entrada = (TEntrada) malloc(sizeof(TEntrada));

        entrada->clave = l_recuperar(lista_ciudades, actual);
        entrada->valor = entrada->clave;

        cp_insertar(colaCP, entrada);
    }

    int contador = 1;

    while(cp_size(colaCP) != 0) {
        TCiudad ciudad_recuperada = cp_eliminar(colaCP)->clave;

        printf("%i. %s", contador, ciudad_recuperada->nombre);
    }

    cp_destruir(colaCP);
}