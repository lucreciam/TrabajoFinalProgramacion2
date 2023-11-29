#ifndef ARBOLPACIENTES_H_INCLUDED
#define ARBOLPACIENTES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

#define ARCHIVOPACIENTES "pacientes.dat"
#define ARCHIVOSOLOPRACTICAS "practicas.dat"
#define ARCHIVOINGRESOS "ingresos.dat"
#define ARCHIVOPRACTICASXINGRESOS "practicasxingresos.dat"
#define archivoCuentas "archivoCuentas.dat"



#include "listaPracticas.h"
#include "arbolPacientes.h"
#include "login.h"
#include "menus.h"
#include "listaIngresos.h"
#include "fecha.h"
#include "practicas.h"

///ESTRUCTURAS

typedef struct  stPaciente
{
    char ApellidoyNombre[40];
    int Edad;
    int DNI;
    char Domicilio[30];
    char Telefono[15];
    int Eliminado;

}stPaciente;

typedef struct  nodoPaciente
{
    stPaciente paciente;
    nodoIngresos * listaIngresos;
    struct nodoPaciente *Izq;
    struct nodoPaciente*Der;

}nodoPaciente;

///FUNCIONES ARBOL
nodoPaciente * inicArbol(); //anda
nodoPaciente * creaNodoPaciente(stPaciente dato); //anda
nodoPaciente * agregaPaciente(nodoPaciente* arbol, stPaciente dato); //anda
void muestraArbol(nodoPaciente * arbol); //anda
nodoPaciente * buscaPaciente(nodoPaciente * arbol,int dni); //anda
nodoPaciente * modificacionPaciente(nodoPaciente* arbol, int dni);
nodoPaciente * altaPaciente (nodoPaciente * arbol); //anda
void mostrarPacientesOrdenadosAlfabeticamente(nodoPaciente* arbol); //anda
int contarNodos(nodoPaciente* arbol); //anda
void recorridoInorden(nodoPaciente* arbol, stPaciente* arreglo, int* indice); //anda
void busquedaMenuPacientes(nodoPaciente* arbol);


nodoPaciente* cargarArbolDesdeArchivo(nodoPaciente* arbol,stPaciente paciente);

nodoPaciente* getNodoPaciente(nodoPaciente* arbol,int dni);

///FUNCIONES ESTRUCTURA
stPaciente cargaPaciente(int dni); //anda
void muestraPaciente(stPaciente dato); //anda
stPaciente modificarAYP(stPaciente dato); //anda
stPaciente modificarEdad(stPaciente dato); //anda
stPaciente modificarDomicilio(stPaciente dato); //anda
stPaciente modificarTelefono(stPaciente dato); //anda
stPaciente modificarAltaBaja(stPaciente dato); //anda
int compararPacientes(const void* a, const void* b);//anda

///FUNCIONES DE ARCHIVO
void cargarArchivoPacientes(nodoPaciente * arbolPacientes); //anda
//void recorreArbolEscritura(nodoPaciente *arbolPacientes, FILE *arch); //anda
nodoPaciente * cargaArbolPacientes(nodoPaciente*  arbolPacientes); //anda

void recorreArbolEscritura(nodoPaciente *arbolPacientes, FILE *archivoPacientes, FILE * archivoIngresos, FILE * archivoPracticas);
void escribirArchivos(nodoPaciente * arbol);

///FUNCIONES DE VERIFICACION
int obtenerDNI(); //anda

///FUNCIONES DE MENUSH

nodoPaciente * inicSistema(stPractica arregloPracticas[], int * validos, nodoPaciente * arbolPacientes);
nodoPaciente * menuAdmin(nodoPaciente * arbolGeneral, stPractica practicas[],int * validos);
nodoPaciente * menuPacientesAdmin(nodoPaciente * arbolGeneral,stPractica practicas[],int validos);
nodoPaciente * menuPracticasAdmin(nodoPaciente * arbolGeneral,stPractica practicas[],int * validos);
nodoPaciente * menuIngresosAdmin(nodoPaciente* arbolGeneral, stPractica practicas[], int* validos);
nodoPaciente * menuAdministrativo(nodoPaciente * arbolGeneral, stPractica practicas[],int *validos);
nodoPaciente * menuTecyBio(nodoPaciente * arbolPacientes, stPractica arregloPracticas[], int * validos);

///FUNCIONES DE INGRESOS
nodoPaciente * modificarIngreso(nodoPaciente* arbol);
void mostrarIngresoPaciente(nodoPaciente* arbolGeneral);
void muestraIngresoPorDni(nodoPaciente* arbolGeneral);
void filtraIngresosPaciente(nodoPaciente* arbol,stPractica arregloPracticas[]);
void filtraIngresosPorFecha(nodoPaciente*  arbol,stFecha fecha,stPractica practicas[]);
void muestraIngresoPorFecha(nodoPaciente *  arbolGeneral);
nodoIngresos*validacionFecha(stIngresos ingreso, nodoPaciente*buscado);
nodoIngresos* obtenerIngresoID(nodoPaciente* arbol, int id);

///FUNCIONES DE PRACTICAS
int buscaPractica(nodoPaciente *arbol, int nroPractica);
void bajaPractica(stPractica practicas[], int validos, nodoPaciente * arbol, int idPractica);



///FUNCIONES MENU
void finSistema(nodoPaciente * arbolPacientes, stPractica arregloPracticas[], int  validos);
void menuEmpleados(nodoPaciente* arbolGeneral,stPractica practicas[],int validos);
void menuPrincipal();

#endif // ARBOLPACIENTES_H_INCLUDED
