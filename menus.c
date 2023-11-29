#include <stdio.h>
#include <stdlib.h>
#include "arbolPacientes.h"
#include "listaPracticas.h"
#include "arbolPacientes.h"
#include "login.h"
#include "menus.h"
#include "listaIngresos.h"
#include "fecha.h"

#define ARCHIVOPACIENTES "pacientes.dat"
#define ARCHIVOPRACTICAS "practicas.dat"
#define ARCHIVOINGRESOS "ingresos.dat"
#define ARCHIVOPRACTICASXINGRESOS "practicasxingresos.dat"
#define archivoCuentas "archivoCuentas.dat"

#define ESC 27

int IDGLOBAL;

nodoPaciente * inicSistema(stPractica arregloPracticas[], int * validos, nodoPaciente * arbolPacientes)
{

    IDGLOBAL = buscaIdIngresoMayor();

    (*validos) = levantarArchivoArreglosPracticas(arregloPracticas);

    arbolPacientes = cargaArbolPacientes(arbolPacientes);

    return arbolPacientes;
}

void finSistema(nodoPaciente * arbolPacientes, stPractica arregloPracticas[], int  validos)
{

    guardarCambiosArregloPracticas(arregloPracticas,validos);

    escribirArchivos(arbolPacientes);

}

void menuPrincipal()
{

    IDGLOBAL = buscaIdIngresoMayor();



    int validos = 0;
    stPractica arregloPracticas[100];

    nodoPaciente * arbolPacientes = inicArbol();

    char opcion = 0;

    arbolPacientes = inicSistema(arregloPracticas,&validos,arbolPacientes);

    while(1)
    {
        opcion = 0;

        system("cls");

        while(opcion != ESC)
        {


            int log = login();

            system("cls");


            switch(log)
            {
            case 1:

                arbolPacientes = menuAdmin(arbolPacientes,arregloPracticas,&validos);
                opcion = ESC;
                break;

            case 2:

                arbolPacientes = menuAdministrativo(arbolPacientes,arregloPracticas,&validos);
                opcion = ESC;

                break;
            case 3:

                arbolPacientes = menuTecyBio(arbolPacientes,arregloPracticas,&validos);
                opcion = ESC;
                break;
            case 4:
                arbolPacientes = menuTecyBio(arbolPacientes,arregloPracticas,&validos);
                opcion = ESC;
                break;
            default:
                printf("Ingrese una opcion valida ! \n");
                break;
            }

            finSistema(arbolPacientes,arregloPracticas,validos);

        }
    }
}

nodoPaciente * menuAdmin(nodoPaciente * arbolGeneral, stPractica practicas[],int * validos)/*, archivoEmpleados, archivoPracticas*///TODO
{


    char opc = 0;

    while(opc != ESC)
    {

        system("cls");

        printf("\n---------------------------------------\n");
        printf("\n\nBIENVENIDO AL MENU ADMINISTRADOR\n\n\n");
        printf("1- PACIENTES\n"); // MODIFICACION, BAJA, ALTA, MUESTRA
        printf("2- PRACTICAS\n"); // MOFICICACION, BAJA, ALTA, MUESTRA
        printf("3- INGRESOS\n"); //MODIFICACION, BAJA, ALTA, MUESTRA
        printf("4- EMPLEADOS\n"); // MODIFICACION, BAJA, ALTA, MUESTRA
        printf("\n\nESC para salir y guardar cambios.");
        printf("\n---------------------------------------\n");

        fflush(stdin);
        opc = getch();

        switch(opc)
        {
        case '1':
            system("cls");

            arbolGeneral = menuPacientesAdmin(arbolGeneral,practicas,(*validos));

            break;

        case '2':
            system("cls");

            arbolGeneral = menuPracticasAdmin(arbolGeneral,practicas,validos);

            break;

        case '3':
            system("cls");

            arbolGeneral = menuIngresosAdmin(arbolGeneral,practicas,validos);

            break;

        case '4':
            system("cls");
            menuEmpleados(arbolGeneral,practicas,(*validos));

            break;
        default:

            printf("Seleccione una opcion Valida\n");
            break;
        }


    }

    return arbolGeneral;

}

