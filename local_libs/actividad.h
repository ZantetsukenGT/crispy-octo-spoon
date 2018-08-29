#ifndef ACTIVIDAD_H_INCLUDED
#define ACTIVIDAD_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct fecha //Fecha
{
    int dd;
    int mm;
    int yyyy;

} Fecha;

typedef struct hora
{
    int hh;
    int mm;

} Hora;

typedef struct actividad
{
    char * id_actividad;
    char * descripcion_actividad;
    Fecha * fecha_actividad;
    Hora * hora_inicio;
    Hora * hora_final;

} Actividad;


Fecha * CrearFecha(int dd, int mm, int yyyy);

Hora * CrearHora(int hh, int mm);

Actividad * CrearActividad(char* id, char* descripcion, Hora* inicio, Hora* fin, Fecha* fecha);

Hora * SetHora();

Fecha * SetFecha();

int Transformar_Hora_Entero(Hora* hora);

int Transformar_Fecha_Entero(Fecha* fecha);

Hora * Copiar_Hora(Hora * viejo);

Fecha * Copiar_Fecha(Fecha * viejo);

void Liberar_Actividad(Actividad** borrar);

#endif // ACTIVIDAD_H_INCLUDED
