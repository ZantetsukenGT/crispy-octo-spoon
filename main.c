#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "local_libs/esenciales.h"
#include "local_libs/nodo_secundario.h"
#include "local_libs/nodo_principal.h"
#include "local_libs/reporte.h"

bool EstaRepetido(NodoPrincipal * primero, char * id_actividad);

void InsertarActividad(NodoPrincipal ** primero, Fecha *fecha, Actividad * data);
NodoPrincipal * InsertarPrincipal(NodoPrincipal ** primero, Fecha *fecha);
void InsertarSecundario(NodoSecundario ** primero, Actividad * data);

void CrearNuevaActividad(NodoPrincipal ** primero);

void ConsultarActividad(NodoPrincipal ** primero);

void ModificarActividad(NodoSecundario * reemplazar, NodoPrincipal *row, NodoPrincipal ** primero);

void EliminarActividad(NodoSecundario * eliminar, NodoPrincipal *row, NodoPrincipal ** primero);

void imprimir(NodoPrincipal* p);

void vaciar(NodoPrincipal **p);

////////////////////////////////////////GLOBALES//////////////////////////////////////////
////////////////////////////////////////GLOBALES//////////////////////////////////////////
////////////////////////////////////////GLOBALES//////////////////////////////////////////

int modo_insercion;

////////////////////////////////////////METODOS//////////////////////////////////////////
////////////////////////////////////////METODOS//////////////////////////////////////////
////////////////////////////////////////METODOS//////////////////////////////////////////

bool EstaRepetido(NodoPrincipal * primero, char * id_actividad)
{
    NodoPrincipal * principal = primero;
    NodoSecundario * secundario = NULL;

    if(principal != NULL)
    {
        do
        {
            secundario = Buscar_Secundario(id_actividad,principal->siguiente);
            if(secundario != NULL)
            {
                return true;
            }
            principal = principal->abajo;
        }
        while(principal != primero);
    }
    return false;
}


void InsertarActividad(NodoPrincipal ** primero,Fecha *fecha, Actividad * actividad)
{
    NodoPrincipal * row = InsertarPrincipal(primero, fecha);
    InsertarSecundario(&(row->siguiente),actividad);
}

NodoPrincipal * InsertarPrincipal(NodoPrincipal ** primero, Fecha *fecha)
{
    NodoPrincipal * aux = Buscar_Principal(fecha,*primero);
    if(aux != NULL)
    {
        return aux;
    }

    NodoPrincipal * nuevo = Crear_Nodo_Principal(fecha);
    NodoPrincipal * pivote = NULL;

    switch(modo_insercion)
    {
    case 1:
        if(*primero != NULL)
        {
            if(Transformar_Fecha_Entero(fecha) < Obtener_Fecha_Principal(*primero))
            {
                InsertarAlFrente_CDoble_Principal(nuevo,primero);
                return nuevo;
            }

            pivote = *primero;
            do
            {
                if(Transformar_Fecha_Entero(fecha) < Obtener_Fecha_Principal(pivote))
                {
                    pivote->arriba->abajo = nuevo;
                    nuevo->arriba = pivote->arriba;

                    pivote->arriba = nuevo;
                    nuevo->abajo = pivote;
                    return nuevo;
                }
                pivote = pivote->abajo;
            }
            while(pivote != *primero);
            InsertarAlFinal_CDoble_Principal(nuevo,primero);
            return nuevo;
        }

        InsertarAlFrente_CDoble_Principal(nuevo,primero);
        return nuevo;
    case 2:
        InsertarAlFinal_CDoble_Principal(nuevo,primero);
        return nuevo;
    default:
        InsertarAlFrente_CDoble_Principal(nuevo,primero);
        return nuevo;
    }
}