nodoPaciente * menuPacientesAdmin(nodoPaciente * arbolGeneral,stPractica practicas[],int validos)
{


    char opc;

    int dni = 0;

    while(opc != ESC)
    {
        system("cls");

        printf("\n---------------------------------------\n");
        printf("\n\nMENU PACIENTES\n\n\n");
        printf("1 - Ver listado de pacientes \n");
        printf("2 - Buscar paciente \n");
        printf("3 - Alta del paciente  \n");
        printf("4 - Modificacion de un paciente \n");
        printf("\n\n\nESC para volver al menu anterior");
        printf("\n---------------------------------------\n");

        fflush(stdin);
        opc = getch();


        switch(opc)
        {
        case '1': //LISTADO DE PACIENTES
            system("cls");
            mostrarPacientesOrdenadosAlfabeticamente(arbolGeneral); //funcion que muestra en orden de nombre y apellido

            break;

        case '2': //BUSCAR PACIENTE
            system("cls");
            busquedaMenuPacientes(arbolGeneral);
            break;

        case '3': //DAR DE ALTA UN PACIENTE

            system("cls");
            arbolGeneral = altaPaciente(arbolGeneral);

            break;
        case '4':

            system("cls");
            dni = obtenerDNI();
            nodoPaciente * buscadoo = buscaPaciente(arbolGeneral,dni);

            if(buscadoo == NULL)
            {
                printf("El paciente no esta cargado \n");

            }
            else
            {

                arbolGeneral = modificacionPaciente(arbolGeneral,dni);
            }

            break;
        case ESC:

            finSistema(arbolGeneral,practicas,validos);
            system("cls");

        default:

            printf("Seleccione una opcion Valida\n");
            break;

        }
    }

    return arbolGeneral;
}

nodoPaciente * menuPracticasAdmin(nodoPaciente * arbolGeneral,stPractica practicas[],int * validos)
{


    int opc = 0;
    int dni = 0;

    while(opc != ESC)
    {
        system("cls");

        printf("\n---------------------------------------\n");
        printf("\n\nMENU DE PRACTICAS DE ADMINSITRADOR\n\n\n");
        printf("1 - Ver listado de Practicas \n");
        printf("2 - Buscar Practicas \n");
        printf("3 - Alta de Practicas \n");
        printf("4 - Baja de Practicas \n");
        printf("5 - Modificacion de Practicas \n");
        printf("\n\n\nESC para volver al menu anterior");
        printf("\n---------------------------------------\n");

        fflush(stdin);
        opc = getch();

        switch(opc)
        {
        case '1':

            mostrarPracticas(practicas,(*validos));
            break;

        case '2':

            muestraPracticasPorCaracter(practicas,(*validos));

            break;
        case '3':

            altaPractica(practicas,validos);
            break;

        case '4':
            system("cls");

            int id = verificarID(practicas,(*validos));

            if(id != -1)
            {
                bajaPractica(practicas, (*validos), arbolGeneral, id);
            }

            system("pause");

            break;
        case '5':

            modificacionPractica(practicas,(*validos));

            break;
        case ESC:

            guardarCambiosArregloPracticas(practicas,(*validos));

        default:

            printf("Seleccione una opcion Valida\n");

            break;
        }

        finSistema(arbolGeneral,practicas,(*validos));

    }

    return arbolGeneral;
}

nodoPaciente * menuIngresosAdmin(nodoPaciente* arbolGeneral, stPractica practicas[], int* validos)
{
    char opc;
    int dni = 0;

    while (opc != ESC)
    {
        system("cls");

        printf("\n---------------------------------------\n");
        printf("\n\nMENU INGRESOS ADMINISTRADOR\n\n\n");
        printf("1 - Ver listado de Ingresos\n");
        printf("2 - Buscar ingreso con practicas\n");
        printf("3 - Alta de Ingreso\n");
        printf("4 - Modificacion de un Ingreso\n");
        printf("5 - Baja de un Ingreso\n");
        printf("\n\n\nESC para volver al menu anterior");
        printf("\n---------------------------------------\n");

        fflush(stdin);
        opc = getch();

        switch (opc)
        {
        case '1':
            mostrarIngresoPaciente(arbolGeneral);
            opc = ESC;
            system("pause");
            break;

        case '2':

            system("cls");
            filtraIngresosPaciente(arbolGeneral,practicas);

            break;

        case '3':

            system("cls");

            int dni = obtenerDNI();

            nodoPaciente * buscado = buscaPaciente(arbolGeneral, dni);

            if(!buscado)
            {
                printf("\nEl paciente no se encuentra en Sistema. Procedemos a dar de alta. \n\n");

                stPaciente nuevo = cargaPaciente(dni);

                arbolGeneral = agregaPaciente(arbolGeneral,nuevo);

                buscado = buscaPaciente(arbolGeneral,dni);
            }

            nodoIngresos* existe = ingresoExistente(buscado->listaIngresos,obtenerFechaActual());

            if(existe)
            {
                existe->practicas = cargaPracticas(existe->dato.nroIngreso,existe->practicas,practicas,(*validos));
            }
            else
            {
                buscado->listaIngresos = altaIngresos(buscado->listaIngresos, practicas, (*validos),dni);
            }

            break;

        case '4':

            system("cls");
            arbolGeneral = modificarIngreso(arbolGeneral);

            break;
            case '5':

            system("cls");
            int dni2 = obtenerDNI();

            nodoPaciente * buscado2 = buscaPaciente(arbolGeneral, dni2);

            if(buscado)
            {
                buscado2->listaIngresos = bajaIngreso(buscado2->listaIngresos);
            }
            else{
                printf("El paciente no esta cargado en el sistema \n");
            }

            system("cls");

            break;
        case ESC:

            break;

        default:

            printf("Seleccione una opcion Valida\n");
            break;
        }

        finSistema(arbolGeneral,practicas,(*validos));

    }

    return arbolGeneral;
}

