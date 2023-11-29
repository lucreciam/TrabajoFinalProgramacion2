
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


///FUNCIONES BASICAS

nodoIngresos * inicLista() // Inicializa la lista
{
    return NULL;
}

nodoIngresos * crearNodo(stIngresos dato) // Funcion que crea un nuevo nodo Ingreso
{

    nodoIngresos* nodoNuevo = (nodoIngresos*) malloc(sizeof(nodoIngresos));

    nodoNuevo->dato = dato;
    nodoNuevo->siguiente = NULL;
    nodoNuevo->practicas = inicListaPractica();

    return nodoNuevo;
}

nodoIngresos* agregoFinalListaIngresos(nodoIngresos* listaIngresos, stIngresos nuevo)
{
    nodoIngresos* ultimo;

    nodoIngresos* nuevoNodo;

    nuevoNodo = crearNodo(nuevo);

    if(listaIngresos == NULL)
    {
        listaIngresos = nuevoNodo;
    }
    else
    {
        ultimo = buscaUltimoNodoIngresos(listaIngresos);
        ultimo->siguiente = nuevoNodo;
    }

    return listaIngresos;
}

nodoIngresos * altaIngresos(nodoIngresos * lista,stPractica practicas[],int validos,int dni) //
{

    nodoIngresos* nuevoNodoIngresos = crearNodo(cargaIngreso(dni));

    nuevoNodoIngresos->practicas = cargaPracticas(nuevoNodoIngresos->dato.nroIngreso,nuevoNodoIngresos->practicas,practicas,validos);


    lista = agregarFinalNodo(nuevoNodoIngresos,lista);

return lista;
}

nodoIngresos * ingresoExistente (nodoIngresos * listaIngresos, stFecha fecha)
{
    nodoIngresos * aux = listaIngresos;
    nodoIngresos * encontrado = NULL;

    while(aux != NULL)
    {
        if(aux->dato.fechaIngreso.anio == fecha.anio)
        {
            if(aux->dato.fechaIngreso.mes == fecha.mes)
            {
                if(aux->dato.fechaIngreso.dia == fecha.dia)
                {
                    encontrado = aux;
                }
            }
        }
        aux = aux->siguiente;
    }

    return encontrado;
}

nodoIngresos* agregarFinalNodo(nodoIngresos* nuevoNodo,nodoIngresos* lista)
{
    if(!lista)
    {
        lista = nuevoNodo;
    }
    else
    {
        nodoIngresos* aux = buscaUltimoNodoIngresos(lista);
        aux->siguiente = nuevoNodo;
    }

    return lista;
}

nodoIngresos* buscaUltimoNodoIngresos(nodoIngresos* listaIngresos)
{
    nodoIngresos* aux = listaIngresos;

    if(aux != NULL)
    {
        while(aux->siguiente != NULL)
        {
            aux = aux->siguiente;
        }
    }

    return aux;
}

void muestraListaIngresos(nodoIngresos* listaIngresos)
{

    while(listaIngresos != NULL)
    {
        muestraIngreso(listaIngresos->dato);
        listaIngresos = listaIngresos->siguiente;
    }

}

void mostrarIngresoPaciente(nodoPaciente* arbolGeneral)
{
    int dni = obtenerDNI();

    nodoPaciente * buscado = buscaPaciente(arbolGeneral,dni);


    if(buscado)
    {
        muestraListaIngresos(buscado->listaIngresos);

    }
    else
    {
        printf("El paciente no esta en Sistema ! \n");
    }

}

nodoIngresos * bajaIngreso(nodoIngresos* listaIngresos)
{
    muestraListaIngresos(listaIngresos);
    getch();
    system("cls");

    printf("Ingrese el id del ingreso");
    int id =0;
    fflush(stdin);
    scanf("%i", &id);

    nodoIngresos * buscado = buscaIngreso(listaIngresos,id);


    if (buscado != NULL)
    {
        if(buscado->dato.eliminado == 1)
        {
            printf("El ingreso ya esta dado de baja");

        }
        else
        {
            buscado->dato.eliminado = 1;
            bajaLista(buscado->practicas);
        }
    }
    else
    {
        printf("No existe el Ingreso");
    }
    return listaIngresos;
}


