#include "colacp.h"

TNodo ultimo_nodo_padre(TColaCP cola) {
    TNodo nodo_actual, nodo_ultimo = ELE_NULO;
    TLista lista_nodos = crear_lista();
    boolean encontre = FALSE;

    l_insertar(&lista_nodos, l_primera(lista_nodos), cola->raiz);

    // Lo hago hasta que se termine la lista o que lo encuentre al ultimo nodo
    while(l_size(lista_nodos) != 0 || !encontre) {
        nodo_actual = l_recuperar(lista_nodos, l_primera(lista_nodos));
        l_eliminar(&lista_nodos, l_primera(lista_nodos));

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
                TPosicion ultima = l_ultima(lista_nodos);

                if (ultima == POS_NULA) {
                    l_insertar(&lista_nodos, POS_NULA, nodo_actual->hijo_izquierdo);
                    l_insertar(&lista_nodos, l_ultima(lista_nodos)->celda_siguiente, nodo_actual->hijo_derecho);
                } else {
                    l_insertar(&lista_nodos, l_ultima(lista_nodos)->celda_siguiente, nodo_actual->hijo_izquierdo);
                    l_insertar(&lista_nodos, l_ultima(lista_nodos)->celda_siguiente, nodo_actual->hijo_derecho);
                }
            }
        }
    }

    l_destruir(&lista_nodos);

    return nodo_ultimo;
}

void burbujear_arriba(TNodo raiz, TNodo nodo) {
    TNodo nodo_actual = nodo;
    while(nodo_actual != raiz) {
        if (funcion_prioridad(nodo_actual->entrada, nodo_actual->padre->entrada) == 1) {
            TEntrada entrada_aux;

            entrada_aux = nodo_actual->padre->entrada;
            nodo_actual->padre->entrada = nodo_actual->entrada;
            nodo_actual->entrada = entrada_aux;
        }

        nodo_actual = nodo_actual->padre;
    }
}

void burbujear_abajo(TColaCP cola) {
    boolean seguir = TRUE;
    TNodo nodo_actual = cola->raiz, nodo_minimo = NULL;
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

/**
* Metodos
**/

TColaCP crear_cola_CP(int (*f)(TEntrada, TEntrada)) {
    funcion_prioridad = f;

    TColaCP colaCP = (TColaCP) malloc(sizeof(struct cola_con_prioridad));

    colaCP->raiz = ELE_NULO;
    colaCP->cantidad_elementos = 0;

    return colaCP;
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

        burbujear_arriba(cola->raiz, nuevo_nodo);
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
    } else {
        if (nodo_ultimo_padre->hijo_izquierdo == ELE_NULO) {
            TNodo padre = nodo_ultimo_padre->padre;

            if (padre == ELE_NULO) {
                free(nodo_ultimo_padre);
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
    }

    burbujear_abajo(cola);

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

    while(cp_size(cola) != 0) {
        TEntrada entrada_eliminada = cp_eliminar(cola);
        free(entrada_eliminada->clave);
        free(entrada_eliminada->valor);
        free(entrada_eliminada);
    }

    return TRUE;
}