void menuEmpleados(nodoPaciente* arbolGeneral,stPractica practicas[],int validos)
{


    char opc;
    int dni = 0;

    while(opc != ESC)
    {
        system("cls");

        printf("\n---------------------------------------\n");
        printf("\n\nMENU EMPLEADOS\n\n\n");
        printf("1 - Ver listado de empleados \n");
        printf("2 - Modificacion empleados \n");
        printf("3 - Alta empleado \n");
        printf("\n\n\nESC para guardar cambios y cerrar sesion");
        printf("\n---------------------------------------\n");

        fflush(stdin);
        opc = getch();

        switch(opc)
        {
        case'1':
                system("cls");
            listarEmpleados(1);
            break;
        case'2':
                system("cls");
            modificarEmpleado(1);
            break;
        case'3':
                system("cls");
            altaEmpleado();
            break;
        case ESC:

            finSistema(arbolGeneral,practicas,validos);

            system("cls");
            printf(" GOODBYE ! \n");

            break;
        default:
            printf("Seleccione una opcion Valida\n");
            break;
        }
    }
    system("cls");
}

nodoPaciente * menuAdministrativo(nodoPaciente * arbolGeneral, stPractica practicas[],int *validos)
{
    char opc;
    while(opc != ESC)
    {
        system("cls");

        printf("\n---------------------------------------\n");
        printf("\n\nMENU ADMINISTRATIVO\n\n\n");
        printf("1 - PACIENTES"); //VER, CARGAR NUEVOS, MODIFICAR ALGUNOS DATOS
        printf("2 - INGRESOS"); //CARGAR INGRESOS (cargar practica si o si), MODIFICAR DATOS INGRESOS
        printf("3 - PRACTICAS"); //VER PRACTICAS DISPONIBLES, BUSCAR
        printf("\n\n\nESC para guardar cambios y cerrar sesion");
        printf("\n---------------------------------------\n");

        opc = getch();

        switch(opc)
        {
        case '1':

            system("cls");
            arbolGeneral = menuPacientesAdmin(arbolGeneral,practicas,(*validos));
            break;

        case '2':
            system("cls");
            arbolGeneral = menuIngresosAdmin(arbolGeneral,practicas,validos);
            break;

        case '3':

            mostrarPracticas(practicas,(*validos));
            break;

        case ESC:

            finSistema(arbolGeneral,practicas,(*validos));

            system("cls");

            printf(" GOODBYE ! \n");

            break;
        default:
            printf("Seleccione una opcion Valida\n");
            break;

        }
    }

    return arbolGeneral;
}

nodoPaciente *  menuTecyBio(nodoPaciente * arbolPacientes, stPractica arregloPracticas[], int * validos)
{
    int opc;
    while(opc != ESC)
    {
        system("cls");

        printf("\n---------------------------------------\n");
        printf("\n\n MENU TECNICOS Y BIOQUIMICOS \n\n\n");
        printf("1- Cargar resultados \n"); //BUSQUEDA PACIENTE, VER PRACTICAS REALIZADAS, CARGAR RESULTADOS,
        printf("2- Alta \n");//ALTA Y BAJA DE PRACTICAS (si no tienen ingresos asociados)
        printf("3- Modificacion\n");
        printf("\n\n\nESC para guardar cambios y cerrar sesion");
        printf("\n---------------------------------------\n");

        opc = getch();

        switch(opc)
        {
        case '1':
            system("cls");

            nodoPaciente* aux = arbolPacientes;

            printf("Ingrese el DNI del paciente: \n");

            int dni = 0;
            fflush(stdin);
            scanf("%i",&dni);

            nodoPaciente* busqueda = buscaPaciente(aux,dni);

            if(busqueda)
            {

                muestraListaIngresos(busqueda->listaIngresos);

                printf("Ingrese el ID de ingreso: \n");
                int id = 0;
                fflush(stdin);
                scanf("%i",&id);

                nodoIngresos * encontrado = buscaIngreso(busqueda->listaIngresos,id);

                if(encontrado)
                {
                    encontrado->practicas = cargarResultados(encontrado->practicas,arregloPracticas);
                }
                else{

                    printf("El id del ingreso es incorrecto \n");
                }
            }
            else
            {
                printf("El paciente no se puedo cargar ! \n");
            }
            break;
        case '2':
            altaPractica(arregloPracticas,validos);
            break;
        case '3':
            modificacionPractica(arregloPracticas,(*validos));
            break;
        case '4':
            cambiarEstadoPractica(arregloPracticas,(*validos));
            break;
        case ESC:
            finSistema(arbolPacientes,arregloPracticas,(*validos));

            system("cls");

            printf(" GOODBYE ! \n");

            break;

        default:
            printf("Opcion invalida ! \n");
            break;

        }
    }
    return arbolPacientes;
}