void InsertarSecundario(NodoSecundario ** primero, Actividad* actividad)
{
    NodoSecundario * nuevo = Crear_Nodo_Secundario(actividad);
    NodoSecundario * pivote = NULL;

    switch(modo_insercion)
    {
    case 1:
        if(*primero != NULL)
        {
            if(Obtener_Hora_Inicio(nuevo) < Obtener_Hora_Inicio(*primero))
            {
                InsertarAlFrente_Doble_Secundario(nuevo,primero);
                return;
            }

            pivote = *primero;
            while(pivote != NULL)
            {
                if(Obtener_Hora_Inicio(pivote) == Obtener_Hora_Inicio(nuevo))
                {
                    return;
                }

                if(Obtener_Hora_Inicio(nuevo) < Obtener_Hora_Inicio(pivote))
                {
                    pivote->anterior->siguiente = nuevo;
                    nuevo->anterior = pivote->anterior;

                    pivote->anterior = nuevo;
                    nuevo->siguiente = pivote;
                    return;
                }
                pivote = pivote->siguiente;
            }
            InsertarAlFinal_Doble_Secundario(nuevo,primero);
            return;
        }

        InsertarAlFrente_Doble_Secundario(nuevo,primero);
        break;
    case 2:
        InsertarAlFinal_Doble_Secundario(nuevo,primero);
        break;
    case 3:
        InsertarAlFrente_Doble_Secundario(nuevo,primero);
        break;
    }
}

void CrearNuevaActividad(NodoPrincipal ** primero)
{
    int opcion = 0;
    if(*primero == NULL)
    {
        while(opcion != 1 && opcion != 2 && opcion != 3)
        {
            printf("Su agenda esta completamente vacia,\n");
            printf("elija la forma de almacenar los datos:\n\n");

            printf("\t1: Ordenadas por hora\n");
            printf("\t2: Comportamiento de cola\n");
            printf("\t3: Comportamiento de pila\n\n");
            printf("Su eleccion: ");
            scanf("%d", &opcion);
            printf("\n");
            switch(opcion)
            {
            case 1:
            case 2:
            case 3:
                break;
            default:
                printf("Opcion Invalida\n\n");
            }
        }
        modo_insercion = opcion;
    }
    opcion = 0;

    Actividad * nueva = NULL;

    char* titulo = strdup("default");
    char* descripcion = strdup("default");
    Fecha* fecha = CrearFecha(0,0,0);
    Hora* inicio = CrearHora(0,0);
    Hora* fin = CrearHora(23,59);

    while (opcion != 6 && opcion != 7)
    {
        int i = 0;

        printf("Elija una opcion para continuar\n\n");

        printf("\t1: Definir titulo de actividad\n");
        printf("\t2: Definir descripcion\n");
        printf("\t3: Definir fecha\n");
        printf("\t4: Definir hora de inicio\n");
        printf("\t5: Definir hora de fin\n\n");
        printf("\t6: Guardar\n");
        printf("\t7: Cancelar\n\n");
        printf("Su eleccion: ");
        scanf("%d", &opcion);
        printf("\n");
        switch(opcion)
        {
        case 1:
            printf("Titulo actividad: ");
            scanf("%s", titulo);
            printf("\n");
            break;
        case 2:
            printf("Descripcion actividad: ");
            scanf("%s", descripcion);
            printf("\n");
            break;
        case 3:
            fecha = SetFecha();
            break;
        case 4:
            inicio = SetHora();
            break;
        case 5:
            fin = SetHora();
            break;
        case 6:
            if(EstaRepetido(*primero,titulo))
            {
                char* pivote = CopiarCadena(titulo);
                while(EstaRepetido(*primero,pivote))
                {
                    i++;
                    pivote = CopiarCadena(titulo);
                    pivote = ConcatenarCharNumero(pivote,i);
                }
                titulo = CopiarCadena(pivote);
            }
            nueva = CrearActividad(titulo,descripcion,inicio,fin,fecha);
            InsertarActividad(primero,fecha,nueva);
            break;
        case 7:
            break;
        default:
            printf("Opcion Invalida\n\n");
        }
    }
}

