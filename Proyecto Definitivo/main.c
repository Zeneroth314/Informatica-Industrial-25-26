#include <stdio.h>
#include <stdlib.h>
#include "Administrador.h"
#include "LecturaSegura.h"
#include "Menus.h"
#include "SerialPC.h"
#include <string.h>

int main(void) {
    Elementos productos[40];
    int i;                                  // Variable usada para acceder a array de elementos
    int ejecucion = 0;                      // Variable de ejecución del programa
    int cant;                               // Número de existencias
    int NProd;                              // Número de productos
    char elecID[32];                        // Elección de ID
    HANDLE puerto;
    int num_com;
    NProd = subir_productos(productos);
    num_com = leer_entero("Introduzca el numero de puerto COM: ");
    puerto = abrir_puerto(num_com);
    while (!ejecucion) {
        system("cls");
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
                    pausa();
                    break;
                }
                printf("Ha seleccionado: %s\n",productos[i].nombre);
                printf("Precio: %d centimos\n",productos[i].precio);
                printf("Existencias: %d unidades\n", productos[i].stock);
                if (productos[i].stock == 0) {
                    printf("No hay existencias de este producto.\n");
                    pausa();
                    break;
                }

                cant = leer_entero("Cuantas unidades desea adquirir: ");
                if (cant > productos[i].stock) {
                    printf("Supera la cantidad de existencias de la que se dispone.\n");
                    if (confirmar("Desea establecer el maximo de existencias para la compra")) {
                        cant = productos[i].stock;
                    }
                    else {
                        printf("Volviendo al menu...\n");
                        pausa();
                        break;
                    }
                }
                printf("Ha seleccionado comprar %d unidades de %s.\n", cant, productos[i].nombre);

                if (puerto != INVALID_HANDLE_VALUE) {
                    // Calcular total via STM32
                    enviar_datos(puerto, cant, productos[i].precio);
                    int total = recibir_total(puerto);
                    if (total == -1) break;
                    printf("Total a pagar: %d centimos\n", total);
                    iniciar_monedero(puerto);
                    // Monedero
                    int monedas[] = {0, 1, 2, 5, 10, 20, 50, 100, 200};
                    int acumulado = 0;
                    int cancelado = 0;
                    char respuesta[64];

                    while (acumulado < total && !cancelado) {
                        system("cls");
                        printf("========== MONEDERO ==========\n");
                        printf("Total a pagar:    %d centimos\n", total);
                        printf("Introducidas:     %d centimos\n", acumulado);
                        printf("Faltan:           %d centimos\n", total - acumulado);
                        printf("==============================\n");
                        printf("1: 1 centimo\n");
                        printf("2: 2 centimos\n");
                        printf("3: 5 centimos\n");
                        printf("4: 10 centimos\n");
                        printf("5: 20 centimos\n");
                        printf("6: 50 centimos\n");
                        printf("7: 1 euro (100 centimos)\n");
                        printf("8: 2 euros (200 centimos)\n");
                        printf("==============================\n");
                        printf("Introduce moneda: ");
                        int eleccion = leer_tecla_monedero(puerto);
                        if (eleccion == -1) {
                            printf("Operacion cancelada desde el STM32.\n");
                            cancelado = 1;
                            continue;
                        }

                        int moneda = monedas[eleccion];
                        enviar_moneda(puerto, moneda, acumulado, total);
                        recibir_respuesta_monedero(puerto, respuesta);

                        if (strncmp(respuesta, "SIGUE", 5) == 0) {
                            // Extraer nuevo acumulado
                            acumulado = 0;
                            int k = 6;
                            while (respuesta[k] >= '0' && respuesta[k] <= '9')
                                acumulado = acumulado * 10 + (respuesta[k++] - '0');
                            printf("Acumulado actualizado: %d centimos\n", acumulado);
                        } else if (strncmp(respuesta, "OK", 2) == 0) {
                            int cambio = 0;
                            int k = 3;
                            while (respuesta[k] >= '0' && respuesta[k] <= '9')
                                cambio = cambio * 10 + (respuesta[k++] - '0');
                            if (respuesta[k] == ';') k++;

                            printf("Pago completado.\n");
                            if (cambio > 0) {
                                printf("Cambio: %d centimos\n", cambio);
                                mostrar_cambio(&respuesta[k]);
                            } else {
                                printf("Sin cambio.\n");
                            }
                            productos[i].stock -= cant;
                            guardar_fichero(productos, NProd);
                            acumulado = total;
                        }
                    }
                } else {
                    printf("Puerto serie no disponible\n");
                }
                printf("Pulse Enter para volver al menu...");
                getchar();
                system("cls");
                break;
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