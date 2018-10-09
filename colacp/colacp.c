#include "colacp.h"

/**
 * Metodos Privados
 */

/**
 * Devuelve el primer nodo que tenga hijos nulos haciendo recorrido por niveles
 * @param cola Cola de donde sacar el el hijo con hijos nulos
 * @return Primer nodo que tenga por lo menos un hijo nulo
 */
TNodo ultimo_nodo_padre(TColaCP cola);

/**
 * Burbujea a partir del nodo para arriba
 * @param nodo Nodo por donde empezar a burbujear
 */
void burbujear_arriba(TNodo nodo);

/**
 * Burbujea a partir de la raiz para abajo
 * @param raiz Raiz de la cola para burbujear
 */
void burbujear_abajo(TNodo raiz);

/**
 * Destruye el arbol dada su raiz de manera recursiva
 * @param raiz Raiz del arbol para empezar a destruir
 */
void destruir_arbol(TNodo raiz);

void crear_cola_CP(TColaCP *cola, int (*f)(TEntrada, TEntrada)) {
    funcion_prioridad = f;

    *cola = (TColaCP) malloc(sizeof(struct cola_con_prioridad));

    (*cola)->raiz = ELE_NULO;
    (*cola)->cantidad_elementos = 0;
}

int cp_insertar(TColaCP cola, TEntrada entr) {
    if (cola == NULL) {
        exit(CCP_NO_INI);
    }

    TNodo nuevo_nodo = (TNodo) malloc(sizeof(struct nodo));

    if (cola->raiz == ELE_NULO) {
        nuevo_nodo->entrada = entr;
        nuevo_nodo->padre = ELE_NULO;
        nuevo_nodo->hijo_izquierdo = ELE_NULO;
        nuevo_nodo->hijo_derecho = ELE_NULO;

        cola->raiz = nuevo_nodo;
    } else {
        TNodo padre_ultimo_nodo = ultimo_nodo_padre(cola);

        nuevo_nodo->entrada = entr;
        nuevo_nodo->padre = padre_ultimo_nodo;
        nuevo_nodo->hijo_izquierdo = ELE_NULO;
        nuevo_nodo->hijo_derecho = ELE_NULO;

        if (padre_ultimo_nodo->hijo_izquierdo == ELE_NULO) {
            padre_ultimo_nodo->hijo_izquierdo = nuevo_nodo;
        } else {
            padre_ultimo_nodo->hijo_derecho = nuevo_nodo;
        }

        burbujear_arriba(nuevo_nodo);
    }

    cola->cantidad_elementos++;

    return TRUE;
}

TEntrada cp_eliminar(TColaCP cola) {
    if (cola == NULL) {
        exit(CCP_NO_INI);
    }

    TEntrada entrada_a_devolver = cola->raiz->entrada;
    TNodo nodo_ultimo_padre = ultimo_nodo_padre(cola);

    if (nodo_ultimo_padre->hijo_derecho != ELE_NULO) {
        cola->raiz->entrada = nodo_ultimo_padre->hijo_derecho->entrada;

        free(nodo_ultimo_padre->hijo_derecho);

        nodo_ultimo_padre->hijo_derecho = ELE_NULO;
    } else if (nodo_ultimo_padre->hijo_izquierdo == ELE_NULO) {
        TNodo padre = nodo_ultimo_padre->padre;

        if (padre == ELE_NULO) {
            free(nodo_ultimo_padre);
            cola->raiz = ELE_NULO;
        } else {
            cola->raiz->entrada = padre->hijo_derecho->entrada;

            free(nodo_ultimo_padre->padre->hijo_derecho);

            nodo_ultimo_padre->padre->hijo_derecho = ELE_NULO;
        }
    } else {
        cola->raiz->entrada = nodo_ultimo_padre->hijo_izquierdo->entrada;

        free(nodo_ultimo_padre->hijo_izquierdo);

        nodo_ultimo_padre->hijo_izquierdo = ELE_NULO;
    }

    if (cola->raiz != ELE_NULO) {
        burbujear_abajo(cola->raiz);
    }

    cola->cantidad_elementos--;

    return entrada_a_devolver;
}

int cp_size(TColaCP cola) {
    if (cola == NULL) {
        exit(CCP_NO_INI);
    }

    return cola->cantidad_elementos;
}

