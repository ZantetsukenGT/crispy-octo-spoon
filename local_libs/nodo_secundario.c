#include "nodo_secundario.h"

NodoSecundario * Crear_Nodo_Secundario(Actividad * actividad)
{
    NodoSecundario * nuevo = (NodoSecundario*) malloc(sizeof(NodoSecundario));
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;
    nuevo->actividad = actividad;
    return nuevo;
}

int Obtener_Fecha_Secundario(NodoSecundario * nuevo){
    return Transformar_Fecha_Entero(nuevo->actividad->fecha_actividad);
}


int Obtener_Hora_Inicio(NodoSecundario * nuevo){
    return Transformar_Hora_Entero(nuevo->actividad->hora_inicio);
}

int Obtener_Hora_Final(NodoSecundario * nuevo){
    return Transformar_Hora_Entero(nuevo->actividad->hora_final);
}

void InsertarAlFrente_Doble_Secundario(NodoSecundario *nuevo, NodoSecundario **primero)
{
    if(*primero == NULL)
    {
        *primero = nuevo;
    }
    else
    {
        nuevo->siguiente = *primero;
        (*primero)->anterior = nuevo;
        *primero = nuevo;
    }
}


void InsertarAlFinal_Doble_Secundario(NodoSecundario *nuevo, NodoSecundario **primero)
{
    if(*primero == NULL)
    {
        *primero = nuevo;
    }
    else
    {
        NodoSecundario * pivote = *primero;

        while(pivote->siguiente != NULL)
        {
            pivote = pivote->siguiente;
        }

        pivote->siguiente = nuevo;
        nuevo->anterior = pivote;
    }
}

NodoSecundario * RemoverDelFrente_Doble_Secundario(NodoSecundario **primero)
{
    NodoSecundario * pivote = NULL;
    if(*primero != NULL)
    {
        if((*primero)->siguiente == NULL)
        {
            pivote = *primero;
            *primero = NULL;
        }
        else
        {
            pivote = *primero;
            *primero = (*primero)->siguiente;
            (*primero)->anterior = NULL;
        }
    }
    return pivote;
}

NodoSecundario * RemoverDelFinal_Doble_Secundario(NodoSecundario **primero)
{
    NodoSecundario * pivote = NULL;
    if(*primero != NULL)
    {
        if((*primero)->siguiente == NULL)
        {
            pivote = *primero;
            *primero = NULL;
        }
        else
        {
            pivote = *primero;

            while(pivote->siguiente != NULL)
            {
                pivote = pivote->siguiente;
            }
            pivote->anterior->siguiente = NULL;
        }
    }
    return pivote;
}

NodoSecundario * Buscar_Secundario(char * id_actividad, NodoSecundario *primero)
{
    NodoSecundario * pivote = primero;

    while(pivote != NULL)
    {
        char * actual = pivote->actividad->id_actividad;
        if(strcmp(id_actividad,actual) == 0)
        {
            return pivote;
        }
        pivote = pivote->siguiente;
    }
    return NULL;
}

NodoSecundario * Remover_Por_Busqueda_Secundario(char * id_actividad, NodoSecundario **primero)
{
    NodoSecundario * pivote = Buscar_Secundario(id_actividad,*primero);
    if(pivote != NULL)
    {
        if(pivote == *primero)
        {
            return RemoverDelFrente_Doble_Secundario(primero);
        }
        if(pivote->siguiente == NULL)
        {
            return RemoverDelFinal_Doble_Secundario(primero);
        }
        pivote->anterior->siguiente = pivote->siguiente;
        pivote->siguiente->anterior = pivote->anterior;
        return pivote;
    }
    return NULL;
}

void ImprimirInfo_Secundario(NodoSecundario * nuevo)
{
    Actividad * tmp = nuevo->actividad;
    printf("id_actividad -> %s\n",tmp->id_actividad);
    printf("descripcion -> %s\n",tmp->descripcion_actividad);
    printf("Fecha -> %d\n", Obtener_Fecha_Secundario(nuevo));
    printf("Hora inicio -> %d\n",Obtener_Hora_Inicio(nuevo));
    printf("Hora final -> %d\n\n",Obtener_Hora_Final(nuevo));
}

void Liberar_NodoSecundario(NodoSecundario** borrar)
{
    if(*borrar != NULL)
    {
        Liberar_NodoSecundario(&(*borrar)->siguiente);
        Liberar_Actividad(&(*borrar)->actividad);

        free(*borrar);
    }
}
