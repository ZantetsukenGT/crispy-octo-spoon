#include "actividad.h"

Fecha * CrearFecha(int dd, int mm, int yyyy)
{
    Fecha * nuevo = (Fecha*) malloc(sizeof(Fecha));
    nuevo->dd = dd;
    nuevo->mm = mm;
    nuevo->yyyy = yyyy;
    return nuevo;
}

Hora * CrearHora(int hh, int mm)
{
    Hora * nuevo = (Hora*) malloc(sizeof(Hora));
    nuevo->hh = hh;
    nuevo->mm = mm;
    return nuevo;
}

Actividad * CrearActividad(char* id, char* descripcion, Hora* inicio, Hora* fin, Fecha* fecha)
{
    Actividad * nuevo = (Actividad*) malloc(sizeof(Actividad));
    nuevo->id_actividad = id;
    nuevo->descripcion_actividad = descripcion;
    nuevo->hora_inicio = inicio;
    nuevo->hora_final = fin;
    nuevo->fecha_actividad = fecha;
    return nuevo;
}

Hora * SetHora()
{
    int mm;
    int hh;

    printf("Ingrese la hora: ");
    scanf("%d", &hh);

    printf("Ingrese los minutos: ");
    scanf("%d", &mm);

    printf("\n");
    return CrearHora(hh,mm);
}

Fecha * SetFecha()
{
    int yyyy;
    int mm;
    int dd;

    printf("Ingrese el año: ");
    scanf("%d", &yyyy);

    printf("Ingrese el mes: ");
    scanf("%d", &mm);

    printf("Ingrese el dia: ");
    scanf("%d", &dd);
    printf("\n");
    return CrearFecha(dd,mm,yyyy);
}


int Transformar_Fecha_Entero(Fecha* fecha)
{
    return fecha->dd + 31*fecha->mm + 372*fecha->yyyy;
}

int Transformar_Hora_Entero(Hora* hora)
{
    return hora->mm + 60*hora->hh;
}

Hora * Copiar_Hora(Hora * viejo)
{
    Hora * nuevo = CrearHora(viejo->hh,viejo->mm);
    return nuevo;
}

Fecha * Copiar_Fecha(Fecha * viejo)
{
    Fecha * nuevo = CrearFecha(viejo->dd,viejo->mm,viejo->yyyy);
    return nuevo;
}

void Liberar_Actividad(Actividad ** borrar)
{
    free((*borrar)->fecha_actividad);
    free((*borrar)->hora_final);
    free((*borrar)->hora_inicio);
    free(*borrar);
}