int cp_destruir(TColaCP cola) {
    if (cola == NULL) {
        exit(CCP_NO_INI);
    }

    destruir_arbol(cola->raiz);

    free(cola);

    return TRUE;
}

TNodo ultimo_nodo_padre(TColaCP cola) {
    TNodo nodo_actual, nodo_ultimo = ELE_NULO;
    TLista* lista_nodos = (TLista *) malloc(sizeof(TLista *));
    crear_lista(lista_nodos);
    boolean encontre = FALSE;

    l_insertar(lista_nodos, l_primera(*lista_nodos), cola->raiz);

    // Lo hago hasta que se termine la lista o que lo encuentre al ultimo nodo
    while(l_size(*lista_nodos) != 0 || !encontre) {
        nodo_actual = l_recuperar(*lista_nodos, l_primera(*lista_nodos));
        l_eliminar(lista_nodos, l_primera(*lista_nodos));

        if (nodo_actual != ELE_NULO) {
            // Si tiene hijos nulos encontro el padre
            if (nodo_actual->hijo_izquierdo == ELE_NULO) {
                nodo_ultimo = nodo_actual;
                encontre = TRUE;
            } else if (nodo_actual->hijo_derecho == ELE_NULO){
                nodo_ultimo = nodo_actual;
                encontre = TRUE;
            } else {
                // Agrega los hijos a la lista
                TPosicion ultima = l_ultima(*lista_nodos);

                if (ultima == POS_NULA) {
                    l_insertar(lista_nodos, POS_NULA, nodo_actual->hijo_izquierdo);
                    l_insertar(lista_nodos, l_ultima(*lista_nodos)->celda_siguiente, nodo_actual->hijo_derecho);
                } else {
                    l_insertar(lista_nodos, l_ultima(*lista_nodos)->celda_siguiente, nodo_actual->hijo_izquierdo);
                    l_insertar(lista_nodos, l_ultima(*lista_nodos)->celda_siguiente, nodo_actual->hijo_derecho);
                }
            }
        }
    }

    l_destruir(lista_nodos);

    return nodo_ultimo;
}

void burbujear_arriba(TNodo nodo) {
    TNodo nodo_actual = nodo;
    while(nodo_actual->padre != ELE_NULO) {
        if (funcion_prioridad(nodo_actual->entrada, nodo_actual->padre->entrada) == 1) {
            TEntrada entrada_aux;

            entrada_aux = nodo_actual->padre->entrada;
            nodo_actual->padre->entrada = nodo_actual->entrada;
            nodo_actual->entrada = entrada_aux;
        }

        nodo_actual = nodo_actual->padre;
    }
}

void burbujear_abajo(TNodo raiz) {
    boolean seguir = TRUE;
    TNodo nodo_actual = raiz, nodo_minimo = NULL;
    TEntrada aux_entrada = NULL;

    while(seguir) {
        if (nodo_actual->hijo_izquierdo == ELE_NULO) {
            seguir = FALSE;
        } else {
            // Minimo de los hijos
            if (nodo_actual->hijo_derecho != ELE_NULO) {
                if (funcion_prioridad(nodo_actual->hijo_izquierdo->entrada, nodo_actual->hijo_derecho->entrada) == 1) {
                    nodo_minimo = nodo_actual->hijo_izquierdo;
                } else {
                    nodo_minimo = nodo_actual->hijo_derecho;
                }
            } else {
                nodo_minimo = nodo_actual->hijo_izquierdo;
            }

            if (funcion_prioridad(nodo_actual->entrada, nodo_minimo->entrada) == -1) {
                aux_entrada = nodo_actual->entrada;

                nodo_actual->entrada = nodo_minimo->entrada;
                nodo_minimo->entrada = aux_entrada;
            } else {
                seguir = FALSE;
            }
        }
    }
}

void destruir_arbol(TNodo raiz) {
    if (raiz != ELE_NULO) {
        if (raiz->hijo_izquierdo != ELE_NULO) {
            destruir_arbol(raiz->hijo_izquierdo);
        }
        if (raiz->hijo_derecho != ELE_NULO) {
            destruir_arbol(raiz->hijo_derecho);
        }

        free(raiz->entrada);
        free(raiz);
    }
}