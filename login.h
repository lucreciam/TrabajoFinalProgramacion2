#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>

#define archivoCuentas "archivoCuentas.dat"

#define ESC 27
#define DIM 30


#define ARCHIVOPACIENTES "pacientes.dat"
#define ARCHIVOSOLOPRACTICAS "practicas.dat"
#define ARCHIVOINGRESOS "ingresos.dat"
#define ARCHIVOPRACTICASXINGRESOS "practicasxingresos.dat"
#define archivoCuentas "archivoCuentas.dat"


#include "time.h"
#include "arbolPacientes.h"
#include "listaPracticas.h"
#include "arbolPacientes.h"
#include "menus.h"
#include "listaIngresos.h"
#include "fecha.h"

typedef struct
{
    int dni;
    char apellidoYNombre[40];
    char usuario[20];
    char contrasenia[20];
    char perfil[20];
    int eliminado;
} Empleado;

Empleado buscarCuenta(int dni);
void muestraUnEmpleado(Empleado muestraEmpleado);
void muestraUnEmpleadoAdmin(Empleado muestraEmpleado);
void muestraEmpleadosAdmin(Empleado arregloEmpleados[],int validos);
void muestraEmpleados(Empleado arregloEmpleados[],int validos);
void ordenarPorSeleccion(Empleado arreglo[], int n);
int contarEmpleadosEnArchivo();
void listarEmpleados(int esAdmin);
void altaEmpleado();
void bajaEmpleado();
void modificarEmpleado(int esAdmin);
void ocultarPassword(char password[DIM]);
int login();


#endif // LOGIN_H_INCLUDED
