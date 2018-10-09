#include "planificador.h"
TCiudad ciudad_actual;

/**
 * Devuelve la distancia entre las 2 ciudades
 * @param ciudad1 Ciudad 1
 * @param ciudad2 Ciudad 2
 * @return Distancia de Manhattan de las 2 ciudades
 */
int distancia(TCiudad ciudad1, TCiudad ciudad2);

/**
 * Define la prioridad para la cola de forma descendente
 * @param entrada1 Entrada 1
 * @param entrada2 Entrada 2
 * @return 1 si la entrada 1 tiene mayor prioridad que la 2, 0 si tienen igual prioridad
 *      -1 si tiene menor prioridad
 */
int prioridad_descendente(TEntrada entrada1, TEntrada entrada2);

/**
 * Define la prioridad para la cola de forma ascendente
 * @param entrada1 Entrada 1
 * @param entrada2 Entrada 2
 * @return 1 si la entrada 1 tiene mayor prioridad que la 2, 0 si tienen igual prioridad
 *      -1 si tiene menor prioridad
 */
int prioridad_ascendente(TEntrada entrada1, TEntrada entrada2);

/**
 * Lee el nombre hasta el ; de un archivo y lo guarda en el campo nombre de la ciudad
 * @param ciudad Ciudad en donde guardar el nombre
 * @param archivo Archivo de donde leer el nombre
 */
void leer_nombre(TCiudad ciudad, FILE *archivo);

/**
 * Crea una nueva lista sacando la ciudad de los elementos
 * @param lista Lista de donde copiar
 * @param ciudad_a_sacar Ciudad a sacar
 */
TLista copiar_lista(TLista lista, TCiudad ciudad_a_sacar);

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
            ultima = (ultima == POS_NULA) ? POS_NULA : ultima->celda_siguiente;

            l_insertar(lista_ciudades, ultima, ciudad_leida);
        }
    }

    fclose(archivo_ciudades);
}

void mostrar_ascendente(TLista lista_ciudades){
    TColaCP cola;
    crear_cola_CP(&cola, &prioridad_ascendente);

    TPosicion pos=l_primera(lista_ciudades);

    int *dist;

    while(pos!=POS_NULA){
        TCiudad actual=pos->elemento;

        TEntrada entr=(TEntrada)malloc(sizeof(struct entrada));

        dist = (int *) malloc(sizeof(int));
        *dist=distancia(actual,ciudad_actual);

        entr->clave=dist;
        entr->valor=actual;

        cp_insertar(cola,entr);

        pos=l_siguiente(lista_ciudades,pos);
    }

    int contador = 1;

    while(cp_size(cola)!=0) {
        TEntrada elemento_ciudad = cp_eliminar(cola);

        TCiudad ciudad_recuperada = elemento_ciudad->valor;

        char *nombre = ciudad_recuperada->nombre;
        printf("%i. %s\n",contador,nombre);

        contador++;

        free(elemento_ciudad->clave);
        free(elemento_ciudad);
    }

    cp_destruir(cola);
}

void mostrar_descendente(TLista lista_ciudades) {
    TColaCP colaCP;
    crear_cola_CP(&colaCP, &prioridad_descendente);

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

        free(elemento_ciudad->clave);
        free(elemento_ciudad);
    }

    cp_destruir(colaCP);
}

void reducir_horas_manejo(TLista lista_ciudades) {
    TColaCP colaCP;
    TPosicion cursor_lista_aux;
    TLista lista_aux = copiar_lista(lista_ciudades, ELE_NULO), lista_aux_vieja;
    TCiudad posicion_actual = ciudad_actual, ciudad_cercana;
    TEntrada entrada, entrada_ciudad_cercana;
    int *clave;
    int total_recorrido = 0;

    for(int i = 0; i < l_size(lista_ciudades); i++) {
        cursor_lista_aux = l_primera(lista_aux);

        crear_cola_CP(&colaCP, &prioridad_ascendente);
        while(cursor_lista_aux != POS_NULA) {
            entrada = (TEntrada) malloc(sizeof(struct entrada));
            clave = (int *) malloc(sizeof(int));

            *clave = distancia(cursor_lista_aux->elemento, posicion_actual);

            entrada->clave = clave;
            entrada->valor = cursor_lista_aux->elemento;

            cp_insertar(colaCP, entrada);

            cursor_lista_aux = l_siguiente(lista_aux, cursor_lista_aux);
        }

        entrada_ciudad_cercana = cp_eliminar(colaCP);

        ciudad_cercana = entrada_ciudad_cercana->valor;

        printf("%i. %s\n", i + 1, ciudad_cercana->nombre);

        total_recorrido += *((int *) entrada_ciudad_cercana->clave);

        posicion_actual = ciudad_cercana;

        free(entrada_ciudad_cercana->clave);
        free(entrada_ciudad_cercana);

        cp_destruir(colaCP);

        lista_aux_vieja = lista_aux;
        lista_aux = copiar_lista(lista_aux_vieja, ciudad_cercana);

        l_destruir(&lista_aux_vieja);
    }

    printf("Total recorrido: %i", total_recorrido);

    l_destruir(&lista_aux);
}

void destruir_lista_ciudad(TLista* lista) {
    if (l_size(*lista) != 0) {
        TPosicion cursor = l_primera(*lista);

        while(cursor != ELE_NULO) {
            TCiudad ciudad = l_recuperar(*lista, cursor);

            free(ciudad->nombre);
            free(ciudad);

            cursor = cursor->celda_siguiente;
        }
    }

    l_destruir(lista);

    free(ciudad_actual);
}

int distancia(TCiudad ciudad1, TCiudad ciudad2) {
    return abs(ciudad2->pos_x - ciudad1->pos_x) + abs(ciudad2->pos_y - ciudad1->pos_y);
}

int prioridad_descendente(TEntrada entrada1, TEntrada entrada2) {
    int clave1 = *((int *) entrada1->clave);
    int clave2 = *((int *) entrada2->clave);

    if (clave1 > clave2) {
        return 1;
    } else if (clave1 < clave2) {
        return -1;
    } else {
        return 0;
    }
}

int prioridad_ascendente(TEntrada entrada1, TEntrada entrada2){
    int clave1 = *((int *) entrada1->clave);
    int clave2 = *((int *) entrada2->clave);
    if (clave1 < clave2) {
        return 1;
    } else if (clave1 > clave2) {
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

TLista copiar_lista(TLista lista, TCiudad ciudad_a_sacar) {
    TPosicion cursor = l_primera(lista), cursor_lista_nueva = POS_NULA, siguiente;
    TLista *lista_nueva = (TLista *) malloc(sizeof(TLista *));
    crear_lista(lista_nueva);

    while (cursor != POS_NULA) {
        if (cursor->elemento != ciudad_a_sacar) {
            siguiente = (cursor_lista_nueva == POS_NULA) ? POS_NULA : l_siguiente(*lista_nueva, cursor_lista_nueva);

            l_insertar(lista_nueva, siguiente, cursor->elemento);

            cursor_lista_nueva = l_ultima(*lista_nueva);
        }

        cursor = l_siguiente(*lista_nueva, cursor);
    }

    return *lista_nueva;
}