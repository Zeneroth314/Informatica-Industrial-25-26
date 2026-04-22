#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "funciones.h"

int main(void) {
    Producto productos[24];     // Typedef de productos del sistema, por ahora con limite en 24.
    int i;                      // Cantidad de productos que hay en el sistema.
    int n = 0;                  // Verificador de caso en el switch.
    int x=0;                    // Verificación de que lo que entra al menú sea en el rango de 1 a 5.
    int salir=0;                // Hace verificación de que salga del programa entero.
    int salir2 = 0;             // Se utiliza para salir del bucle de escritura de productos nuevos.
    int salir3 = 0;             // Se usa para comprobar que se introduce "Y/N o y/n" en las opciones de si o no.
    int salir4 = 0;             // Igual que salir 3 para no arriesgarme a que se me crucen.
    int guardado=0;             // Verificación de si se ha guardado o no.
    char aux[64];               // Auxiliar para leer en añadir.
    float aux2 = 0;             // Idem.
    int aux3 = 0;               // Idem.
    int escritura;              // Usado en el bucle de listar para poner los productos en pantalla.
    i = subir_productos(productos);
    printf("Productos cargados: %d\n", i);
        while (!salir) {
            n=0;
            salir2 = 0;
            salir3 = 0;
            while (!x) {
                prompt_menu();
                leer_menu("Elija una opcion:  ", &n);
                if (n < 1 || n > 7) {
                    printf("Opcion no valida. Intentelo de nuevo. \n");
                }
                else x = 1;
            }
            switch (n) {
                case 1:
                    x=0;
                    n=0;
                    if (i==0) {
                        printf("No hay productos que mostrar.\n\n");
                        break;
                    }
                    cabecera_tabla();
                    for (escritura=0; escritura < i; escritura++) {
                        printf("%-20s %-20s %-18.2f %-6d\n",productos[escritura].id,productos[escritura].nombre,productos[escritura].precio,productos[escritura].stock);
                    }
                    printf("=======================================================================\n");
                    printf("\n\n");
                    break;
                case 2:
                    n=0;
                    x=0;
                    escritura = buscador_ID(productos, i);
                    if (escritura == -1) {
                        printf("ID inexistente.\n\n");
                        break;
                    }
                    cabecera_tabla();
                    printf("%-20s %-20s %-18.2f %-6d\n",productos[escritura].id,productos[escritura].nombre,productos[escritura].precio,productos[escritura].stock);
                    printf("-----------------------------------------------------------------------\n\n");
                    break;

                case 3:
                    n=0;
                    x=0;
                    guardado = 1;
                        for (;!salir2;) {
                            leer_cadena("Introduzca el ID del producto: ", aux, sizeof(aux));
                            if (buscador_ID_anadir(productos,i, aux)== 0) {
                                printf("ID ya usado.\n\n");
                                break;
                            }
                            strcpy(productos[i].id, aux);
                            leer_cadena("Introduzca el nombre: ", aux, sizeof(aux));
                            strcpy(productos[i].nombre, aux);
                            leer_float("Introduzca el precio: ", &aux2);
                            productos[i].precio = aux2;
                            aux2 = 0;
                            leer_entero("Introduzca el stock: ", &aux3);
                            productos[i].stock = aux3;
                            i++;
                            aux3 = 0;
                            if (confirmar_si_no ()) salir2 = 0;
                            else salir2 = 1;
                        }
                    break;
                case 4:
                    x=0;
                    n=0;
                    guardado = 1;
                    while (!salir3) {
                        if (i==0) {
                            printf("No hay productos que modificar.\n\n");
                            break;
                        }
                        salir2=0;
                        while (!salir2) {
                            escritura = buscador_ID(productos,i);
                            if (escritura==-1) {
                                printf("Error, ID inexistente\n\n");
                                salir3=1;
                                break;
                            }
                            salir2 = 1;
                        }
                        if (salir3) break;
                        leer_cadena("Introduzca el nuevo ID: ", aux, sizeof(aux));
                        strcpy(productos[escritura].id, aux);
                        leer_cadena("Introduzca el nombre: ", aux, sizeof(aux));
                        strcpy(productos[escritura].nombre, aux);
                        leer_float("Introduzca el precio: ", &aux2);
                        productos[escritura].precio = aux2;
                        aux2 = 0;
                        leer_entero("Introduzca el stock: ", &aux3);
                        productos[escritura].stock = aux3;
                        aux3 = 0;
                        if (confirmar_si_no ()) salir3 = 0;
                        else salir3 = 1;
                    }
                    break;
                case 5:
                    n=0;
                    x=0;
                    if (guardar_fichero(productos,i)==1) {
                        printf("Fichero guardado con exito.\n\n");
                        guardado = 0;
                    }
                    break;
                case 6:
                    n=0;
                    x=0;
                    aux3 =0;
                    guardado=1;
                    salir4 = 0;
                    salir3 =0;
                    while (!salir4) {
                        escritura = buscador_ID(productos,i);
                        if (escritura==-1) {
                            printf("Error, ID inexistente\n\n");
                        }
                        else{
                            salir4=1;
                        }
                    }
                        cabecera_tabla();
                        printf("%-20s %-20s %-18.2f %-6d\n",productos[escritura].id,productos[escritura].nombre,productos[escritura].precio,productos[escritura].stock);
                        printf("-----------------------------------------------------------------------\n\n");
                    while (!salir3) {
                        aux3 = confirmar_si_no_2();
                        if (aux3 == 1) {
                            i = borrar_producto(productos, escritura, i);
                            printf("Borrado\n\n");
                            salir3 = 1;
                        }
                        else if (aux3 == 0) {
                            printf("No borrado\n\n");
                            salir3 = 1;
                        }
                    }
                    break;


                case 7:
                    n=0;
                    salir4=0;
                    if (guardado) {
                        leer_cadena("Ha salido sin guardar. Desea guardar antes de salir? Y/N: ",aux, sizeof(aux));
                        while (!salir4) {
                            if (strcmp(aux, "Y") == 0 || strcmp(aux, "y") == 0) {
                                salir4 = 1;
                                if (guardar_fichero(productos,i)==1) printf("Fichero guardado con exito.\n\n");
                                salir = 1;
                            }
                            else if (strcmp(aux, "N") == 0 || strcmp(aux, "n") == 0) {
                                salir4 = 1;
                                salir = 1;
                            }
                            else {
                                leer_cadena("Opcion no valida.\n Desea guardar antes de salir? Y/N: ",aux, sizeof(aux));
                                salir4 = 0;
                            }
                        }
                    }
                    else {
                        salir = 1;
                    }
            }
        }

        return 0;
}