#include "esenciales.h"

void GenerarSeed()
{
    srand(time(NULL));
}

int Contar_Digitos(int n)
{
    if(n >= 10)
    {
        return 1 + Contar_Digitos(n/10);
    }
    return 1;
}

int randomizer(int Min, int Max)
{
    return Min + rand()%(Max-Min+1);
}

char * ConcatenarCharNumero(char *a, int n)
{
    int size = Contar_Digitos(n);
    char b[size];
    sprintf(b,"%d",n);

    return ConcatenarCharChar(a,b);
}

char * ConcatenarCharChar(char *a, char *b)
{
    char * c = (char*) malloc(strlen(a) + strlen(b) + 1);
    strcpy(c,a);
    strcat(c,b);

    return c;
}

char * ConcatenarNumeroNumero(int a, int n)
{
    int size = Contar_Digitos(n);
    char b[size];
    sprintf(b,"%d",n);

    return ConcatenarCharNumero(b,a);
}

char * CopiarCadena(char *a)
{
    char * b = (char*)malloc(sizeof(strlen(a)+1));
    strcpy(b,a);
    return b;
}

