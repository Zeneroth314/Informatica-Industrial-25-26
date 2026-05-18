#include <stdio.h>
#include "LecturaSegura.h"
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "Menus.h"
#include "SerialPC.h"
#include "Config.h"

int leer_entero(const char* mensaje) {
    int numero = 0;
    int c;
    int valido = 0;

    while (!valido) {
        printf("%s", mensaje);
        fflush(stdout);

        numero = 0;
        int tieneDigitos = 0;
        int errorChar = 0;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c >= '0' && c <= '9') {
                numero = numero * 10 + (c - '0');
                tieneDigitos = 1;
            } else if (c != '\r') {
                errorChar = 1;
            }
        }
        if (tieneDigitos && !errorChar) {
            valido = 1;
        } else {
            printf("Error: Introduzca valores correctos.\n");
        }
    }

    return numero;
}

void leer_cadena(const char* mensaje, char* destino, int tam_max) {
    int c;
    int i = 0;
    printf("%s", mensaje);
    while ((c = getchar()) != '\n' && c != EOF) {
        if (i < tam_max - 1) {
            destino[i] = (char)c;
            i++;
        }
    }
    destino[i] = '\0';
}
int seleccionar_producto(Elementos *productos, int NProd, char *elecID, int *cant) {
    listado(productos, NProd);
    leer_cadena("Introduzca el ID del producto que desee: ", elecID, 32);
    int i = buscador_ID(productos, NProd, elecID);
    if (i == -1) {
        printf("Error, no existe ese producto, volviendo al menu...\n");
        pausa();
        return -1;
    }
    printf("Ha seleccionado: %s\n", productos[i].nombre);
    printf("Precio: %d centimos\n", productos[i].precio);
    printf("Existencias: %d unidades\n", productos[i].stock);
    if (productos[i].stock == 0) {
        printf("No hay existencias de este producto.\n");
        pausa();
        return -1;
    }
    *cant = leer_entero("Cuantas unidades desea adquirir: ");
    if (*cant > productos[i].stock) {
        printf("Supera la cantidad de existencias de la que se dispone.\n");
        if (confirmar("Desea establecer el maximo de existencias para la compra")) {
            *cant = productos[i].stock;
        } else {
            printf("Volviendo al menu...\n");
            pausa();
            return -1;
        }
    }
    return i;
}

