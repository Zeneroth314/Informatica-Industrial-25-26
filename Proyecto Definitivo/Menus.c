#include <stdio.h>
#include "Menus.h"
#include "LecturaSegura.h"

void menu_general() {
    printf("========== MENU ==========\n");
    printf("1: Comprar productos.\n");
    printf("2: Area de administrador.\n");
    printf("3: Salir\n");
}

void menu_administrador() {
    printf("1: Listar.\n");
    printf("2: Buscar por ID.\n");
    printf("3: Anadir.\n");
    printf("4: Modificar.\n");
    printf("5: Guardar.\n");
    printf("6: Borrar producto.\n");
    printf("7: Salir.\n");
}
void listado(Elementos *productos,int NProd) {
    int i;
    printf("=======================================================================\n");
    printf("%-20s %-20s %-18s %-6s\n", "ID", "Nombre", "Precio(CENT)", "Stock");
    printf("-----------------------------------------------------------------------\n");
    for (i=0; i < NProd; i++) {
        printf("%-20s %-20s %-18d %-6d\n",productos[i].id,productos[i].nombre,productos[i].precio,productos[i].stock);
    }
    printf("=======================================================================\n");
}