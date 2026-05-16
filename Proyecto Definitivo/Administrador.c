#include <stdio.h>
#include "Administrador.h"
#include <string.h>
#include "LecturaSegura.h"
#include "Menus.h"

void administrador(Elementos *productos, int *NProd) {
    int i;
    int opcion = 0;
    while (opcion != 7) {
        system("cls");
        opcion = 0;
        menu_administrador();
        while (opcion < 1 || opcion > 7) {
            opcion = leer_entero("Introduzca la opcion que desee: ");
            if (opcion < 1 || opcion > 7) printf("Error: Introduzca valores correctos\n");
        }
        switch (opcion) {
            case 1:
                system("cls");
                listado(productos, *NProd);
                pausa();
                break;
            case 2:
                system("cls");
                i = buscador_ID_admin(productos, *NProd);
                if (i != -1) {
                    printf("=======================================================================\n");
                    printf("%-20s %-20s %-18s %-6s\n", "ID", "Nombre", "Precio(CENT)", "Stock");
                    printf("-----------------------------------------------------------------------\n");
                    printf("%-20s %-20s %-18d %-6d\n",productos[i].id,productos[i].nombre,productos[i].precio,productos[i].stock);
                    printf("=======================================================================\n");
                    pausa();
                    break;
                }
                    printf("No existe ese producto, volviendo al menu de administrador...\n");
                    pausa();
                    break;
            case 3:
                if (*NProd >= 40) {
                    printf("Limite de productos alcanzado, no se pueden añadr mas.\n");
                    pausa();
                } else {
                    *NProd = anadir_ID_admin(productos, *NProd);
                    pausa();
                }
                break;
            case 4: modificar_ID_admin(productos, *NProd);
                pausa();
                break;
            case 5: guardar_fichero(productos, *NProd);
                pausa();
                break;
            case 6:
                *NProd = borrar_producto(productos, *NProd);
                pausa();
                break;
            case 7: printf("Volviendo al menu general...\n");
                break;
        }
    }
}
int buscador_ID_admin(Elementos *productos, int NProd) {
    int i;
    char elecID[32];
    leer_cadena("Introduzca el ID del producto que desee: ",elecID,32);
    i = buscador_ID(productos, NProd,elecID);
    if (i == -1) {
        return -1;
    }
    return i;
}
int anadir_ID_admin(Elementos *productos, int NProd) {
    int buff;
    char buff2[32];
    leer_cadena("Introduzca el ID: ", buff2, 32);
    if (buscador_ID(productos, NProd, buff2) != -1) {
        printf("Ya existe ese ID en el sistema. \n");
        return NProd;
    }
        strcpy(productos[NProd].id, buff2);
        leer_cadena("Introduzca el nombre: ", buff2, 32);
        strcpy(productos[NProd].nombre, buff2);
        buff = leer_entero("Introduzca el precio: ");
        productos[NProd].precio = buff;
        buff = leer_entero("Introduzca el stock: ");
        productos[NProd].stock = buff;
        return NProd + 1;
}
void modificar_ID_admin(Elementos *productos, int NProd) {
    char buff2[32];
    int buff;
    int i;
    leer_cadena("Introduzca el ID: ", buff2, 32);
    i = buscador_ID(productos, NProd, buff2);
    if (i != -1) {
        leer_cadena("Introduzca el nuevo ID: ", buff2, 32);
        strcpy(productos[i].id, buff2);
        leer_cadena("Introduzca el nuevo nombre: ", buff2, 32);
        strcpy(productos[i].nombre, buff2);
        buff = leer_entero("Introduzca el nuevo precio: ");
        productos[i].precio = buff;
        buff = leer_entero("Introduzca el nuevo stock: ");
        productos[i].stock = buff;
    }
    else {
        printf("No existe ese ID en el sistema.\n");
    }
}
int borrar_producto(Elementos *productos, int NProd) {
    char buff[32];
    leer_cadena("Introduzca el ID del producto a borrar: ", buff, 32);
    int i = buscador_ID(productos, NProd, buff);
    if (i == -1) {
        printf("Error: no existe ese ID en el sistema.\n");
        return NProd;
    }
    printf("Producto encontrado: %s - %s\n", productos[i].id, productos[i].nombre);
    if (!confirmar("Desea borrar este producto")) {
        printf("Operacion cancelada.\n");
        return NProd;
    }
    int n;
    for (n = i; n < NProd - 1; n++) {
        productos[n] = productos[n+1];
    }
    printf("Producto borrado correctamente.\n");
    return NProd - 1;
}