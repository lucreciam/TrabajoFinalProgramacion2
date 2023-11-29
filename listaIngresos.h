#ifndef LISTAINGRESOS_H_INCLUDED
#define LISTAINGRESOS_H_INCLUDED
#include "listaPracticas.h"
#include "arbolPacientes.h"
#include "practicas.h"
#include "login.h"
#include "menus.h"
#include "fecha.h"

#define ARCHIVOPACIENTES "pacientes.dat"
#define ARCHIVOSOLOPRACTICAS "practicas.dat"
#define ARCHIVOINGRESOS "ingresos.dat"
#define ARCHIVOPRACTICASXINGRESOS "practicasxingresos.dat"
#define archivoCuentas "archivoCuentas.dat"




typedef struct stIngresos
{
    int nroIngreso;
    stFecha fechaIngreso; //por defecto la actual
    stFecha fechaRetiro;
    int dni;
    int matriculaProfesional;
    int eliminado;

}stIngresos;

typedef struct nodoIngresos
{
    stIngresos dato;
    struct nodoIngresos * siguiente;
    struct nodoPracticas * practicas;

}nodoIngresos;

///FUNCIONES DE LA LISTA

nodoIngresos * inicLista(); // Inicializa la lista
nodoIngresos * crearNodo(stIngresos dato); // Funcion que crea un nuevo nodo Ingreso
nodoIngresos* agregoFinalListaIngresos(nodoIngresos* listaIngresos, stIngresos nuevo);
void muestraListaIngresos(nodoIngresos* listaIngresos);
nodoIngresos* buscaUltimoNodoIngresos(nodoIngresos* listaIngresos);
nodoIngresos * buscaIngreso(nodoIngresos * listaIngresos, int idIngreso);
nodoIngresos* agregarFinalNodo(nodoIngresos* nuevoNodo,nodoIngresos* lista);
nodoIngresos * altaIngresos(nodoIngresos * lista,stPractica practicas[],int validos,int dni);
nodoIngresos * ingresoExistente (nodoIngresos * listaIngresos, stFecha fecha);
nodoIngresos * bajaIngreso(nodoIngresos* listaIngresos);


///FUNCIONES DE ESTRUCTURA

void muestraIngreso(stIngresos ingreso);
stIngresos cargaIngreso(int dni);

///FUNCIONES EXTRAS

///VALIDACIONES


///FUNCIONES ARCHIVO
nodoIngresos * cargarListaIngresosArchivo(nodoIngresos *ingresosPaciente,int dni);
//void cargaArchivoIngresos(nodoIngresos * listaIngresos);
int buscaIdIngresoMayor();




#endif // LISTAINGRESOS_H_INCLUDED