void ConsultarActividad(NodoPrincipal ** primero)
{
    char * titulo = strdup("");
    printf("Escriba el titulo de la actividad por consultar\n\n");
    printf("Titulo: ");
    scanf("%s", titulo);
    printf("El titulo a buscar es: %s",titulo);
    printf("\n\n");

    NodoPrincipal * principal = *primero;
    NodoSecundario * secundario = NULL;

    if(principal != NULL)
    {
        do
        {
            secundario = Buscar_Secundario(titulo,principal->siguiente);
            if(secundario != NULL)
            {
                break;
            }
            principal = principal->abajo;
        }
        while(principal != *primero);
    }

    if(secundario != NULL)
    {
        char* titulo = CopiarCadena(secundario->actividad->id_actividad);
        char* descripcion = CopiarCadena(secundario->actividad->descripcion_actividad);
        Fecha* fecha = Copiar_Fecha(secundario->actividad->fecha_actividad);
        Hora* inicio = Copiar_Hora(secundario->actividad->hora_inicio);
        Hora* fin = Copiar_Hora(secundario->actividad->hora_final);

        int opcion = 0;
        while (opcion != 1 && opcion != 2 && opcion != 3)
        {
            printf("Identificador:\t%s\n",titulo);
            printf("Fecha:\t\t%d/%d/%d\n",fecha->dd,fecha->mm,fecha->yyyy);
            printf("Hora de inicio:\t%d:%d\n",inicio->hh,inicio->mm);
            printf("Hora de final:\t%d:%d\n",fin->hh,fin->mm);
            printf("Descripcion:\t%s\n\n",descripcion);

            printf("Elija una opcion para continuar\n\n");

            printf("\t1: Actualizar\n");
            printf("\t2: Eliminar\n");
            printf("\t3: Cancelar\n\n");
            printf("Su eleccion: ");
            scanf("%d", &opcion);
            printf("\n");
            switch(opcion)
            {
            case 1:
                ModificarActividad(secundario,principal,primero);
                break;
            case 2:
                EliminarActividad(secundario,principal,primero);
                break;
            case 3:
                break;
            default:
                printf("Opcion Invalida\n\n");
            }
        }
    }
    else
    {
        printf("Actividad no encontrada\n\n");
    }
}

void ModificarActividad(NodoSecundario * reemplazar, NodoPrincipal *row, NodoPrincipal ** primero)
{
    Actividad * pivote = NULL;

    char* titulo = CopiarCadena(reemplazar->actividad->id_actividad);
    char* descripcion = CopiarCadena(reemplazar->actividad->descripcion_actividad);

    Fecha* fecha = Copiar_Fecha(reemplazar->actividad->fecha_actividad);
    Hora* inicio = Copiar_Hora(reemplazar->actividad->hora_inicio);
    Hora* fin = Copiar_Hora(reemplazar->actividad->hora_final);

    int opcion = 0;
    while (opcion != 5 && opcion != 6 && opcion != 7)
    {
        printf("Identificador:\t%s\n",titulo);
        printf("Fecha:\t\t%d/%d/%d\n",fecha->dd,fecha->mm,fecha->yyyy);
        printf("Hora de inicio:\t%d:%d\n",inicio->hh,inicio->mm);
        printf("Hora de final:\t%d:%d\n",fin->hh,fin->mm);
        printf("Descripcion:\t%s\n\n",descripcion);

        printf("Elija una opcion para continuar\n\n");

        printf("\t1: Modificar descripcion\n");
        printf("\t2: Modificar fecha\n");
        printf("\t3: Modificar hora de inicio\n");
        printf("\t4: Modificar hora de fin\n\n");
        printf("\t5: Guardar\n");
        printf("\t6: Eliminar\n");
        printf("\t7: Cancelar\n\n");
        printf("Su eleccion: ");
        scanf("%d", &opcion);
        printf("\n");
        switch(opcion)
        {
        case 1:
            printf("Descripcion actividad: ");
            scanf("%s", descripcion);
            printf("\n");
            break;
        case 2:
            fecha = SetFecha();
            break;
        case 3:
            inicio = SetHora();
            break;
        case 4:
            fin = SetHora();
            break;
        case 5:
            EliminarActividad(reemplazar,row,primero);

            pivote = CrearActividad(titulo,descripcion,inicio,fin,fecha);

            InsertarActividad(primero,fecha,pivote);
            break;
        case 6:
            EliminarActividad(reemplazar,row,primero);
            break;
        case 7:
            break;
        default:
            printf("Opcion Invalida\n\n");
        }
    }
}