///FUNCIONES DE LA ESTRCUTURA

stIngresos cargaIngreso(int dni)
{
    stIngresos ingreso;

    IDGLOBAL++;

    ingreso.nroIngreso = IDGLOBAL;

    ingreso.dni = dni;

    printf("Ingrese matricula del solicitante \n");
    fflush(stdin);
    scanf("%i",&ingreso.matriculaProfesional);

    ingreso.fechaIngreso = obtenerFechaActual(); //por defecto la actual

    printf("\nIngrese la fecha que desea retirar los Resultados: \n");
    ingreso.fechaRetiro = ingresarFecha();

    ingreso.eliminado = 0; //por defecto activa

    return ingreso;
}

void muestraIngreso(stIngresos i)
{
    printf("-----------------------------\n");
    printf("Numero de Ingreso....: %i \n",i.nroIngreso);
    printf("Fecha de ingreso: %02d/%02d/%04d\n", i.fechaIngreso.dia, i.fechaIngreso.mes, i.fechaIngreso.anio);
    printf("Fecha de Retiro: %02d/%02d/%04d\n", i.fechaRetiro.dia, i.fechaRetiro.mes, i.fechaRetiro.anio);
    printf("Matricula.........: %i \n", i.matriculaProfesional);
    if(i.eliminado == 0)
    {
        printf("Estado: ALTA \n");
    }else
    {
        printf("Estado: BAJA \n");
    }
}


///FUNCIONES EXTRAS

nodoIngresos* obtenerIngresoID(nodoPaciente* arbol, int id)
{
    if (!arbol)
    {
        return NULL;
    }

    nodoIngresos* aux = buscaIngreso(arbol->listaIngresos, id);

    if (!aux || aux->dato.nroIngreso != id)
    {
        aux = obtenerIngresoID(arbol->Izq, id);
    }

    if (!aux || aux->dato.nroIngreso != id)
    {
        aux = obtenerIngresoID(arbol->Der, id);
    }

    return aux;
}

void muestraIngresoPorDni(nodoPaciente* arbolGeneral)
{
    int dni = 0;
    int nro = 0;

    printf("\n Ingrese DNI del paciente: \n");

    fflush(stdin);
    scanf("%d", &dni);

    nodoPaciente * buscado = buscaPaciente(arbolGeneral,dni);

    printf("\n Ingrese Nro de Ingreso: \n");
    scanf("%d",&nro);

    nodoIngresos * buscadoIngreso = buscaIngreso(buscado->listaIngresos,nro);

    muestraIngreso(buscadoIngreso->dato);

}

void filtraIngresosPaciente(nodoPaciente* arbol,stPractica arregloPracticas[])
{
    system("cls");

    printf("Como desea filtrar la busqueda de Ingresos ? \n");

    int opc = 0;
    char control = 0;

    while(control != ESC)
    {
        printf("1) Filtrar por DNI. \n");
        printf("2) Filtrar por ID de Ingreso. \n");
        printf("3) Filtrar por Fecha. \n");


        fflush(stdin);
        scanf("%i",&opc);

        switch(opc)
        {
        case 1:
            printf("Ingrese el DNI del paciente: \n");
            int dni = 0;
            fflush(stdin);
            scanf("%i",&dni);

            arbol = buscaPaciente(arbol,dni);

            if(arbol)
            {
                system("cls");

                nodoIngresos* muestradeIngresos = arbol->listaIngresos;

                while(muestradeIngresos)
                {
                    muestraIngreso(muestradeIngresos->dato);

                    nodoPracticas* muestradePracticas = muestradeIngresos->practicas;
                    system("pause");

                    while(muestradePracticas)
                    {

                        printf("Practicas asociadas: \n");

                        muestraUnaPracticaIngreso(muestradePracticas->practica,arregloPracticas);

                        muestradePracticas = muestradePracticas->siguiente;
                        system("pause");
                    }

                    muestradeIngresos = muestradeIngresos->siguiente;
                }
            }
            else
            {
                printf("El paciente no esta en Sistema ! \n");
                system("pause");
            }

            control = ESC;

            break;
        case 2:

            printf("Ingrese el ID de Ingreso: \n");
            int id = 0;
            fflush(stdin);
            scanf("%i",&id);

            nodoIngresos * ingresos = obtenerIngresoID(arbol,id);

            if(ingresos)
            {
                system("cls");

                muestraIngreso(ingresos->dato);
                printf("Practicas asociadas: \n\n");
                muestraListaPracticas(ingresos->practicas,arregloPracticas);
            }
            else
            {
                printf("No hay Ingresos con ese ID ! \n");
            }


            control = ESC;

            break;
        case 3:
            printf("Filtrado por fecha.\n");

            stFecha fecha = cargarFecha();
            filtraIngresosPorFecha(arbol,fecha,arregloPracticas);

            control = ESC;

            break;
        default:
            printf("Opcion invalida ! Vamos de nuevo.. \n");
            break;

        }
    }

    system("pause");
}

