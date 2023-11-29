#ifndef LISTAPRACTICAS_H_INCLUDED
#define LISTAPRACTICAS_H_INCLUDED

#include "arbolPacientes.h"
#include "arbolPacientes.h"
#include "login.h"
#include "menus.h"
#include "listaIngresos.h"
#include "fecha.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define ARCHIVOPACIENTES "pacientes.dat"
#define ARCHIVOSOLOPRACTICAS "practicas.dat"
#define ARCHIVOINGRESOS "ingresos.dat"
#define ARCHIVOPRACTICASXINGRESOS "practicasxingresos.dat"
#define archivoCuentas "archivoCuentas.dat"



#define ESC 27
extern int IDGLOBAL;

typedef struct stPracxIngreso
{
    int nroIngreso;
    int NroPractica;
    char Resultado[40];
    int eliminado;

}stPracxIngreso;

typedef struct nodoPracticas
{
    stPracxIngreso practica;
    struct nodoPracticas *siguiente;

}nodoPracticas;

///FUNCIONES DE LISTA
nodoPracticas * inicListaPractica(); // Inicializa la lista
nodoPracticas * crearNodoPractica(stPracxIngreso dato); // Funcion que crea un nuevo nodo Practicas
nodoPracticas * buscaUltimoNodoPractica(nodoPracticas * listaPracticas);// Busca ultimo nodo
nodoPracticas * agregoFinalListaPractica(nodoPracticas* listaPracticas,stPracxIngreso nuevo); // Agrego el final de la lista
void muestraListaPracticas(nodoPracticas* listaPracticas,stPractica arregloPracticas[]); // Muestra lista
nodoPracticas * cargaListaPracticas(nodoPracticas * listaPractica, int idIngreso); // Lee el archivo y carga la lista
nodoPracticas * buscarPracticaxIngreso(nodoPracticas * listaPracticas, int idPractica);
nodoPracticas * bajaLista(nodoPracticas * listaPracticas);




///FUNCIONES DE ESTRUCTURA
void muestraUnaPracticaIngreso(stPracxIngreso practica,stPractica arregloPracticas[]);// Muestra una practica Ingreso
nodoPracticas * cargaPracticas(int idIngreso,nodoPracticas * listaPracticas,stPractica practicas[],int validos); //Carga de practicas hasta que quiera el usuario

///FUNCIONES DE ARCHIVO
//void cargarArchivoIngresosPracticas(nodoPracticas * listaPracticas); //Carga el archivo con los datos de la lista recibida por paremetro
void cargarArchivoIngresosPracticas(nodoPracticas * listaPracticas, FILE * archivoPracticas);
nodoPracticas * cargarResultados(nodoPracticas * listaPracticas,stPractica arregloPracticas[]);
///FUNCIONES EXTRA


#endif // LISTAPRACTICAS_H_INCLUDED
