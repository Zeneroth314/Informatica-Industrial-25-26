#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "funciones.h"

int main(void) {
    Producto productos[24]; //cantidad de productos que hay en el programa.
    int i;              // contador para escribir.
    int n = 0;
    int x=0;                  // x hace la verificación de que lo que entra al menú sea en el rango de 1 a 4, es la confirmación
    int salir2 = 0;
    int salir3 = 0;
    int salir=0;              // salir hace verificación de que salga
    int salir4 = 0;
    char aux[64];               // auxiliar para leer en añadir
    int guardado=0;
    float aux2;
    int escritura;
    int aux3;
    int aux4;
    aux2= 0;
    aux3 = 0;
    salir = 0;
    //subir_productos();
        while (!salir) {
            n=0;
            salir2 = 0;
            salir3 = 0;
            prompt_menu();
            while (!x) {
                leer_menu("Elija una opcion:  ", &n);
                if (n < 1 || n > 5) {
                    printf("Opcion no valida. Intentelo de nuevo. \n");
                    prompt_menu();
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
                    tabla();
                    for (escritura = 0; escritura < i; escritura++) {
                        printf("%-20s %-20s %-18.2f %-6d\n",productos[escritura].id,productos[escritura].nombre,productos[escritura].precio,productos[escritura].stock);
                    }
                    printf("=======================================================================\n");
                    printf("\n\n");
                    break;
                case 2:
                    n=0;
                    x=0;
                    guardado = 1;
                        for (;!salir2;i++) {
                            leer_cadena("Introduzca el ID: ", aux, sizeof(aux));
                            strcpy(productos[i].id, aux);
                            leer_cadena("Introduzca el nombre: ", aux, sizeof(aux));
                            strcpy(productos[i].nombre, aux);
                            leer_float("Introduzca el precio: ", &aux2);
                            productos[i].precio = aux2;
                            aux2 = 0;
                            leer_entero("Introduzca el stock: ", &aux3);
                            productos[i].stock = aux3;
                            aux3 = 0;
                            leer_cadena("Desea continuar anadiendo? Y/N: ",aux, sizeof(aux));
                            salir3 = 0;
                            while (!salir3) {
                                if (strcmp(aux, "Y") == 0 || strcmp(aux, "y") == 0) {
                                    salir2 = 0;
                                    salir3 = 1;
                                }
                                else if (strcmp(aux, "N") == 0 || strcmp(aux, "n") == 0) {
                                    salir2 = 1;
                                    salir3 = 1;
                                }
                                else {
                                    leer_cadena("Opcion no valida.\n Desea continuar anadiendo? Y/N: ",aux, sizeof(aux));
                                    salir3 = 0;
                                }
                            }
                        }
                    break;
                case 3:
                    x=0;
                    n=0;
                    guardado = 1;
                    while (!salir3) {
                        if (i==0) {
                            printf("No hay productos que modificar.\n\n");
                            break;
                        }
                        while (!salir2) {
                            leer_entero("Introduzca el numero de la posicion del producto que desea cambiar: ",&aux4);
                            if (aux4 - 1 > i || aux4 <= 0) {
                                printf("No existe el producto. ");
                                salir2 = 0;
                            }
                            else if (aux4 - 1 < i) {
                                salir2 = 1;
                            }
                        }
                        leer_cadena("Introduzca el ID: ", aux, sizeof(aux));
                        strcpy(productos[aux4-1].id, aux);
                        leer_cadena("Introduzca el nombre: ", aux, sizeof(aux));
                        strcpy(productos[aux4-1].nombre, aux);
                        leer_float("Introduzca el precio: ", &aux2);
                        productos[aux4-1].precio = aux2;
                        aux2 = 0;
                        leer_entero("Introduzca el stock: ", &aux3);
                        productos[aux4-1].stock = aux3;
                        aux3 = 0;
                        leer_cadena("Desea continuar modificando? Y/N: ",aux, sizeof(aux));
                        salir4=0;
                        while (!salir4) {
                            if (strcmp(aux, "Y") == 0 || strcmp(aux, "y") == 0) {
                                salir3 = 0;
                                salir4 = 1;
                            }
                            else if (strcmp(aux, "N") == 0 || strcmp(aux, "n") == 0) {
                                salir3 = 1;
                                salir4 = 1;
                            }
                            else {
                                leer_cadena("Opcion no valida.\n Desea continuar modificando? Y/N: ",aux, sizeof(aux));
                                salir4 = 0;
                            }
                        }
                    }
                    break;


                case 4:
                    n=0;
                    x=0;
                    guardado = 0;
                    guardar_fichero(productos, i);
                    if (guardar_fichero(productos,i)==1) printf("Fichero guardado con exito.\n\n");
                    break;
                case 5:
                    n=0;
                    salir4=0;
                    if (guardado) {
                        leer_cadena("Ha salido sin guardar. Desea guardar antes de salir? Y/N: ",aux, sizeof(aux));
                        while (!salir4) {
                            if (strcmp(aux, "Y") == 0 || strcmp(aux, "y") == 0) {
                                salir4 = 1;
                                guardar_fichero(productos, i);
                                if (guardar_fichero(productos,i)==1) printf("Fichero guardado con exito.\n\n");
                                salir = 1;
                            }
                            else if (strcmp(aux, "N") == 0 || strcmp(aux, "n") == 0) {
                                salir4 = 1;
                                salir = 1;
                            }
                            else {
                                leer_cadena("Opcion no valida.\n Desea continuar modificando? Y/N: ",aux, sizeof(aux));
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