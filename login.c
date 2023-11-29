#include "login.h"
#include "menus.h"
#include "arbolPacientes.h"
#include "listaIngresos.h"
#include <unistd.h>


Empleado buscarCuenta(int dni)
{
    FILE* archi = fopen(archivoCuentas,"rb");

    Empleado lecturaArchivo;

    if(!archi)
    {
        printf("Error al abrir archivo para busqueda de Usuarios\n");
    }
    else
    {
        while(fread(&lecturaArchivo,sizeof(Empleado),1,archi) > 0)
        {
            if(lecturaArchivo.dni == dni)
            {
                fclose(archi);

                return lecturaArchivo;
            }
        }
    }

    fclose(archi);

    lecturaArchivo.dni = -1;

    return lecturaArchivo;

}

///FUNCIONES PARA MUESTRA DE EMPLEADOS:////////

void muestraUnEmpleado(Empleado muestraEmpleado)
{
    printf("\n-----------------------------------\n");
    printf("Empleado %s : %s \n",muestraEmpleado.perfil,muestraEmpleado.apellidoYNombre);

    printf("DNI: %i \n",muestraEmpleado.dni);

    printf("Usuario: %s",muestraEmpleado.usuario);

    printf("Contrasenia: ******** \n");
    printf("\n-----------------------------------\n");

}

void muestraUnEmpleadoAdmin(Empleado muestraEmpleado)
{
    printf("\n-----------------------------------\n");

    printf("Empleado %s \n",muestraEmpleado.perfil);
    printf("Nombre y Apellido : %s \n",muestraEmpleado.apellidoYNombre);

    printf("DNI: %i \n",muestraEmpleado.dni);
    printf("Usuario: %s \n",muestraEmpleado.usuario);
    printf("Contrasenia: %s \n",muestraEmpleado.contrasenia);
    printf("\n-----------------------------------\n");
}

void muestraEmpleadosAdmin(Empleado arregloEmpleados[],int validos)
{
    for (int i = 0; i < validos; i++)
    {
        muestraUnEmpleadoAdmin(arregloEmpleados[i]);
    }
}

void muestraEmpleados(Empleado arregloEmpleados[],int validos)
{
    for (int i = 0; i < validos; i++)
    {
        muestraUnEmpleado(arregloEmpleados[i]);
    }
}

void ordenarPorSeleccion(Empleado arreglo[], int n)
{
    int i, j, min_idx;
    Empleado temp;

    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;

        for (j = i + 1; j < n; j++)
        {
            if (strcmp(arreglo[j].apellidoYNombre, arreglo[min_idx].apellidoYNombre) < 0)
            {
                min_idx = j;
            }
        }

        temp = arreglo[min_idx];
        arreglo[min_idx] = arreglo[i];
        arreglo[i] = temp;
    }
}

int contarEmpleadosEnArchivo()
{
    FILE *archivo = fopen(archivoCuentas, "rb");

    if (!archivo)
    {
        printf("Error al abrir el archivo");
        return -1;
    }

    int contador = 0;

    Empleado empleado;

    while (fread(&empleado, sizeof(Empleado), 1, archivo) == 1 )
    {
        contador++;
    }

    fclose(archivo);

    return contador;
}

///MUESTRA UN LISTADO DE EMPLEADOS

void listarEmpleados(int esAdmin)
{
    int validos = contarEmpleadosEnArchivo();

    Empleado empleados[validos];

    FILE *archivo = fopen(archivoCuentas,"rb");

    rewind(archivo);

    int i = 0;

    if(validos > 0)
    {

        if (!archivo)
        {
            printf("\nError al abrir el archivo\n");
        }
        else
        {
            while(fread(&empleados[i],sizeof(Empleado),1,archivo) > 0 && i < validos)
            {
                i++;
            }

            /// Ordena el array de empleados alfab�ticamente

            ordenarPorSeleccion(empleados,validos);
        }

        if(esAdmin == 1)
        {
            muestraEmpleadosAdmin(empleados,validos);
        }
        else
        {
            muestraEmpleados(empleados,validos);
        }

        system("pause");

    }
    else
    {
        printf("No hay ningun empleado en Sistema ! \n");
    }

    fclose(archivo);
}

