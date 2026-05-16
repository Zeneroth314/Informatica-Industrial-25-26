#include <stdio.h>
#include "LecturaSegura.h"
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "SerialPC.h"

int leer_entero(const char* mensaje) {
    int numero = 0;
    int c;
    int valido = 0;

    while (!valido) {
        printf("%s", mensaje);

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

int subir_productos(Elementos *productos) {
    FILE *fichero = fopen("productos.txt", "r");
    if (!fichero) {
        fichero = fopen("productos.txt", "w"); // Lo crea vacío
        fclose(fichero);
        printf("Se han cargado 0 productos\n");
        return 0;
    }
    int cantidad = 0;
    char buf[128];

    while (fgets(buf, sizeof(buf), fichero)) {
        Elementos *p = &productos[cantidad];

        if (sscanf(buf, "%31[^;];%31[^;];%d;%d", p->id, p->nombre, &p->precio, &p->stock) == 4) {
            cantidad++;
        }
    }

    fclose(fichero);
    printf("Se han cargado %d productos\n", cantidad);
    return cantidad;
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

int guardar_fichero(Elementos *productos, int NProd) {
    FILE *fichero = fopen("productos.txt", "w");
    if (!fichero) {
        printf("Error fichero no guardado\n");
        return 0;
    }
    for (int i = 0; i < NProd; i++) {
        fprintf(fichero, "%s;%s;%d;%d\n",
                productos[i].id,
                productos[i].nombre,
                productos[i].precio,
                productos[i].stock);
    }
    fclose(fichero);
    printf("Se han guardado %d productos correctamente\n", NProd);
    return 1;
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