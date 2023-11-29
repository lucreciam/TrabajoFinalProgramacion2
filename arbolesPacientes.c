#include "arbolPacientes.h"
#include "listaPracticas.h"
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


///FUNCIONES BASICAS ARBOLES

nodoPaciente * inicArbol()
{
    return NULL;
}

nodoPaciente * creaNodoPaciente(stPaciente dato) //recibe dato crea nodo
{
    nodoPaciente * nuevoNodo = (nodoPaciente*) malloc(sizeof(nodoPaciente));

    nuevoNodo->paciente = dato;

    nuevoNodo->listaIngresos = NULL;

    nuevoNodo->Izq = NULL;
    nuevoNodo->Der = NULL;

    return nuevoNodo;
}

nodoPaciente * agregaPaciente(nodoPaciente* arbol, stPaciente dato) //solo agrega el paciente al arbol ordenado, crea nodo adentro
{
    if(arbol == NULL)
    {
        nodoPaciente * nuevoNodo = creaNodoPaciente(dato);
        arbol = nuevoNodo;
    }
    else
    {
        if(dato.DNI < arbol->paciente.DNI)
        {
            arbol->Izq = agregaPaciente(arbol->Izq,dato);
        }
        else
        {
            arbol->Der = agregaPaciente(arbol->Der,dato);
        }
    }
    return arbol;
}

void muestraArbol(nodoPaciente * arbol) //Muestra arbol ordenado por DNI
{
    if(arbol)
    {
        muestraArbol(arbol->Izq);
        muestraPaciente(arbol->paciente);
        muestraArbol(arbol->Der);
    }
}

nodoPaciente * buscaPaciente(nodoPaciente * arbol,int dni) //recibe dni y devulve nodo NULL si no lo encuentra
{
    if (arbol == NULL)
    {
        return NULL;
    }

    if (arbol->paciente.DNI == dni)
    {
        return arbol;
    }
    else if (arbol->paciente.DNI > dni)
    {
        return buscaPaciente(arbol->Izq, dni);
    }
    else
    {
        return buscaPaciente(arbol->Der, dni);
    }
}



nodoPaciente* getNodoPaciente(nodoPaciente* arbol,int dni)
{
    if(!arbol)
    {
        return NULL;
    }

    if(arbol->paciente.DNI == dni)
    {
        return arbol;
    }
    arbol->Izq = buscaPaciente(arbol->Izq,dni);
    arbol->Der = buscaPaciente(arbol->Der,dni);
}




///FUNCIONES BASICAS ESTRUCTURA

stPaciente cargaPaciente(int dni) // carga estructura paciente
{
    stPaciente paciente;

    paciente.DNI = dni;

    char nombre[20];
    char apellido[20];
    printf("Ingrese el nombre\n");
    fflush(stdin);
    gets(nombre);

    printf("Ingrese el apellido\n");
    fflush(stdin);
    gets(apellido);

    strcat(nombre,apellido);
    strcpy(paciente.ApellidoyNombre,nombre);

    printf("Ingrese la edad\n");
    scanf("%i", &paciente.Edad);


    printf("Ingrese el telefono\n");
    fflush(stdin);
    gets(paciente.Telefono);

    paciente.Eliminado = 0; //por defecto activo

    printf("Ingrese el domicilio\n");
    fflush(stdin);
    gets(paciente.Domicilio);


    return paciente;
}

void muestraPaciente(stPaciente dato) //Muestra estructura paciente
{
    printf("---------------------------------------\n");
    printf("Apellido y nombre: %s \n", dato.ApellidoyNombre);
    printf("Edad: %d \n", dato.Edad);
    printf("DNI: %d \n", dato.DNI);
    printf("Domicilio: %s \n", dato.Domicilio);
    printf("Telefono: %s \n", dato.Telefono);

    if(dato.Eliminado == 1)
    {
        printf("Estado: Baja\n");
    }
    else
    {
        printf("Estado: Alta\n");
    }
    printf("---------------------------------------\n");
}

///FUNCIONES DE ARCHIVO

//void cargarArchivoPacientes(nodoPaciente * arbolPacientes) //carga las 3 estructuras en el archivo
//{
//
//    FILE * archivo = fopen(ARCHIVOPACIENTES,"wb");
//
//    if(archivo)
//    {
//        recorreArbolEscritura(arbolPacientes,archivo);
//    }
//    else
//    {
//        printf("ERROR No se abrio el archivo \n");
//    }
//
//    fclose(archivo);
//}