void filtraIngresosPorFecha(nodoPaciente*  arbol,stFecha fecha,stPractica practicas[])
{
    if(arbol)
    {
        nodoIngresos* aux = arbol->listaIngresos;

        while(aux)
        {
            if((aux->dato.fechaIngreso.anio) == (fecha.anio))
            {
                if((aux->dato.fechaIngreso.mes) == (fecha.mes))
                {
                    if((aux->dato.fechaIngreso.dia )== (fecha.dia))
                    {
                        system("cls");
                        muestraIngreso(aux->dato);
                        printf("Practicas asociadas: \n\n");
                        muestraListaPracticas(aux->practicas,practicas);

                        fflush(stdin);
                        getch();
                    }
                }
            }

            aux = aux->siguiente;
        }

        filtraIngresosPorFecha(arbol->Izq,fecha,practicas);

        filtraIngresosPorFecha(arbol->Der,fecha,practicas);

    }
}

void muestraIngresoPorFecha(nodoPaciente*  arbolGeneral)
{
    stFecha desde;
    stFecha hasta;

    int dni=0;
    printf("\nIngrese DNI del paciente: \n");
    scanf("%d", &dni);
    nodoPaciente * buscado = buscaPaciente(arbolGeneral,dni);

    printf("\nIngrese Fecha porfavor\n");
    printf("\nDesde:");
    desde = cargarFecha();
    printf("\nHasta:");
    hasta = cargarFecha();

    while( (buscado->listaIngresos->dato.fechaIngreso.anio > desde.anio )&&(buscado->listaIngresos->dato.fechaIngreso.anio < hasta.anio))
    {
        while( (buscado->listaIngresos->dato.fechaIngreso.mes > desde.mes )&&( buscado->listaIngresos->dato.fechaIngreso.mes < hasta.mes))
        {
            while((buscado->listaIngresos->dato.fechaIngreso.dia>desde.dia )&& (buscado->listaIngresos->dato.fechaIngreso.dia<hasta.dia))
            {

                muestraIngreso(buscado->listaIngresos->dato);
            }
        }
    }

}

nodoIngresos * validacionFecha(stIngresos ingreso, nodoPaciente*buscado)
{
    nodoIngresos * aux = buscado->listaIngresos;

    while(aux!=NULL)
    {
        if(ingreso.fechaIngreso.anio == aux->dato.fechaIngreso.anio)
        {
            if(ingreso.fechaIngreso.mes ==aux->dato.fechaIngreso.mes)
            {
                if(ingreso.fechaIngreso.dia == aux->dato.fechaIngreso.dia)
                {
                    return aux;
                }
            }
        }
        aux = aux->siguiente;
    }
    return aux;
}

nodoIngresos * buscaIngreso(nodoIngresos * listaIngresos, int idIngreso)
{
    nodoIngresos * nodoBuscado = NULL;

    while(listaIngresos)
    {

        if(listaIngresos->dato.nroIngreso == idIngreso)
        {
             nodoBuscado = listaIngresos;
        }

        listaIngresos = listaIngresos->siguiente;
    }

    return nodoBuscado;
}

