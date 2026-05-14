#include <stdio.h>
#include "LecturaSegura.h"
#include <string.h>
#include <conio.h>

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
int leer_tecla_monedero(void) {
    char c;
    while (1) {
        c = _getch();
        if (c >= '1' && c <= '8') {
            printf("%c\n", c); // mostrar la tecla pulsada
            return c - '0';
        }
        printf("Error: opcion no valida\n");
    }
}