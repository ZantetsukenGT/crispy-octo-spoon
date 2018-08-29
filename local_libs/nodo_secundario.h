#ifndef NODO_SECUNDARIO_H_INCLUDED
#define NODO_SECUNDARIO_H_INCLUDED

#include <stdlib.h>
#include "actividad.h"

typedef struct nodosecundario//NodoSecundario
{
    struct nodosecundario *anterior;
    struct nodosecundario *siguiente;
    Actividad * actividad;

}NodoSecundario;

NodoSecundario * Crear_Nodo_Secundario(Actividad * data);

int Obtener_Fecha_Secundario(NodoSecundario * nuevo);

int Obtener_Hora_Inicio(NodoSecundario * nuevo);

int Obtener_Hora_Final(NodoSecundario * nuevo);

void InsertarAlFrente_Doble_Secundario(NodoSecundario *nuevo, NodoSecundario **primero);
void InsertarAlFinal_Doble_Secundario(NodoSecundario *nuevo, NodoSecundario **primero);

NodoSecundario * RemoverDelFrente_Doble_Secundario(NodoSecundario **primero);
NodoSecundario * RemoverDelFinal_Doble_Secundario(NodoSecundario **primero);

NodoSecundario * Buscar_Secundario(char * id_actividad, NodoSecundario *primero);
NodoSecundario * Remover_Por_Busqueda_Secundario(char * id_actividad, NodoSecundario **primero);

void ImprimirInfo_Secundario(NodoSecundario * nuevo);

void Liberar_NodoSecundario(NodoSecundario** borrar);

#endif // NODO_SECUNDARIO_H_INCLUDED
