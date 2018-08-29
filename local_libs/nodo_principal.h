#ifndef NODO_PRINCIPAL_H_INCLUDED
#define NODO_PRINCIPAL_H_INCLUDED

#include <stdlib.h>
#include "actividad.h"
#include "nodo_secundario.h"

typedef struct nodoprincipal//Nodo
{
    struct nodoprincipal *arriba;
    struct nodoprincipal *abajo;
    Fecha * fecha;
    NodoSecundario* siguiente;

}NodoPrincipal;

NodoPrincipal * Crear_Nodo_Principal(Fecha * fecha);

int Obtener_Fecha_Principal(NodoPrincipal * nuevo);

void InsertarAlFrente_CDoble_Principal(NodoPrincipal *nuevo, NodoPrincipal **primero);
void InsertarAlFinal_CDoble_Principal(NodoPrincipal *nuevo, NodoPrincipal **primero);

NodoPrincipal * RemoverDelFrente_CDoble_Principal(NodoPrincipal **primero);
NodoPrincipal * RemoverDelFinal_CDoble_Principal(NodoPrincipal **primero);

NodoPrincipal * Buscar_Principal(Fecha * fecha, NodoPrincipal *primero);
NodoPrincipal * Remover_Por_Busqueda_Principal(Fecha * fecha, NodoPrincipal **primero);

void ImprimirInfo_Principal(NodoPrincipal * nuevo);

void Liberar_NodoPrincipal(NodoPrincipal** borrar);
#endif // NODO_PRINCIPAL_H_INCLUDED
