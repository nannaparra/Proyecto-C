#include "planificador.h"

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

void leer_archivo(char *path_archivo, TLista lista_ciudades) {
    FILE *archivo_ciudades = fopen(path_archivo, "r");
    boolean primera_linea = TRUE;
    TCiudad ciudad_leida;

    while(!feof(archivo_ciudades)) {
        ciudad_leida = (TCiudad) malloc(sizeof(TCiudad));

        if (primera_linea) {
            ciudad_leida->nombre = "Actual";

            primera_linea = FALSE;
        } else {
            leer_nombre(ciudad_leida, archivo_ciudades);
        }

        fscanf(archivo_ciudades, "%f;%f\n", &ciudad_leida->pos_x, &ciudad_leida->pos_y);

        l_insertar(&lista_ciudades, POS_NULA, ciudad_leida);
    }

    fclose(archivo_ciudades);
    free(archivo_ciudades);
}