#include "nodo_principal.h"

NodoPrincipal * Crear_Nodo_Principal(Fecha * fecha)
{
    NodoPrincipal * nuevo = (NodoPrincipal*) malloc(sizeof(NodoPrincipal));

    nuevo->arriba = NULL;
    nuevo->abajo = NULL;
    nuevo->fecha = fecha;
    nuevo->siguiente = NULL;
    return nuevo;
}

int Obtener_Fecha_Principal(NodoPrincipal * nuevo)
{
    return Transformar_Fecha_Entero(nuevo->fecha);
}


void InsertarAlFrente_CDoble_Principal(NodoPrincipal *nuevo, NodoPrincipal **primero)
{
    if(*primero == NULL)
    {
        *primero = nuevo;

        (*primero)->arriba = *primero;
        (*primero)->abajo = *primero;
    }
    else
    {
        nuevo->abajo = *primero;
        nuevo->arriba = (*primero)->arriba;

        (*primero)->arriba->abajo = nuevo;
        (*primero)->arriba = nuevo;
        *primero = nuevo;
    }
}


void InsertarAlFinal_CDoble_Principal(NodoPrincipal *nuevo, NodoPrincipal **primero)
{
    if(*primero == NULL)
    {
        *primero = nuevo;

        (*primero)->arriba = *primero;
        (*primero)->abajo = *primero;
    }
    else
    {
        NodoPrincipal * pivote = *primero;

        while(pivote->abajo != *primero)
        {
            pivote = pivote->abajo;
        }
        nuevo->abajo = *primero;
        nuevo->arriba = pivote;

        (*primero)->arriba = nuevo;
        pivote->abajo = nuevo;
    }
}

NodoPrincipal * RemoverDelFrente_CDoble_Principal(NodoPrincipal **primero)
{
    NodoPrincipal * pivote = NULL;
    if(*primero != NULL)
    {
        if((*primero)->abajo == *primero)
        {
            pivote = *primero;
            *primero = NULL;
        }
        else
        {
            pivote = *primero;

            (*primero)->abajo->arriba = (*primero)->arriba;
            (*primero)->arriba->abajo = (*primero)->abajo;

            *primero = (*primero)->abajo;
        }
    }
    return pivote;
}

NodoPrincipal * RemoverDelFinal_CDoble_Principal(NodoPrincipal **primero)
{
    NodoPrincipal * pivote = NULL;
    if(*primero != NULL)
    {
        if((*primero)->abajo == *primero)
        {
            pivote = *primero;
            *primero = NULL;
        }
        else
        {
            pivote = *primero;

            while(pivote->abajo != *primero)
            {
                pivote = pivote->abajo;
            }

            pivote->arriba->abajo = *primero;
            (*primero)->arriba = pivote->arriba;
        }
    }
    return pivote;
}

NodoPrincipal * Buscar_Principal(Fecha *fecha, NodoPrincipal *primero)
{
    int buscado = Transformar_Fecha_Entero(fecha);
    if(primero != NULL)
    {
        NodoPrincipal * pivote = primero;
        do
        {
            int actual = Obtener_Fecha_Principal(pivote);
            if(actual == buscado)
            {
                return pivote;
            }
            pivote = pivote->abajo;
        }
        while(pivote != primero);
    }
    return NULL;
}

NodoPrincipal * Remover_Por_Busqueda_Principal(Fecha * fecha, NodoPrincipal **primero)
{
    NodoPrincipal * pivote = Buscar_Principal(fecha,*primero);
    if(pivote != NULL)
    {
        if(pivote == *primero)
        {
            return RemoverDelFrente_CDoble_Principal(primero);
        }
        pivote->arriba->abajo = pivote->abajo;
        pivote->abajo->arriba = pivote->arriba;
    }
    return pivote;
}

void ImprimirInfo_Principal(NodoPrincipal * nuevo)
{
    printf("Row -> %d\n\n",Obtener_Fecha_Principal(nuevo));
}

void Liberar_NodoPrincipal(NodoPrincipal** borrar)
{
    if(*borrar != NULL)
    {
        Liberar_NodoPrincipal(&(*borrar)->abajo);
        Liberar_NodoSecundario(&(*borrar)->siguiente);
        free((*borrar)->fecha);
        free(*borrar);
    }
}
