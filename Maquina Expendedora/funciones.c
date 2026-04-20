#include "funciones.h"
#include <string.h>

int leer_entero(const char *prompt, int *out) {
    char buf[128];
    for (;;) {
        printf("%s", prompt);
        if (!fgets(buf, sizeof(buf), stdin)) return 0; // EOF
        errno = 0; // variable global de error en strol
        char *end = NULL;
        long v = strtol(buf, &end, 10);
        // Saltar espacios finales
        while (end && isspace((unsigned char)*end)) end++;

        if (errno == 0 && end && *end == '\0') {
            *out = (int)v;
            return 1;
        }
        printf("Valor invalido. Intenta de nuevo.\n");
    }
}

int leer_float(const char *prompt, float *out) {
    char buf[128];
    for (;;) {
        printf("%s", prompt);
        if (!fgets(buf, sizeof(buf), stdin)) return 0;
        errno = 0; // variable global de error en strof
        char *end = NULL;
        float v = strtof(buf, &end);
        while (end && isspace((unsigned char)*end)) end++;
        if (errno == 0 && end && *end == '\0') {
            *out = v;
            return 1;
        }
        printf("Valor invalido. Intenta de nuevo.\n");
    }
}

int leer_cadena(const char *prompt, char *dst, size_t cap) {
    printf("%s", prompt);
    if (!fgets(dst, cap, stdin)) return 0;
    // quitar \n si existe
    size_t n = strlen(dst);
    if (n > 0 && dst[n - 1] == '\n')
        dst[n - 1] = '\0';
    return 1;
}

void prompt_menu() {
    printf("========== MENU ==========\n");
    printf("1: Listar.\n");
    printf("2: Anadir.\n");
    printf("3: Modificar.\n");
    printf("4: Guardar.\n");
    printf("5: Salir.\n");
}

int leer_menu(const char *prompt, int *out) {
    char buf[128];
    for (;;) {
        printf("%s", prompt);
        if (!fgets(buf, sizeof(buf), stdin)) return 0; // EOF
        errno = 0; // variable global de error en strol
        char *end = NULL;
        long v = strtol(buf, &end, 10);
        // Saltar espacios finales
        while (end && isspace((unsigned char)*end)) end++;

        if (errno == 0 && end && *end == '\0') {
            *out = (int)v;
            return 1;
        }
        printf("Entrada no valida. Intentelo de nuevo.\n");
        prompt_menu();
    }
}
void tabla(){
        printf("=======================================================================\n");
        printf("%-20s %-20s %-18s %-6s\n", "ID", "Nombre", "Precio(EUR)", "Stock");
        printf("-----------------------------------------------------------------------\n");
}

int guardar_fichero(Producto *productos, int i) {
            FILE *fichero = fopen("productos.txt", "w");
            if (!fichero) {
                printf("Error fichero no guardado\n");
                return;
            }
        for (int escritura = 0; escritura < i; escritura++) {
            fprintf(fichero, "%s;%s;%.2f;%d\n",
                    productos[escritura].id,
                    productos[escritura].nombre,
                    productos[escritura].precio,
                    productos[escritura].stock);
        }
    fclose(fichero);
}
int subir_productos() {
    FILE *fichero = fopen("productos.txt", "r");
    if (!fichero) return 0;
}