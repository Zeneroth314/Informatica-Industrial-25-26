#include <stdio.h>
#include <stdlib.h>
#include "Administrador.h"
#include "LecturaSegura.h"
#include "Menus.h"
#include "SerialPC.h"
#include <string.h>
#include "Config.h"

Configuracion cfg;

int main(void) {
    Elementos productos[40];
    int i;                                  // Variable usada para acceder a array de elementos
    int ejecucion = 0;                      // Variable de ejecución del programa
    int cant;                               // Número de existencias
    int NProd;                              // Número de productos
    char elecID[32];                        // Elección de ID
    HANDLE puerto;
    system("cls");
    if (cargar_config(&cfg)) {
        printf("Configuracion cargada:\n");
        printf("  COM:     %d\n", cfg.com);
        printf("  BAUD:    %d\n", cfg.baud);
        printf("  DATOS:   %s\n", cfg.datos);
        printf("  FORMATO: %s\n", cfg.formato);
        printf("\n");
        if (!confirmar("Desea usar esta configuracion")) {
            configurar_puerto(&cfg);
        }
    } else {
        printf("No se encontro configuracion. Configurando...\n");
        configurar_puerto(&cfg);
    }
    if (strcmp(cfg.formato, "BIN") == 0)
        NProd = subir_productos_bin(productos, cfg.datos);
    else
        NProd = subir_productos_txt(productos, cfg.datos);
    puerto = aplicar_config(&cfg);
    if (puerto == INVALID_HANDLE_VALUE) {
        printf("No se pudo abrir el puerto configurado.\n");
        if (confirmar("Desea reconfigurar el puerto")) {
            configurar_puerto(&cfg);
            puerto = aplicar_config(&cfg);
        }
    }
    pausa();
    while (!ejecucion) {
        system("cls");
        int opcion=0;
        menu_general();
        while (opcion != 1 && opcion != 2 && opcion != 3) {
            opcion = leer_entero("Introduzca la opcion que desee:");
            if (opcion != 1 && opcion != 2 && opcion != 3) printf("Error: Introduzca valores correctos\n");
        }
        switch (opcion) {
            case 1: {
                system("cls");
                i = seleccionar_producto(productos, NProd, elecID, &cant);
                if (i == -1) break;
                printf("Ha seleccionado comprar %d unidades de %s.\n", cant, productos[i].nombre);
                if (puerto != INVALID_HANDLE_VALUE) {
                    proceso_monedero(puerto, productos, i, cant, NProd);
                } else {
                    printf("Puerto serie no disponible\n");
                    pausa();
                }
                break;
            }
            case 2:
                system("cls");
                if (verificar_contrasena()) {
                    pausa();
                    administrador(productos, &NProd);
                }
                break;
            case 3:
                ejecucion = 1;
                break;
        }
    }
}
