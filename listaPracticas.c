#include "listaPracticas.h"
#include "arbolPacientes.h"
#include "login.h"
#include "menus.h"
#include "listaIngresos.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>


nodoPracticas * inicListaPractica() // Inicializa la lista
{
    return NULL;
}

nodoPracticas * crearNodoPractica(stPracxIngreso dato) // Funcion que crea un nuevo nodo Practicas
{

    nodoPracticas * nodoNuevo = (nodoPracticas*) malloc(sizeof(nodoPracticas));

    nodoNuevo->practica = dato;
    nodoNuevo->siguiente = NULL;

    return nodoNuevo;
}

nodoPracticas * buscaUltimoNodoPractica(nodoPracticas * listaPracticas) // Busca ultimo nodo
{
    nodoPracticas * aux = listaPracticas;

    if(aux != NULL)
    {
        while(aux->siguiente != NULL)
        {
            aux = aux->siguiente;
        }
    }

    return aux;
}

nodoPracticas * agregoFinalListaPractica(nodoPracticas* listaPracticas,stPracxIngreso nuevo) // Agrego el final de la lista
{
    nodoPracticas * ultimo;
    nodoPracticas * nuevoNodo;
    nuevoNodo = crearNodoPractica(nuevo);

    if(listaPracticas == NULL)
    {
        listaPracticas = nuevoNodo;
    }
    else
    {
        ultimo = buscaUltimoNodoPractica(listaPracticas);

        ultimo->siguiente = nuevoNodo;
    }

    return listaPracticas;
}

void muestraUnaPracticaIngreso(stPracxIngreso practica,stPractica arregloPracticas[]) // Muestra una practica Ingreso
{
    printf("\n---------------------------------------\n");
    printf("Practica: %s ",arregloPracticas[practica.NroPractica-1].nombrePractica);
    printf("\nNumero de ingreso: %i\n", practica.nroIngreso);
    printf("Numero de practica: %i\n", practica.NroPractica);
    printf("Resultado : %s\n", practica.Resultado);
    if(practica.eliminado == 0)
    {
        printf("Estado: ALTA\n");
    }else{

        printf("Estado: BAJA \n");

    }
}

nodoPracticas * cargaPracticas(int idIngreso,nodoPracticas * listaPracticas,stPractica practicas[],int validos) //Carga de practicas hasta que quiera el usuario
{
    char opc = 0;
    stPracxIngreso practicaIngreso;

    while(opc != ESC)
    {
        muestraPracticasPorCaracter(practicas,validos);
        fflush(stdin);

        int id = verificarID(practicas,validos);

        if(id != -1)
        {
            nodoPracticas* buscado = buscarPracticaxIngreso(listaPracticas,id);

            if(buscado)
            {
                printf("La practica ya se encuentra agendada para hoy ! \n");
            }
            else
            {
                practicaIngreso.nroIngreso = idIngreso;

                practicaIngreso.NroPractica = id;

                practicaIngreso.eliminado = 0;

                strcpy(practicaIngreso.Resultado,"Sin Resultados");

                listaPracticas = agregoFinalListaPractica(listaPracticas,practicaIngreso);

            }

            system("cls");

            printf("Practicas agregadas: \n\n");

            muestraListaPracticas(listaPracticas,practicas);
        }

        printf("\n\n\n Quiere agregar otra practica ? 'ESC' para salir, cualquier tecla para continuar agregando. \n");

        fflush(stdin);
        opc = getch();
    }

    return listaPracticas;
}

void muestraListaPracticas(nodoPracticas* listaPracticas,stPractica arregloPracticas[]) // Muestra lista
{
    while(listaPracticas != NULL)
    {
        muestraUnaPracticaIngreso(listaPracticas->practica,arregloPracticas);
        listaPracticas = listaPracticas->siguiente;
    }
}