///ALTA Y BAJA EMPLEADOS///////////////
void altaEmpleado()
{
    Empleado nuevoEmpleado;

    int flag = 0;

    printf("Ingrese el DNI del nuevo Empleado: ");
    fflush(stdin);
    int dni = 0;
    scanf("%i",&dni);

    Empleado verif = buscarCuenta(dni);

    if(verif.dni == -1)
    {
        nuevoEmpleado.dni = dni;
        flag = 1;
    }
    else
    {
        printf("El DNI ingresado ya se encuentra registrado !");
        muestraUnEmpleado(verif);

    }

    if(flag == 1)
    {

        printf("Ingrese el Nombre y Apellido: ");
        fflush(stdin);
        gets(nuevoEmpleado.apellidoYNombre);

        printf("Ingrese el Usuario: ");
        fflush(stdin);
        gets(nuevoEmpleado.usuario);

        printf("Ingrese la contrasenia: ");
        fflush(stdin);
        gets(nuevoEmpleado.contrasenia);

        char control = 0;

        while(control != ESC)
        {
            printf("Elija el tipo de Perfil: \n");
            printf("1 - Administrador.\n");
            printf("2 - Administrativo.\n");
            printf("3 - Bioquimico.\n");
            printf("4 - Tecnico.\n");

            int perfil = 0;

            fflush(stdin);
            scanf("%i",&perfil);

            switch(perfil)
            {
            case 1:
                strcpy(nuevoEmpleado.perfil,"Administrador");
                control = ESC;
                break;
            case 2:
                strcpy(nuevoEmpleado.perfil,"Administrativo");
                control = ESC;
                break;
            case 3:
                strcpy(nuevoEmpleado.perfil,"Bioquimico");
                control = ESC;
                break;
            case 4:
                strcpy(nuevoEmpleado.perfil,"Tecnico");
                control = ESC;
                break;
            default:
                printf("Opcion inexistente ! Vamos de nuevo... ");

                break;
            }
        }

        nuevoEmpleado.eliminado = 0;

        FILE* archi = fopen(archivoCuentas,"ab");

        if(!archi)
        {
            printf("Error al arbrir archivo\n");
        }
        else
        {
            fwrite(&nuevoEmpleado,sizeof(Empleado),1,archi);
        }

        fclose(archi);
    }

}

void bajaEmpleado()
{
    printf("Ingrese el DNI del Empleado a dar de baja: \n");

    int dni = 0;
    fflush(stdin);
    scanf("%i",&dni);

    FILE* archi = fopen(archivoCuentas,"r+b");

    if(!archi)
    {
        printf("Error al abrir archivo, dar de baja\n");
    }
    else
    {
        Empleado buscado = buscarCuenta(dni);

        if(buscado.dni != -1)
        {
            Empleado nuevo;

            while(fread(&nuevo,sizeof(Empleado),1,archi) > 0 )
            {
                if(dni == nuevo.dni)
                {
                    nuevo.eliminado = 1;

                    fseek(archi,-sizeof(Empleado),SEEK_CUR);

                    fwrite(&nuevo,sizeof(Empleado),1,archi);
                }
            }
        }
        else
        {
            printf("El empleado no se encontro en el Sistema. /n");
        }
    }

    fclose(archi);
}

/// MODIFICACION DE EMPLEADOS/////////////////

void modificarEmpleado(int esAdmin)
{
    Empleado modificacion;
    char opc = 0;

    printf("Ingrese el DNI del Empleado a modificar: ");
    int dni = 0;
    fflush(stdin);
    scanf("%i",&dni);

    modificacion = buscarCuenta(dni);

    if(modificacion.dni == -1)
    {
        printf("El empleado no esta en sistema ! \n");
        opc = ESC;

    }

    while(opc != ESC)
    {
        printf("Empleado a Modificar:\n");

        muestraUnEmpleado(modificacion);

        system("pause");

        system("cls");

        printf("Elija opcion a modificar\n");
        printf("1)- Apellido y Nombre\n");
        printf("2)- Usuario\n");
        printf("3)- Contrasenia\n");
        printf("4)- Perfil\n");
        printf("5)- Estado\n");
        printf("\n\nESC para salir.\n\n");

        char control = 0;

        fflush(stdin);

        control = getch();

        switch(control)
        {

        case '1':
            system("cls");
            fflush(stdin);
            printf("Ingrese nuevo Nombre y Apellido: \n");
            gets(modificacion.apellidoYNombre);
            opc = ESC;
            break;
        case '2':
            system("cls");
            printf("Ingrese nuevo Usuario: \n");
            fflush(stdin);
            gets(modificacion.usuario);
            opc = ESC;
            break;
        case '3':
            system("cls");
            fflush(stdin);
            printf("Ingrese nueva Contrasenia: \n");
            gets(modificacion.contrasenia);
            opc = ESC;
            break;
        case '4':
            system("cls");
            fflush(stdin);
            printf("Ingrese nuevo Perfil: \n");
            gets(modificacion.perfil);
            opc = ESC;
            break;
        case '5':
            system("cls");
            if(modificacion.eliminado == 1)
            {
                modificacion.eliminado = 0;
                opc = ESC;
            }
            else
            {
                modificacion.eliminado = 1;
                opc = ESC;
            }
            break;
        case 27:
            opc = 27;
        default:
            printf("Error, porfavor seleccione opcion valida\n");

        }

        Empleado busqueda;

        int flag = 0;

        FILE* archi = fopen(archivoCuentas,"r+b");
        rewind(archi);
        int contador = 0;

        while (fread(&busqueda, sizeof(Empleado), 1, archi) > 0 && flag == 0)
        {
            //contador++;

            if (modificacion.dni == busqueda.dni)
            {
                // Volver al inicio del registro del empleado en el archivo
                if(fseek(archi,-sizeof(Empleado), SEEK_CUR) == 0)
                {
                    fwrite(&modificacion, sizeof(Empleado), 1, archi);

                    flag = 1;
                }
                else
                {
                    printf("ERROR EN SEEK \n");
                }

                // Escribir la informaci�n modificada en el archi

            }
        }


        fclose(archi);


        printf("Empleado Modificado exitosamente ! \n\n");

        muestraUnEmpleadoAdmin(modificacion);

    }
}

