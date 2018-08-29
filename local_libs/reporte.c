#include "reporte.h"

void GenerarReporte1(Fecha * dia_actual, NodoPrincipal * primero)//genera boxes de una lista doble enlazada
{
    char *text_reporte = strdup("");
    char *tmp1 = strdup("");
    NodoPrincipal * actual = Buscar_Principal(dia_actual,primero);

    if(actual != NULL)
    {
        text_reporte = ConcatenarCharChar(text_reporte,"digraph G{ rankdir = LR; ");

        NodoSecundario * pivote = actual->siguiente;

        while(pivote != NULL)//ciclo que da formato a todo nodo
        {
            tmp1 = ConcatenarCharChar("Nodo",pivote->actividad->id_actividad);
            tmp1 = ConcatenarCharNumero(tmp1,Obtener_Fecha_Secundario(pivote));
            tmp1 = ConcatenarCharChar(tmp1,"[label = \"");
            tmp1 = ConcatenarCharChar(tmp1,pivote->actividad->id_actividad);
            tmp1 = ConcatenarCharChar(tmp1,"\n");
            tmp1 = ConcatenarCharNumero(tmp1,pivote->actividad->fecha_actividad->dd);
            tmp1 = ConcatenarCharChar(tmp1,"/");
            tmp1 = ConcatenarCharNumero(tmp1,pivote->actividad->fecha_actividad->mm);
            tmp1 = ConcatenarCharChar(tmp1,"/");
            tmp1 = ConcatenarCharNumero(tmp1,pivote->actividad->fecha_actividad->yyyy);
            tmp1 = ConcatenarCharChar(tmp1,"\n");
            tmp1 = ConcatenarCharNumero(tmp1,pivote->actividad->hora_inicio->hh);
            tmp1 = ConcatenarCharChar(tmp1,":");
            tmp1 = ConcatenarCharNumero(tmp1,pivote->actividad->hora_inicio->mm);
            tmp1 = ConcatenarCharChar(tmp1," - ");
            tmp1 = ConcatenarCharNumero(tmp1,pivote->actividad->hora_final->hh);
            tmp1 = ConcatenarCharChar(tmp1,":");
            tmp1 = ConcatenarCharNumero(tmp1,pivote->actividad->hora_final->mm);
            tmp1 = ConcatenarCharChar(tmp1,"\", shape = box]; ");
            text_reporte = ConcatenarCharChar(text_reporte,tmp1);
            pivote = pivote->siguiente;
        }

        pivote = actual->siguiente;

        while(pivote != NULL)//ciclo que linkea de inicio a final
        {
            if(pivote->siguiente!= NULL)
            {
                tmp1 = ConcatenarCharChar("Nodo",pivote->actividad->id_actividad);
                tmp1 = ConcatenarCharNumero(tmp1,Obtener_Fecha_Secundario(pivote));
                tmp1 = ConcatenarCharChar(tmp1,"-> ");
                text_reporte = ConcatenarCharChar(text_reporte,tmp1);
            }
            else
            {
                tmp1 = ConcatenarCharChar("Nodo",pivote->actividad->id_actividad);
                tmp1 = ConcatenarCharNumero(tmp1,Obtener_Fecha_Secundario(pivote));
                tmp1 = ConcatenarCharChar(tmp1,"; ");
                text_reporte = ConcatenarCharChar(text_reporte,tmp1);
            }
            pivote = pivote->siguiente;
        }

        pivote = actual->siguiente;

        while(pivote->siguiente != NULL)//coloca pivote como el ultimo de lista
        {
            pivote = pivote->siguiente;
        }

        while(pivote != NULL)//ciclo que linkea de final a inicio
        {
            if(pivote->anterior!= NULL)
            {
                tmp1 = ConcatenarCharChar("Nodo",pivote->actividad->id_actividad);
                tmp1 = ConcatenarCharNumero(tmp1,Obtener_Fecha_Secundario(pivote));
                tmp1 = ConcatenarCharChar(tmp1,"-> ");
                text_reporte = ConcatenarCharChar(text_reporte,tmp1);
            }
            else
            {
                tmp1 = ConcatenarCharChar("Nodo",pivote->actividad->id_actividad);
                tmp1 = ConcatenarCharNumero(tmp1,Obtener_Fecha_Secundario(pivote));
                tmp1 = ConcatenarCharChar(tmp1,"; ");
                text_reporte = ConcatenarCharChar(text_reporte,tmp1);
            }
            pivote = pivote->anterior;
        }

        text_reporte = ConcatenarCharChar(text_reporte, "} ");

        FILE *f1 = fopen("Reporte1.dot", "w");

        fprintf(f1, "%s", text_reporte);
        fclose(f1);

        system("dot -Tpng \"Reporte1.dot\" -o \"Reporte1.png\"");
        printf("Se genero con exito el reporte 1\n\n");
        system("eog Reporte1.png");
        return;
    }
    printf("Reporte 1 imposible de generar debido a que no existe esa fecha\n\n");

}