nodoPracticas * cargaListaPracticas(nodoPracticas * listaPractica, int idIngreso) // Lee el archivo y carga la lista
{
    FILE * arch = fopen(ARCHIVOPRACTICASXINGRESOS,"rb");

    stPracxIngreso practicaIngreso;

    if(arch)
    {

        while(fread(&practicaIngreso,sizeof(stPracxIngreso),1,arch) > 0) //borrar los datos?
        {
            if(idIngreso == practicaIngreso.nroIngreso)
            {
                listaPractica = agregoFinalListaPractica(listaPractica,practicaIngreso);
            }
        }
    }
    else
    {

        printf("Error al abrir el archivo de Practicas x ingreso");
    }

    fclose(arch);

    return listaPractica;
}

nodoPracticas * buscarPracticaxIngreso(nodoPracticas * listaPracticas, int idPractica)
{
    nodoPracticas * nodoEncontrado = NULL;

    while(listaPracticas)
    {
        if(listaPracticas->practica.NroPractica == idPractica)
        {
            nodoEncontrado = listaPracticas;
        }

        listaPracticas = listaPracticas->siguiente;
    }

    return nodoEncontrado;
}

nodoPracticas * cargarResultados(nodoPracticas * listaPracticas,stPractica arregloPracticas[])
{

    muestraListaPracticas(listaPracticas,arregloPracticas);

    int idPractica = 0;

    printf("A que practica desea cargar el resultado");
    fflush(stdin);
    scanf("%i", &idPractica);

    char sinresultado[40] = "Sin Resultado";

    printf("Resultado %s \n", sinresultado);

    nodoPracticas * encontrado = buscarPracticaxIngreso(listaPracticas,idPractica);

    if(encontrado == NULL)
    {
        printf("La practica no se encuentra cargada en este ingreso ! \n");
        system("pause");
    }
    else if(strcmpi(sinresultado,encontrado->practica.Resultado) <= 0)
    {
        printf("Ingrese el resultado para la practica seleccionada");

        fflush(stdin);
        gets(sinresultado);
        printf("Resultado %s \n", sinresultado);
        strcpy(encontrado->practica.Resultado,sinresultado);
        system("pause");
    }
    else
    {
        printf("La practica ya tiene cargado un resultado \n");
        system("pause");
    }


    return listaPracticas;
}

nodoPracticas * bajaLista(nodoPracticas * listaPracticas)
{
    nodoPracticas * aux = listaPracticas;

    while (aux != NULL)
    {
        aux->practica.eliminado = 1;
        aux = aux->siguiente;
    }

    return listaPracticas;
}

void cargarArchivoIngresosPracticas(nodoPracticas * listaPracticas, FILE * archivoPracticas) //Carga el archivo con los datos de la lista recibida por paremetro
{
    nodoPracticas * aux = listaPracticas;

    while(aux != NULL)
    {
        fwrite(&aux->practica,sizeof(stPracxIngreso),1,archivoPracticas);

        aux = aux->siguiente;
    }

}

int buscaPractica(nodoPaciente *arbol, int nroPractica)
{
    int encontrado = -1;
    if(arbol)
    {
        encontrado = buscaPractica(arbol->Izq, nroPractica);

        nodoIngresos * aux = arbol->listaIngresos;

            while(aux)
            {
                nodoPracticas * auxp = aux->practicas;

                while(auxp)
                {
                    if(auxp->practica.NroPractica == nroPractica)
                    {
                        encontrado = 1;
                    }

                    auxp = auxp->siguiente;
                }

                aux = aux->siguiente;
            }

        encontrado = buscaPractica(arbol->Der, nroPractica);
    }

    return encontrado;

}


void bajaPractica(stPractica practicas[], int validos, nodoPaciente * arbol, int idPractica)
{
    int entontrado = buscaPractica(arbol,idPractica);

    if(entontrado != 1)
    {
        practicas[idPractica-1].eliminado = 1;
        printf("Practica dada de baja ! \n");


    }else{

        printf("La practica no puede ser dada de baja porque esta incluida en ingresos \n");

    }

}