//void recorreArbolEscritura(nodoPaciente *arbolPacientes, FILE *archivo) //recorre el arbol y escribe los datos en el archivo
//{
//    if (arbolPacientes)
//    {
//        stPaciente nuevoPaciente = arbolPacientes->paciente;
//
//        fwrite(&nuevoPaciente, sizeof(stPaciente), 1, archivo);
//
//
//        printf("PACIENTE EN ESCRITURA ARCHIVO: ARBOL \n");
//        muestraPaciente(arbolPacientes->paciente);
//        system("pause");
//
//        printf("PACIENTE EN ESCRITURA ARCHIVO: ESTRUCTURA \n");
//        muestraPaciente(nuevoPaciente);
//        system("pause");
//
//
//
//
//
//        cargaArchivoIngresos(arbolPacientes->listaIngresos);
//
//
//
//        recorreArbolEscritura(arbolPacientes->Izq, archivo);
//
//        recorreArbolEscritura(arbolPacientes->Der, archivo);
//    }
//}

nodoPaciente * cargaArbolPacientes(nodoPaciente*  arbolPacientes) //lee el archivo y cargar las 3 estrcuturas
{
    FILE * archivo = fopen(ARCHIVOPACIENTES,"rb");

    if(archivo == NULL)
    {
        perror("\n Error al abrir el archivo de pacientes \n");
    }
    else
    {
        stPaciente paciente;

        while(fread(&paciente,sizeof(stPaciente),1,archivo) > 0)
        {
            arbolPacientes = cargarArbolDesdeArchivo(arbolPacientes,paciente);
        }
    }

    fclose(archivo);

    return arbolPacientes;
}

nodoPaciente* cargarArbolDesdeArchivo(nodoPaciente* arbol,stPaciente paciente)
{
    arbol = agregaPaciente(arbol,paciente);

    nodoPaciente * buscado = buscaPaciente(arbol,paciente.DNI);

    buscado->listaIngresos = cargarListaIngresosArchivo(buscado->listaIngresos,paciente.DNI);

    return arbol;
}



///MODIFICACION PACIENTE

stPaciente modificarAYP(stPaciente dato)
{
    printf("Ingrese nuevo Apellido y nombre:\n");
    fflush(stdin);
    gets(dato.ApellidoyNombre);

    return dato;
}
stPaciente modificarEdad(stPaciente dato)
{
    printf("Ingrese nueva Edad:\n");
    fflush(stdin);
    scanf("%i", &dato.Edad);
    return dato;
}
stPaciente modificarDomicilio(stPaciente dato)
{
    printf("Ingrese nuevo Domicilio:\n");
    fflush(stdin);
    gets(dato.Domicilio);
    return dato;
}
stPaciente modificarTelefono(stPaciente dato)
{
    printf("Ingrese nuevo Telefono:\n");
    fflush(stdin);
    gets(dato.Telefono);
    return dato;
}
stPaciente modificarAltaBaja(stPaciente dato)
{
    if(dato.Eliminado == 0)
    {
        printf("Paciente de Alta\n Desea darlo de baja? S\n");
        char opc;
        fflush(stdin);
        opc = getchar();
        if(opc=='S'||opc=='s')
        {
            dato.Eliminado=1;
        }
    }
    else
    {
        printf("Paciente de Baja\n Desea darlo de alta? S\n");
        char opc;
        fflush(stdin);
        opc = getchar();
        if(opc=='S'||opc=='s')
        {
            dato.Eliminado=0;
        }
    }
    return dato;
}

nodoPaciente * modificacionPaciente(nodoPaciente* arbol, int dni) //modificacion de datos del paciente
{
    nodoPaciente* buscado = buscaPaciente(arbol,dni);

    if(buscado == NULL)
    {
        printf("Error, No se encontro datos con el dni\n");
    }
    else
    {
        printf("Paciente a Modificar:\n");

        muestraPaciente(buscado->paciente);

        getchar();

        printf("Elija opcion a modificar\n");
        printf("1)- Apellido y Nombre\n");
        printf("2)- Edad\n");
        printf("3)- Domicilio\n");
        printf("4)- Telefono\n");
        printf("5)- Estado\n");
        int opc;

        fflush(stdin);

        opc = getchar();

        switch(opc)
        {
        case '1':
            system("cls");
            buscado->paciente = modificarAYP(buscado->paciente);
            break;
        case '2':
            system("cls");
            buscado->paciente = modificarEdad(buscado->paciente);
            break;
        case '3':
            system("cls");
            buscado->paciente = modificarDomicilio(buscado->paciente);
            break;
        case '4':
            system("cls");
            buscado->paciente = modificarTelefono(buscado->paciente);
            break;
        case '5':
            system("cls");
            buscado->paciente = modificarAltaBaja(buscado->paciente);
            break;
        default:
            printf("Error, porfavor seleccione opcion valida\n");
        }

    }
    ///Retorno la cabecera o el nodo modificado?
    return arbol;
}

