#ifndef ESENCIALES_H_INCLUDED
#define ESENCIALES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void GenerarSeed();

int Contar_Digitos(int n);

int randomizer(int Min, int Max);

char * ConcatenarCharNumero(char *a, int n);

char * ConcatenarCharChar(char *a, char *b);

char * ConcatenarNumeroNumero(int a, int n);

char * CopiarCadena(char *a);

#endif // ESENCIALES_H_INCLUDED