void ocultarPassword(char password[DIM]) // Funcion para ocultar la contrasenia
{
    printf("Contrasenia: ");


    int i = 0;
    char c;
    int j = 76;
    do
    {
        fflush(stdin);
        c = getch();
        j++;
        if (c == 8 && i > 0)  // Verificar si se presion� la tecla de retroceso
        {
            j--;
            j--;

            printf(" ");
            if (i > 0)
            {
                i--;
            }
        }
        else
        {
            if (c != 13 && c != 10)  // Ignorar las teclas Enter
            {
                password[i++] = c;
                printf("*");
            }
        }
    }
    while (c != 13 && c != 10 && i < 30);

    password[i] = '\0'; // Agregar el car�cter nulo de terminaci�n al final de la cadena

}

int login() //Funci�n principal de login
{
    FILE* archi = fopen(archivoCuentas,"r+b");

    Empleado logeando;
    Empleado lecturaArchivo;

    if(archi)
    {
        char control = 0;

        while (control != ESC)
        {
            system("cls");

            printf("\n\n<<<<<<<<<< LOGIN >>>>>>>>>>\n\n");

            printf("Usuario: ");
            fflush(stdin);
            gets(logeando.usuario);

            printf("\n");

            char password[20];
            fflush(stdin);
            ocultarPassword(password);

            strcpy(logeando.contrasenia,password);

            int flag = 0;

            while( fread(&lecturaArchivo,sizeof(Empleado),1,archi) > 0 && flag == 0)
            {

                if( (strcmpi(lecturaArchivo.usuario,logeando.usuario) == 0) && (strcmpi(lecturaArchivo.contrasenia,password) == 0) )
                {
                    flag = 1;

                    system("cls");

                    printf("\nBienvenido %s!\n",logeando.apellidoYNombre);

                    if(strcmpi(lecturaArchivo.perfil,"Administrador") == 0)
                    {
                        printf("\nCredenciales de Administrador.\n");

                        fclose(archi);



                        return 1;
                    }
                    else if(strcmpi(lecturaArchivo.perfil,"Administrativo") == 0)
                    {
                        printf("\nCredenciales de Administrativo.\n");

                        fclose(archi);



                        return 2;
                    }
                    else if (strcmpi(lecturaArchivo.perfil,"Bioquimico") == 0)
                    {
                        printf("\nCredenciales de Bioquimico.\n");

                        fclose(archi);



                        return 3;
                    }
                    else
                    {
                        printf("\nCredenciales de Tecnico.\n");

                        fclose(archi);



                        return 4;
                    }
                }
            }

            system("cls");

            rewind(archi);

            printf("\nUps ! Parece que ingresaste un usuario o contrasenia invalidos.\n");
            printf("\nESC para salir, cualquier tecla para volver a intentar. \n");

            fflush(stdin);
            control = getch();
        }
    }
    else
    {
        printf("ERROR AL ABRIR ARCHIVO DE EMPLEADOS \n");
    }

    fclose(archi);

    return -1; // Falla en el login
}
