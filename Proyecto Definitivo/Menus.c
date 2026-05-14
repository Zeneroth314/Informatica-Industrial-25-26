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
void menu_monedero() {
    printf("========== MONEDERO ==========\n");
    printf("1:  1 centimo\n");
    printf("2:  2 centimos\n");
    printf("3:  5 centimos\n");
    printf("4:  10 centimos\n");
    printf("5:  20 centimos\n");
    printf("6:  50 centimos\n");
    printf("7:  1 euro (100 centimos)\n");
    printf("8:  2 euros (200 centimos)\n");
}