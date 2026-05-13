#include <stdio.h>
#include <stdlib.h>
#include "Administrador.h"
#include "LecturaSegura.h"
#include "Menus.h"

int main(void) {
    Elementos productos[40];
    int i;                                  // Variable usada para acceder a array de elementos
    int ejecucion = 0;                      // Variable de ejecución del programa
    int cant;                               // Número de existencias
    int NProd;                              // Número de productos
    char elecID[32];                        // Elección de ID
    NProd = subir_productos(productos);
    while (!ejecucion) {
        int opcion=0;
        menu_general();
        while (opcion != 1 && opcion != 2 && opcion != 3) {
            opcion = leer_entero("Introduzca la opcion que desee:");
            if (opcion != 1 && opcion != 2 && opcion != 3) printf("Error: Introduzca valores correctos\n");
        }
        switch (opcion) {
            case 1:
                listado(productos,NProd);
                leer_cadena("Introduzca el ID del producto que desee: ",elecID,32);
                i = buscador_ID(productos, NProd,elecID);
                if (i == -1) {
                    printf("Error, no existe ese producto, volviendo al menu...\n");
                    break;
                }
                printf("Ha seleccionado: %s\n",productos[i].nombre);
                printf("Precio: %d centimos\n",productos[i].precio);
                printf("Existencias: %d unidades\n", productos[i].stock);

                cant = leer_entero("Cuantas unidades desea adquirir: ");
                if (cant > productos[i].stock) {
                    printf("Supera la cantidad de existencias de la que se dispone.\n");
                    if (confirmar("Desea establecer el maximo de existencias para la compra")) {
                        cant = productos[i].stock;
                    }
                    else {
                        printf("Volviendo al menu...\n");
                        break;
                    }
                }
                printf("Ha seleccionado comprar %d unidades de %s.\n ",cant, productos[i].nombre);
                break;
            case 2:
                    administrador(productos,&NProd);
                break;
            case 3:
                ejecucion = 1;
                break;
        }
    }
}