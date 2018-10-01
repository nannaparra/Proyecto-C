#include "planificador.h"
TCiudad ciudad_actual;

int distancia(TCiudad ciudad1, TCiudad ciudad2) {
    return abs(ciudad2->pos_x - ciudad1->pos_x) + abs(ciudad2->pos_y - ciudad1->pos_y);
}

int prioridad_descendente(TEntrada entrada1, TEntrada entrada2) {
    int *clave1 = entrada1->clave;
    int *clave2 = entrada2->clave;

    if (*clave1 > *clave2) {
        return 1;
    } else if (*clave1 < *clave2) {
        return -1;
    } else {
        return 0;
    }
}

int prioridad_ascendente(TEntrada entrada1, TEntrada entrada2){
    if((entrada1->valor)<(entrada2->valor))
       return 1;
    else{
        if((entrada1->valor)>(entrada2->valor))
           return -1;
        else
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
            ciudad_actual = (TCiudad) malloc(sizeof(struct ciudad));

            fscanf(archivo_ciudades, "%f;%f\n", &ciudad_actual->pos_x, &ciudad_actual->pos_y);

            primera_linea = FALSE;
        } else {
            ciudad_leida = (TCiudad) malloc(sizeof(struct ciudad));

            leer_nombre(ciudad_leida, archivo_ciudades);

            fscanf(archivo_ciudades, "%f;%f\n", &ciudad_leida->pos_x, &ciudad_leida->pos_y);

            TPosicion ultima = l_ultima(*lista_ciudades);
            ultima = (ultima == POS_NULA) ? NULL : ultima->celda_siguiente;

            l_insertar(lista_ciudades, ultima, ciudad_leida);
        }
    }

    fclose(archivo_ciudades);
}

void mostrar_ascendente(TLista lista_ciudades){
    TColaCP cola = crear_cola_CP(&prioridad_ascendente);
    TPosicion pos=l_primera(lista_ciudades);
    while(pos!=POS_NULA){
        TCiudad actual=pos->elemento;
        TEntrada entr=(TEntrada) malloc(sizeof(struct entrada));
        entr->clave=actual->nombre;
        int dist=distancia(ciudad_actual,actual);
        entr->valor=&dist;
        cp_insertar(cola,entr);
        pos=l_siguiente(lista_ciudades,pos);
    }
    int contador = 1;
    while(cp_size(cola)!=0) {
        TClave nombre=cp_eliminar(cola)->clave;
        printf("%i. %p",contador,nombre);
    }
    cp_destruir(cola);
}

void mostrar_descendente(TLista lista_ciudades) {
    TColaCP colaCP = crear_cola_CP(&prioridad_descendente);
    TPosicion actual = l_primera(lista_ciudades);
    TEntrada entrada = NULL;
    int *distancia_ciudad;
    TCiudad ciudad_lista;

    while (actual != POS_NULA) {
        entrada = (TEntrada) malloc(sizeof(struct entrada));
        distancia_ciudad = (int *) malloc(sizeof(int));

        ciudad_lista = l_recuperar(lista_ciudades, actual);
        *distancia_ciudad = distancia(ciudad_lista, ciudad_actual);

        entrada->clave = distancia_ciudad;
        entrada->valor = ciudad_lista;

        cp_insertar(colaCP, entrada);

        actual = l_siguiente(lista_ciudades, actual);
    }

    int contador = 1;

    while(cp_size(colaCP) != 0) {
        TEntrada elemento_ciudad = cp_eliminar(colaCP);
        TCiudad ciudad_recuperada = elemento_ciudad->valor;

        char *nombre = ciudad_recuperada->nombre;
        printf("%i. %s\n", contador, nombre);

        contador++;
    }

    cp_destruir(colaCP);
}