void EliminarActividad(NodoSecundario * eliminar, NodoPrincipal *row, NodoPrincipal ** primero)
{
    Remover_Por_Busqueda_Secundario(eliminar->actividad->id_actividad,&row->siguiente);

    NodoPrincipal * actual = Buscar_Principal(row->fecha,*primero);

    if(actual->siguiente == NULL)
    {
        Remover_Por_Busqueda_Principal(row->fecha,primero);
    }
}


////////////////////////////////////////INTERFAZ//////////////////////////////////////////
////////////////////////////////////////INTERFAZ//////////////////////////////////////////
////////////////////////////////////////INTERFAZ//////////////////////////////////////////


void GenerarInterfaz()
{
    NodoPrincipal * primero = NULL;
    Fecha * dia_actual = NULL;
    int opcion = 0;
    while (opcion != 7)
    {
        printf("¿Que desea hacer?\n\n");

        printf("\t1: Crear actividad\n");
        printf("\t2: Consultar una actividad\n");
        printf("\t3: Modificar una actividad\n");
        printf("\t4: Eliminar una actividad\n");
        printf("\t5: Listar actividades del dia actual\n");
        printf("\t6: Imprimir calendario por mes\n");
        printf("\t7: Salir\n\n");
        printf("\t8: TEST PRINT\n\n");
        printf("Su eleccion: ");
        scanf("%i", &opcion);
        printf("\n");
        switch(opcion)
        {
        case 1:
            CrearNuevaActividad(&primero);
            break;
        case 2:
            ConsultarActividad(&primero);
            break;
        case 3:
            ConsultarActividad(&primero);
            break;
        case 4:
            ConsultarActividad(&primero);
            break;
        case 5:
            printf("Ingrese la fecha actual:\n\n");
            dia_actual = SetFecha();
            GenerarReporte1(dia_actual,primero);
            break;
        case 6:
            GenerarReporte2(primero);
            break;
        case 7:
            break;
        case 8:
            imprimir(primero);
            break;
        default:
            printf("Opcion Invalida\n\n");
        }
    }
}

void vaciar(NodoPrincipal **p)
{
    if(*p != NULL)
    {
        (*p)->arriba->abajo = NULL;
        Liberar_NodoPrincipal(p);
    }
}

////////////////////////////////////////MAIN TESTING//////////////////////////////////////////
////////////////////////////////////////MAIN TESTING//////////////////////////////////////////
////////////////////////////////////////MAIN TESTING//////////////////////////////////////////

void imprimir(NodoPrincipal* p)
{
    NodoPrincipal* aux_p = p;

    if(aux_p != NULL)
    {
        do
        {
            NodoSecundario * aux_s = aux_p->siguiente;
            printf("+---+\n| %d |-> ", Obtener_Fecha_Principal(aux_p));
            while(aux_s != NULL)
            {
                if(aux_s->siguiente != NULL)
                {
                    printf("%s -> ", aux_s->actividad->id_actividad);
                }
                else
                {
                    printf("%s\n", aux_s->actividad->id_actividad);
                }
                aux_s = aux_s->siguiente;
            }
            printf("+---+\n");
            aux_p = aux_p->abajo;
        }
        while(aux_p != p);
    }
}

int main()
{
    modo_insercion = 0;
    GenerarInterfaz();
    return 0;
}

