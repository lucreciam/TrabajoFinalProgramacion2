#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
typedef struct stFecha
{
    int dia;
    int mes;
    int anio;
}stFecha;

stFecha cargarFecha();
stFecha obtenerFechaActual();
int verificarFechaFutura(stFecha fechaIngresada);
int esBisiesto(int anio);
int verificarFecha(stFecha fecha, stFecha fechaActual);
stFecha ingresarFecha();
void escribirFecha(FILE *arch, stFecha fecha);
#endif // FECHA_H_INCLUDED
