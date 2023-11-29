#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "unistd.h"

#include "menus.h"
#include "arbolPacientes.h"
#include "listaIngresos.h"
#include "listaPracticas.h"
#include "login.h"
#include "practicas.h"
#include "practicas.h"
#include "time.h"


#define ESC 27

extern int CANT_PRACTICAS;


int comparar(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

int contarElementosArchivoPracticas()
{
    int elementos = 0;

    FILE* archi = fopen("Practicas.dat","rb");
    stPractica lectura;

    if(archi)
    {
        while(fread(&lectura,sizeof(stPractica),1,archi) > 0)
        {
            elementos++;
        }
    }

    fclose(archi);

    return elementos;
}

int levantarArchivoArreglosPracticas(stPractica practicas[])
{
    FILE * archivo = fopen("Practicas.dat","rb");

    int validos = contarElementosArchivoPracticas();

    if(!archivo)
    {
        printf("Error al abrir el archivo/n");
    }
    else
    {

        int i = 0;

        while(fread(&practicas[i], sizeof(stPractica), 1, archivo) == 1)
        {
            i++;
        }

    }
    fclose(archivo);

    return validos;
}

void muestraPracticasPorCaracter(stPractica practicas[], int validos)
{


    char nombrePractica[30];

    int flag = 0;
    char opc = 0;

    while(flag == 0)
    {
        system("cls");

        printf("Ingrese el nombre de la practica:  ");

        fflush(stdin);

        gets(nombrePractica);

        for(int i = 0; i < validos; i++)
        {
            if (strncasecmp(nombrePractica, practicas[i].nombrePractica, strlen(nombrePractica)) == 0)
            {
                muestraUnaPractica(practicas[i]);
            }
        }

        printf("\n\n\n Cualquier tecla para volver a buscar o ESC para terminar.\n ");

        fflush(stdin);

        opc = getch();

        if(opc == ESC)
        {
            flag = 1;
        }

        if(flag == 0)
        {
            system("cls");
            printf("Vamos de nuevo... \n");

        }


    }

}

int obtenerIndicePractica(stPractica arregloPracticas[],int validos,char nombrePractica[])
{
    for(int i = 0; i<validos; i++)
    {
        if(strcmpi(nombrePractica,arregloPracticas[i].nombrePractica) == 0)
        {
            return i;
        }
    }

    return -1;
}

void guardarCambiosArregloPracticas(stPractica practicas[],int validos)
{
    FILE* archi = fopen(ARCHIVOSOLOPRACTICAS,"wb");

    if(archi)
    {

        for(int i = 0; i < validos; i++)
        {
            fwrite(&practicas[i],sizeof(stPractica),1,archi);
        }
    }

    fclose(archi);
}

void altaPractica(stPractica arregloPracticas[],int* validos)
{
    system("cls");

    if( (*validos) < DIMARREGLO)
    {

        printf("Ingrese el nombre de la nueva Practica.\n");

        char nombrePractica[30];

        fflush(stdin);
        gets(nombrePractica);

        strcpy(arregloPracticas[*validos].nombrePractica,nombrePractica);

        arregloPracticas[*validos].nroPractica = (*validos+1);

        arregloPracticas[*validos].eliminado = 0;

        printf("Practica agregada exitosamente ! \n");

        mostrarPractica(arregloPracticas[*validos]);

        (*validos)++;
    }
    else
    {
        printf("No se pueden agregar mas practicas ! La clinica no da a vasto !\n");
    }
}

//void bajaPractica()
//{
//
//}




void mostrarPracticas(stPractica practicas[],int validos)
{
    system("cls");

    for(int i = 0; i < validos; i++)
    {
        muestraUnaPractica(practicas[i]);
    }

    printf("\n\n\n");

    system("pause");
}

///ModIficacion_de_practica: solo su nombre

int verificarID(stPractica practicas[],int validos)
{
    char control = 0;
    int id = 0;

    while(control != ESC && control != 's' && control != 'S')
    {
        printf("\nIngresa el ID de la practica: \n");
        fflush(stdin);
        scanf("%i",&id);

        if( (id-1) < validos && id > 0)
        {

            muestraUnaPractica(practicas[id-1]);

            printf("\nEsta es la practica ? \n \n 'S' para confirmar, ESC para salir.\n");
        }
        else
        {

            printf("\n ID Inexistente, cualquier tecla para ingresar nuevamente, ESC para salir \n");
        }

        fflush(stdin);
        control = getch();
    }


    if(control == 's' || control == 'S')
    {
        return id;
    }
    else
    {
        return -1;
    }



}

void modificacionPractica(stPractica practicas[],int validos)
{

    char cont = 0;

    while(cont != ESC)
    {
        system("cls");

        printf("\n---------------------------------------\n");
        printf("\nQue practica deseas modificar ? \n\n\n");
        printf("1- Ver listado de todas las practicas.\n");
        printf("2- Buscar por nombre.\n");

        char opcion = 0;
        fflush(stdin);

        opcion = getch();

        if(opcion == '1')
        {
            mostrarPracticas(practicas,validos);
            cont = ESC;
        }
        else if(opcion == '2')
        {
            muestraPracticasPorCaracter(practicas,validos);
            cont = ESC;
        }
        else
        {
            system("cls");
            printf("Opcion invalida. Intente nuevamente\n");


        }

    }

    int id = verificarID(practicas,validos);

    if(id != (-1))
    {
        system("cls");

        printf("Practica a modificar: \n");

        mostrarPractica(practicas[id-1]);

        printf("\n\nIngrese el nuevo nombre de la practica: ");

        gets(practicas[id-1].nombrePractica);

    }
    else
    {
        printf("No se pudo modificar el ID ! \n");
    }

}

void muestraUnaPractica(stPractica practica)
{

    printf("\n*******************\n");
    printf("Nombre de la practica: %s \n", practica.nombrePractica);
    printf("NRO practica %i \n", practica.nroPractica);
    if(practica.eliminado == 0)
    {
        printf("Estado : ALTA");
    }
    else
    {
        printf("Estado : BAJA");
    }

}

void mostrarPorNombrePracticas(stPractica practicas[],int validos)
{

    printf("Ingrese el nombre de la practica a buscar: \n");

    char nombrePractica[30];

    fflush(stdin);
    gets(nombrePractica);


    for(int i = 1; i < validos; i++)
    {
        if( strcmpi(nombrePractica,practicas[i].nombrePractica) == 0)
        {
            muestraUnaPractica(practicas[i]);
        }
    }
}

void mostrarPractica(stPractica practica)
{
    printf("\n-------------------------------------------------------\n");
    printf("Practica: %s\n", practica.nombrePractica);
    printf("ID: %i\n", practica.nroPractica);
    if (practica.eliminado == 0)
    {
        printf("Estado: Activa\n");
    }
    else
    {
        printf("Estado: Inactiva\n");
    }
}


void cambiarEstadoPractica(stPractica practicas[],int validos)
{
    mostrarPorNombrePracticas(practicas,validos);

    int id = verificarID(practicas,validos);

    if(practicas[id-1].eliminado == 0)
    {
        practicas[id-1].eliminado = 1;
    }
    else
    {
        practicas[id-1].eliminado = 0;
    }
}





/// SE USAN ????


void mostrarPracticaPorNumero(int nmroPractica)
{
    FILE* archivoPracticas = fopen(ARCHIVOSOLOPRACTICAS,"ab");

    stPractica aux;

    if(!archivoPracticas)
    {
        perror("");
    }
    else
    {
        while(fread(&aux, sizeof(stPractica),1,archivoPracticas)>0)
        {
            if(aux.nroPractica == nmroPractica)
            {
                mostrarPractica(aux);
            }
        }
    }
    fclose(archivoPracticas);
}


stPractica devuelvePractica(int nroPractica)
{
    system("cls");

    FILE* archivoPracticas = fopen(ARCHIVOSOLOPRACTICAS, "rb");

    stPractica aux;

    ///RETORNA EL NUMERO DE PRACTRICA EN -1 SI HAY UN ERROR
    if (archivoPracticas == NULL)
    {
        perror("ERROR");
        aux.nroPractica = -1;
        return aux;
    }
    else
    {
        while(fread(&aux,sizeof(stPractica),1,archivoPracticas) > 0)
        {
            if(aux.nroPractica == nroPractica)
            {
                return aux;
            }
        }
    }

    fclose(archivoPracticas);

    ///SI NO ENCUENTRA RETORNA NRO DE PRACTICA EN -1
    aux.nroPractica = -1;

    return aux;

}