int buscador_ID(Elementos *productos,int NProd, char *id) {
    int i;
    for (i = 0; i < NProd; i++) {
        if (strcmp(productos[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}
// En LecturaSegura.c
void proceso_monedero(HANDLE puerto, Elementos *productos, int i, int cant, int NProd) {
    int monedas[] = {0, 1, 2, 5, 10, 20, 50, 100, 200};
    int acumulado = 0;
    int cancelado = 0;
    char respuesta[64];

    enviar_datos(puerto, cant, productos[i].precio);
    int total = recibir_total(puerto);
    if (total == -1) return;
    printf("Total a pagar: %d centimos\n", total);
    iniciar_monedero(puerto);

    while (acumulado < total && !cancelado) {
        system("cls");
        menu_monedero(total, acumulado);
        printf("Introduce moneda: ");
        int eleccion = leer_tecla_monedero(puerto);
        if (eleccion == -1) {
            printf("Operacion cancelada desde el STM32.\n");
            cancelado = 1;
            continue;
        }
        enviar_moneda(puerto, monedas[eleccion], acumulado, total);
        recibir_respuesta_monedero(puerto, respuesta);

        if (strncmp(respuesta, "SIGUE", 5) == 0) {
            acumulado = 0;
            int k = 6;
            while (respuesta[k] >= '0' && respuesta[k] <= '9')
                acumulado = acumulado * 10 + (respuesta[k++] - '0');
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
            if (strcmp(cfg.formato, "BIN") == 0)
                guardar_fichero_bin(productos, NProd, cfg.datos);
            else
                guardar_fichero_txt(productos, NProd, cfg.datos);
            acumulado = total;
        }
    }
    pausa();
}

int confirmar(const char *mensaje) {
    char buf[64];
    char c;

    while (1) {
        printf("%s (S/N): ", mensaje);

        if (!fgets(buf, sizeof(buf), stdin)) continue;

        // Ignorar espacios y tomar el primer caracter real
        int i = 0;
        while (buf[i] == ' ' || buf[i] == '\t') i++;
        c = buf[i];

        if (c == 'S' || c == 's') return 1;
        if (c == 'N' || c == 'n') return 0;

        printf("Error: introduzca S o N\n");
    }
}
int leer_tecla_monedero(HANDLE puerto) {
    while (1) {
        if (_kbhit()) {
            char c = _getch();
            if (c >= '1' && c <= '8') {
                printf("%c\n", c);
                return c - '0';
            }
            printf("Error: opcion no valida\n");
        }
        // Comprobar botón STM32
        if (comprobar_boton(puerto)) {
            return -1; // señal de cancelación
        }
        Sleep(100); // esperar 100ms antes de volver a comprobar
    }
}
void mostrar_cambio(const char *str) {
    int i = 0;

    while (str[i] != '\0') {
        // Leer cantidad
        int cantidad = 0;
        while (str[i] >= '0' && str[i] <= '9') cantidad = cantidad*10 + (str[i++]-'0');
        if (str[i] == 'x') i++;
        // Leer valor
        int valor = 0;
        while (str[i] >= '0' && str[i] <= '9') valor = valor*10 + (str[i++]-'0');
        if (str[i] == ',') i++;

        // Nombre de la moneda
        const char *nombre;
        switch (valor) {
            case 1:   nombre = "1 centimo";   break;
            case 2:   nombre = "2 centimos";  break;
            case 5:   nombre = "5 centimos";  break;
            case 10:  nombre = "10 centimos"; break;
            case 20:  nombre = "20 centimos"; break;
            case 50:  nombre = "50 centimos"; break;
            case 100: nombre = "1 euro";      break;
            case 200: nombre = "2 euros";     break;
            default:  nombre = "desconocida"; break;
        }

        if (cantidad == 1)
            printf("  - %d moneda  de %s\n", cantidad, nombre);
        else
            printf("  - %d monedas de %s\n", cantidad, nombre);
    }
}
void pausa(void) {
    printf("\nPulse Enter para continuar...");
    // Limpiar buffer por si hay algo pendiente
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
int verificar_contrasena(void) {
    char contrasena[32];
    int intentos = 3;

    while (intentos > 0) {
        leer_cadena("Introduzca la contrasena: ", contrasena, 32);
        if (strcmp(contrasena, "admin123") == 0) {
            printf("Acceso concedido.\n");
            return 1;
        }
        intentos--;
        if (intentos > 0)
            printf("Contrasena incorrecta. Intentos restantes: %d\n", intentos);
    }
    printf("Acceso denegado. Volviendo al menu...\n");
    pausa();
    return 0;
}
int subir_productos_bin(Elementos *productos, const char *fichero) {
    FILE *f = fopen(fichero, "rb");
    if (!f) {
        f = fopen(fichero, "wb");
        if (f) fclose(f);
        printf("Se han cargado 0 productos\n");
        return 0;
    }
    int cantidad = 0;
    while (fread(&productos[cantidad], sizeof(Elementos), 1, f) == 1)
        cantidad++;
    fclose(f);
    printf("Se han cargado %d productos\n", cantidad);
    return cantidad;
}

int subir_productos_txt(Elementos *productos, const char *fichero) {
    FILE *f = fopen(fichero, "r");
    if (!f) {
        f = fopen(fichero, "w");
        if (f) fclose(f);
        printf("Se han cargado 0 productos\n");
        return 0;
    }
    int cantidad = 0;
    char buf[128];
    while (fgets(buf, sizeof(buf), f)) {
        Elementos *p = &productos[cantidad];
        if (sscanf(buf, "%31[^;];%31[^;];%d;%d", p->id, p->nombre, &p->precio, &p->stock) == 4) {
            cantidad++;
        }
    }
    fclose(f);
    printf("Se han cargado %d productos\n", cantidad);
    return cantidad;
}

int guardar_fichero_bin(Elementos *productos, int NProd, const char *fichero) {
    FILE *f = fopen(fichero, "wb");
    if (!f) { printf("Error: fichero no guardado\n"); return 0; }
    fwrite(productos, sizeof(Elementos), NProd, f);
    fclose(f);
    printf("Se han guardado %d productos correctamente\n", NProd);
    return 1;
}

int guardar_fichero_txt(Elementos *productos, int NProd, const char *fichero) {
    FILE *f = fopen(fichero, "w");
    if (!f) { printf("Error: fichero no guardado\n"); return 0; }
    for (int i = 0; i < NProd; i++)
        fprintf(f, "%s;%s;%d;%d\n", productos[i].id, productos[i].nombre,
                productos[i].precio, productos[i].stock);
    fclose(f);
    printf("Se han guardado %d productos correctamente\n", NProd);
    return 1;
}