nodoPaciente * altaPaciente (nodoPaciente * arbol) //cargar un nuevo paciente
{
    int dni = obtenerDNI();

    nodoPaciente * buscado = buscaPaciente(arbol,dni);

    if(buscado != NULL)
    {
        printf("Ya existe un paciente cargado con ese DNI");
    }
    else
    {

        arbol = agregaPaciente(arbol,cargaPaciente(dni));

    }
    return arbol;
}

int obtenerDNI() //verificacion de dni correcto
{
    char input[10];
    int dni;

    do
    {
        printf("Ingrese el DNI: ");
        fflush(stdin);
        scanf("%s", input);

        int i, todosDigitos = 1;

        for(i = 0; input[i] != '\0'; i++)
        {
            if (!isdigit(input[i]))
            {
                todosDigitos = 0;
                break;
            }
        }

        if (todosDigitos)
        {
            dni = atoi(input);

            if (dni <= 0)
            {
                printf("Por favor, ingrese un DNI valido.\n");
            }
        }
        else
        {
            printf("Por favor, ingrese un DNI numerico valido.\n");
        }

    } while (dni <= 0);

    return dni;
}

int contarNodos(nodoPaciente* arbol) //cuenta nodos en el arbol (para muestra alfabeticamente)
{
    if (arbol == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + contarNodos(arbol->Izq) + contarNodos(arbol->Der);
    }
}

void recorridoInorden(nodoPaciente* arbol, stPaciente* arreglo, int* indice) //recorre el arbol ordenado
{
    if (arbol != NULL)
    {
        recorridoInorden(arbol->Izq, arreglo, indice);
        arreglo[*indice] = arbol->paciente;
        (*indice)++;
        recorridoInorden(arbol->Der, arreglo, indice);
    }
}

int compararPacientes(const void* a, const void* b) //compara 2 strings
{
    return strcmp(((stPaciente*)a)->ApellidoyNombre, ((stPaciente*)b)->ApellidoyNombre);
}

void mostrarPacientesOrdenadosAlfabeticamente(nodoPaciente* arbol) //muestra pacientes alfabeticamente
{
    if(arbol == NULL)
    {
        printf("NO hay pacientes cargados \n");
    }

    int tamanioarreglo = contarNodos(arbol);

    stPaciente * arreglo = (stPaciente*)malloc(tamanioarreglo*sizeof(stPaciente));
    int indice = 0;
    recorridoInorden(arbol,arreglo,&indice);

    qsort(arreglo,tamanioarreglo,sizeof(stPaciente),compararPacientes);
    int i;
    for(i=0; i<tamanioarreglo; i++)
    {
        muestraPaciente(arreglo[i]);
    }
    free(arreglo);
    system("pause");
}


void busquedaMenuPacientes(nodoPaciente* arbol)
{
    int dni = 0;

    dni = obtenerDNI();

    nodoPaciente * buscado = buscaPaciente(arbol,dni);

    if(buscado == NULL)
    {
        printf("El paciente no esta cargado ! \n");

    }
    else   //VER
    {
        printf("Paciente encontrado ! \n");
        muestraPaciente(buscado->paciente);
        system("pause");

    }
}


void escribirArchivos(nodoPaciente * arbol)
{
    if(arbol != NULL)
    {
        FILE * archivoPacientes = fopen(ARCHIVOPACIENTES, "wb");
        FILE * archivoIngresos = fopen(ARCHIVOINGRESOS, "wb");
        FILE * archivoPracticas = fopen (ARCHIVOPRACTICASXINGRESOS, "wb");

        if(archivoPacientes && archivoIngresos && archivoPracticas)
        {
            recorreArbolEscritura(arbol,archivoPacientes, archivoIngresos, archivoPracticas);
            fclose(archivoPacientes);
            fclose(archivoPracticas);
            fclose(archivoIngresos);
        }
        else
        {
            printf("ERROR ABRIENDO ARCHIVOS \n");
        }
    }
}
void recorreArbolEscritura(nodoPaciente *arbolPacientes, FILE *archivoPacientes, FILE * archivoIngresos, FILE * archivoPracticas) //recorre el arbol y escribe los datos en el archivo
{
    if (arbolPacientes)
    {
        recorreArbolEscritura(arbolPacientes->Izq,archivoPacientes,archivoIngresos,archivoPracticas);

        fwrite(&arbolPacientes->paciente, sizeof(stPaciente), 1, archivoPacientes);

        cargaArchivoIngresos(arbolPacientes->listaIngresos,archivoIngresos, archivoPracticas);

        recorreArbolEscritura(arbolPacientes->Der,archivoPacientes,archivoIngresos,archivoPracticas);


    }
}


