#include "lista.h"

/**
 * Destruye la posicion recursivamente desde el final al comienzo
 * @param posicion Posicion por donde empezar
 */
void destruir_celda_recursivo(TPosicion posicion);

void crear_lista(TLista *lista) {
    (*lista) = ELE_NULO;
}

int l_insertar(TLista *lista, TPosicion pos, TElemento elem){
    if(lista==NULL)
        exit(LST_NO_INI);

    int exito;

    if(pos==POS_NULA){
        TPosicion posicion_aux=(TPosicion)malloc(sizeof(struct celda));
        posicion_aux->elemento=elem;

        if((*lista)==NULL){
            posicion_aux->celda_siguiente=POS_NULA;
            posicion_aux->celda_anterior=POS_NULA;

            *lista=posicion_aux;
        } else {
            posicion_aux->celda_siguiente=(*lista);
            posicion_aux->celda_anterior=POS_NULA;

            (*lista)->celda_anterior=posicion_aux;

            *lista=posicion_aux;
        }

        if(l_primera(*lista)->elemento==elem)
            exito=TRUE;
        else
            exito=FALSE;
    }else{
        TPosicion posicion_aux=(TPosicion)malloc(sizeof(struct celda));

        posicion_aux->elemento=elem;
        posicion_aux->celda_anterior=pos->celda_anterior;
        posicion_aux->celda_siguiente=pos;

        pos->celda_anterior->celda_siguiente=posicion_aux;
        pos->celda_anterior=posicion_aux;

        if(l_recuperar(*lista,pos)==elem)
            exito=TRUE;
        else
            exito=FALSE;
    }

    return exito;
}

int l_eliminar(TLista * lista, TPosicion pos){
    if(lista==NULL)
        exit(LST_NO_INI);

    int exito;

    if(pos==POS_NULA)
        exito=FALSE;
    else{
        if((pos->celda_anterior)==POS_NULA){
            if((pos->celda_siguiente)==POS_NULA){
                free(pos);
                (*lista)=NULL;
            } else {
                pos->celda_siguiente->celda_anterior=POS_NULA;
                (*lista)=pos->celda_siguiente;
                free(pos);
            }
        } else{
            if((pos->celda_siguiente)==POS_NULA){
                pos->celda_anterior->celda_siguiente=POS_NULA;
                free(pos);
            } else{
                pos->celda_anterior->celda_siguiente=pos->celda_siguiente;
                pos->celda_siguiente->celda_anterior=pos->celda_anterior;
                free(pos);
            }
        }

        exito=TRUE;
    }

    return exito;
}

TPosicion l_primera(TLista lista){
    if(lista==NULL)
        return POS_NULA;
    else
        return lista;
}

TPosicion l_ultima(TLista lista){
    if(lista==NULL)
        return POS_NULA;
    else{
        TPosicion posicion=lista;
        while((posicion->celda_siguiente)!=POS_NULA){
            posicion=posicion->celda_siguiente;
        }

        return posicion;
    }
}

TPosicion l_anterior(TLista lista, TPosicion pos){
    if(pos==lista)
        return POS_NULA;
    else
        return pos->celda_anterior;
}

TPosicion l_siguiente(TLista lista, TPosicion pos){
    if(pos==l_ultima(lista))
        return POS_NULA;
    else
        return pos->celda_siguiente;
}

TElemento l_recuperar(TLista lista, TPosicion pos){
    if(pos==POS_NULA)
        return ELE_NULO;
    else
        return pos->elemento;
}

int l_size(TLista lista){
    int size=0;

    if(lista==NULL)
        return size;
    else{
        TPosicion posicion=lista;
        while(posicion!=POS_NULA){
            size++;
            posicion=posicion->celda_siguiente;
        }

        return size;
    }
}

int l_destruir(TLista * lista){
    if(lista==NULL)
        exit(LST_NO_INI);

    destruir_celda_recursivo(*lista);
    lista = POS_NULA;

    return TRUE;
}

void destruir_celda_recursivo(TPosicion posicion) {
    if (posicion != POS_NULA) {
        if (posicion->celda_siguiente != POS_NULA) {
            destruir_celda_recursivo(posicion->celda_siguiente);
        }

        posicion->celda_siguiente = POS_NULA;
        posicion->celda_anterior = POS_NULA;
        free(posicion);
    }
}