void GenerarReporte2(NodoPrincipal * principal)
{
    char *text_reporte = strdup("");
    char *tmp1 = strdup("");
    NodoPrincipal * actual = principal;

    if(actual != NULL)
    {
        text_reporte = ConcatenarCharChar(text_reporte,"digraph G{ rankdir = TB; ");
        text_reporte = ConcatenarCharChar(text_reporte,"subgraph principales { ");
        do//ciclo que da formato al reporte
        {
            tmp1 = ConcatenarCharNumero("Nodo",Obtener_Fecha_Principal(actual));
            tmp1 = ConcatenarCharChar(tmp1,"[label = \"Dia\n");
            tmp1 = ConcatenarCharNumero(tmp1,actual->fecha->dd);
            tmp1 = ConcatenarCharChar(tmp1,"/");
            tmp1 = ConcatenarCharNumero(tmp1,actual->fecha->mm);
            tmp1 = ConcatenarCharChar(tmp1,"/");
            tmp1 = ConcatenarCharNumero(tmp1,actual->fecha->yyyy);
            tmp1 = ConcatenarCharChar(tmp1,"\", shape = box]; ");
            text_reporte = ConcatenarCharChar(text_reporte,tmp1);

            actual = actual->abajo;
        }
        while(actual != principal);

        actual = principal;

        do//ciclo que linkea de inicio a final
        {
            if(actual->abajo!= principal)
            {
                tmp1 = ConcatenarCharNumero("Nodo",Obtener_Fecha_Principal(actual));
                tmp1 = ConcatenarCharChar(tmp1,"->");
                text_reporte = ConcatenarCharChar(text_reporte,tmp1);
            }
            else
            {
                tmp1 = ConcatenarCharNumero("Nodo",Obtener_Fecha_Principal(actual));
                tmp1 = ConcatenarCharChar(tmp1,"; ");
                text_reporte = ConcatenarCharChar(text_reporte,tmp1);
            }
            actual = actual->abajo;
        }
        while(actual != principal);

        actual = principal->arriba;//coloca actual como el ultimo de lista

        do//ciclo que linkea de final a inicio
        {
            if(actual->arriba!= principal->arriba)
            {
                tmp1 = ConcatenarCharNumero("Nodo",Obtener_Fecha_Principal(actual));
                tmp1 = ConcatenarCharChar(tmp1,"->");
                text_reporte = ConcatenarCharChar(text_reporte,tmp1);
            }
            else
            {
                tmp1 = ConcatenarCharNumero("Nodo",Obtener_Fecha_Principal(actual));
                tmp1 = ConcatenarCharChar(tmp1,"; ");
                text_reporte = ConcatenarCharChar(text_reporte,tmp1);
            }
            actual = actual->arriba;
        }
        while(actual != principal->arriba);

        actual = principal;

        //linkea primero con ultimo y viceversa
        tmp1 = ConcatenarCharNumero("Nodo",Obtener_Fecha_Principal(actual));
        tmp1 = ConcatenarCharChar(tmp1,"->");
        tmp1 = ConcatenarCharChar(tmp1,"Nodo");
        tmp1 = ConcatenarCharNumero(tmp1,Obtener_Fecha_Principal(actual->arriba));
        tmp1 = ConcatenarCharChar(tmp1,"; Nodo");
        tmp1 = ConcatenarCharNumero(tmp1,Obtener_Fecha_Principal(actual->arriba));
        tmp1 = ConcatenarCharChar(tmp1,"->");
        tmp1 = ConcatenarCharChar(tmp1,"Nodo");
        tmp1 = ConcatenarCharNumero(tmp1,Obtener_Fecha_Principal(actual));
        tmp1 = ConcatenarCharChar(tmp1,"; } ");

        text_reporte = ConcatenarCharChar(text_reporte,tmp1);

        int i = 1;
        actual = principal;
        NodoSecundario * pivote = NULL;


        //escribir subgrafos restantes (copiado de reporte 1)
        do
        {
            pivote = actual->siguiente;
            while(pivote != NULL)
            {
                text_reporte = ConcatenarCharChar(text_reporte,"subgraph dia");
                text_reporte = ConcatenarCharNumero(text_reporte,i++);
                text_reporte = ConcatenarCharChar(text_reporte," { rank = \"same\"; ");
                while(pivote != NULL)//ciclo que da formato a todo nodo
                {
                    tmp1 = ConcatenarCharChar("Nodo",pivote->actividad->id_actividad);
                    tmp1 = ConcatenarCharNumero(tmp1,Obtener_Fecha_Secundario(pivote));
                    tmp1 = ConcatenarCharChar(tmp1,"[label = \"");
                    tmp1 = ConcatenarCharChar(tmp1,pivote->actividad->id_actividad);
                    tmp1 = ConcatenarCharChar(tmp1,"\n");
                    tmp1 = ConcatenarCharNumero(tmp1,pivote->actividad->fecha_actividad->dd);
                    tmp1 = ConcatenarCharChar(tmp1,"/");
                    tmp1 = ConcatenarCharNumero(tmp1,pivote->actividad->fecha_actividad->mm);
                    tmp1 = ConcatenarCharChar(tmp1,"/");
                    tmp1 = ConcatenarCharNumero(tmp1,pivote->actividad->fecha_actividad->yyyy);
                    tmp1 = ConcatenarCharChar(tmp1,"\n");
                    tmp1 = ConcatenarCharNumero(tmp1,pivote->actividad->hora_inicio->hh);
                    tmp1 = ConcatenarCharChar(tmp1,":");
                    tmp1 = ConcatenarCharNumero(tmp1,pivote->actividad->hora_inicio->mm);
                    tmp1 = ConcatenarCharChar(tmp1," - ");
                    tmp1 = ConcatenarCharNumero(tmp1,pivote->actividad->hora_final->hh);
                    tmp1 = ConcatenarCharChar(tmp1,":");
                    tmp1 = ConcatenarCharNumero(tmp1,pivote->actividad->hora_final->mm);
                    tmp1 = ConcatenarCharChar(tmp1,"\", shape = box]; ");
                    text_reporte = ConcatenarCharChar(text_reporte,tmp1);
                    pivote = pivote->siguiente;
                }

                pivote = actual->siguiente;

                tmp1 = ConcatenarCharNumero("Nodo",Obtener_Fecha_Principal(actual));
                tmp1 = ConcatenarCharChar(tmp1,"->");

                text_reporte = ConcatenarCharChar(text_reporte,tmp1);

                while(pivote != NULL)//ciclo que linkea de inicio a final
                {
                    if(pivote->siguiente != NULL)
                    {
                        tmp1 = ConcatenarCharChar("Nodo",pivote->actividad->id_actividad);
                        tmp1 = ConcatenarCharNumero(tmp1,Obtener_Fecha_Secundario(pivote));
                        tmp1 = ConcatenarCharChar(tmp1,"-> ");
                        text_reporte = ConcatenarCharChar(text_reporte,tmp1);
                    }
                    else
                    {
                        tmp1 = ConcatenarCharChar("Nodo",pivote->actividad->id_actividad);
                        tmp1 = ConcatenarCharNumero(tmp1,Obtener_Fecha_Secundario(pivote));
                        tmp1 = ConcatenarCharChar(tmp1,"; ");
                        text_reporte = ConcatenarCharChar(text_reporte,tmp1);
                    }
                    pivote = pivote->siguiente;
                }

                pivote = actual->siguiente;

                while(pivote->siguiente != NULL)//coloca pivote como el ultimo de lista
                {
                    pivote = pivote->siguiente;
                }

                while(pivote != NULL)//ciclo que linkea de final a inicio
                {
                    if(pivote->anterior!= NULL)
                    {
                        tmp1 = ConcatenarCharChar("Nodo",pivote->actividad->id_actividad);
                        tmp1 = ConcatenarCharNumero(tmp1,Obtener_Fecha_Secundario(pivote));
                        tmp1 = ConcatenarCharChar(tmp1,"-> ");
                        text_reporte = ConcatenarCharChar(text_reporte,tmp1);
                    }
                    else
                    {
                        tmp1 = ConcatenarCharChar("Nodo",pivote->actividad->id_actividad);
                        tmp1 = ConcatenarCharNumero(tmp1,Obtener_Fecha_Secundario(pivote));
                        tmp1 = ConcatenarCharChar(tmp1,"; ");
                        text_reporte = ConcatenarCharChar(text_reporte,tmp1);
                    }
                    pivote = pivote->anterior;
                }

                text_reporte = ConcatenarCharChar(text_reporte, "} ");
            }
            actual = actual->abajo;
        }
        while(actual != principal);

        text_reporte = ConcatenarCharChar(text_reporte, "}");

        FILE *f1 = fopen("Reporte2.dot", "w");

        fprintf(f1, "%s", text_reporte);
        fclose(f1);

        system("dot -Tpng \"Reporte2.dot\" -o \"Reporte2.png\"");
        printf("Se genero con exito el reporte 2\n\n");
        system("eog Reporte2.png");
        return;
    }
    printf("Reporte 2 imposible de generar debido a que el calendario esta vacio\n\n");

}