///FUNCIONES DE ARCHIVOS

nodoIngresos * cargarListaIngresosArchivo(nodoIngresos *ingresosPaciente,int dni)
{
    FILE * arch = fopen(ARCHIVOINGRESOS, "rb");

    stIngresos ingreso;

    if(arch)
    {
        while( fread(&ingreso,sizeof(stIngresos),1,arch) > 0) //borrar los datos?
        {
            if(ingreso.dni == dni)
            {
                nodoIngresos* nuevoNodo = crearNodo(ingreso);

                ingresosPaciente = agregarFinalNodo(nuevoNodo,ingresosPaciente);

                nuevoNodo->practicas = cargaListaPracticas(nuevoNodo->practicas,ingreso.nroIngreso);
            }
        }
    }else
    {

        printf("Error al abrir el archivo de ingresos \n");

    }

    fclose(arch);

    return ingresosPaciente;

}

int buscaIdIngresoMayor()
{
    FILE * arch = fopen(ARCHIVOINGRESOS, "rb");

    int max = 0;

    if(arch)
    {
        stIngresos ingreso;

        while(fread(&ingreso,sizeof(stIngresos),1,arch) > 0)
        {
            if(ingreso.nroIngreso > max)
            {
                max = ingreso.nroIngreso;
            }
        }
    }

    fclose(arch);

    return max;
}

nodoPaciente * modificarIngreso(nodoPaciente* arbol)
{
    int dni = 0;
    printf("Numero de dni del Paciente: \n");
    fflush(stdin);
    scanf("%i",&dni);

    nodoPaciente* busquedaPaciente = buscaPaciente(arbol,dni);

    nodoIngresos* busquedaIngreso;

    if(busquedaPaciente)
    {
        printf("Lista de ingresos para el paciente %s :\n\n",busquedaPaciente->paciente.ApellidoyNombre);

        muestraListaIngresos(busquedaPaciente->listaIngresos);

        int idIngreso = 0;
        printf("Seleccione un numero de ingreso a modificar: \n");
        fflush(stdin);
        scanf("%i",&idIngreso);

        busquedaIngreso = buscaIngreso(busquedaPaciente->listaIngresos,idIngreso);

        if(busquedaIngreso)
        {

            int opc = 0;
            char control = 0;

            while(control != ESC)
            {
                system("cls");

                printf("1) Modificar Fecha de retiro. \n");
                printf("2) Modificar Matricula del Profesional. \n");

                fflush(stdin);
                scanf("%i",&opc);

                switch(opc)
                {

                    case 1:
                        printf("Ingrese la nueva fecha de retiro: \n");

                        busquedaIngreso->dato.fechaRetiro = ingresarFecha();

                        control = ESC;

                        break;

                    case 2:

                        printf("Ingrese la nueva matricula: \n");

                        scanf("%i",&busquedaIngreso->dato.matriculaProfesional);

                        control = ESC;

                        break;

                    default:
                        printf("Opcion invalida ! Ingrese nuevamente o ESC para salir. \n");

                        fflush(stdin);
                        control = getch();

                        break;

                }

            }

        }
        else
        {
            printf("El ingreso no existe ! \n");

            busquedaPaciente = inicArbol();

            return busquedaPaciente;
        }
    }
    else
    {

        printf("El paciente ingresado no existe ! \n");

        return busquedaPaciente;
    }

    system("cls");

    printf("Ingreso modificado exitosamente ! \n");

    muestraIngreso(busquedaIngreso->dato);

    fflush(stdin);

    getch();

    return arbol;
}

void cargaArchivoIngresos(nodoIngresos *listaIngresos, FILE * archivoIngresos, FILE * archivoPracticas)
{
    nodoIngresos * aux = listaIngresos;

    while (aux != NULL)
        {
            fwrite(&aux->dato,sizeof(stIngresos),1,archivoIngresos);

            cargarArchivoIngresosPracticas(listaIngresos->practicas, archivoPracticas);

            aux = aux->siguiente;
        }

}


