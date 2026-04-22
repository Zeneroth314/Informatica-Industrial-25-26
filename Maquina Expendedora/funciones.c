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
    printf("2: Buscar por ID.\n");
    printf("3: Anadir.\n");
    printf("4: Modificar.\n");
    printf("5: Guardar.\n");
    printf("6: Borrar producto.\n");
    printf("7: Salir.\n");
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
void cabecera_tabla(){
        printf("=======================================================================\n");
        printf("%-20s %-20s %-18s %-6s\n", "ID", "Nombre", "Precio(EUR)", "Stock");
        printf("-----------------------------------------------------------------------\n");
}

int guardar_fichero(Producto *productos, int i) {
            FILE *fichero = fopen("productos.txt", "w");
            if (!fichero) {
                printf("Error fichero no guardado\n");
                return 0;
            }
        for (int escritura = 0; escritura < i; escritura++) {
            fprintf(fichero, "%s;%s;%.2f;%d\n",
                    productos[escritura].id,
                    productos[escritura].nombre,
                    productos[escritura].precio,
                    productos[escritura].stock);
        }
    fclose(fichero);
    return 1;
}
int subir_productos(Producto *productos) {
    FILE *fichero = fopen("productos.txt", "r");
    if (!fichero) return 0;
    int cantidad = 0;
    char buf[128];
    while (fgets(buf, sizeof(buf), fichero)) {
        char id[32];
        char nombre[32];
        float precio;
        int stock;
        if (sscanf(buf, "%31[^;];%31[^;];%f;%d", id, nombre, &precio, &stock) == 4) {
            strcpy(productos[cantidad].id, id);
            strcpy(productos[cantidad].nombre, nombre);
            productos[cantidad].precio = precio;
            productos[cantidad].stock  = stock;
            cantidad++;
        }
    }
    fclose(fichero);
    return cantidad;
}
int buscador_ID(Producto *productos,int i) {
    char aux[32];
    int escritura;
    leer_cadena("Introduzca el ID del producto: ", aux, sizeof(aux));
    for (escritura = 0; escritura < i; escritura++) {
        if (strcmp(productos[escritura].id, aux) == 0) {
            return escritura;
        }
    }
    return -1;
}
int buscador_ID_anadir(Producto *productos,int i, char *aux) {
    int escritura;
    for (escritura = 0; escritura < i; escritura++) {
        if (strcmp(productos[escritura].id, aux) == 0) {
            return 0;
        }
    }
    return -1;
}
int borrar_producto(Producto *productos, int escritura, int i) {
    int n;
    for (n=escritura;n<i-1 ; n++) {
        productos[n] = productos[n+1];
    }
    i--;
    return i;
}
int confirmar_si_no () {
    char aux[64];
    leer_cadena("Desea seguir con la misma accion? Y/N: ",aux, sizeof(aux));
        if (strcmp(aux, "Y") == 0 || strcmp(aux, "y") == 0) {
            return 1;
        }
        if (strcmp(aux, "N") == 0 || strcmp(aux, "n") == 0) {
            return 0;
        }
    return confirmar_si_no ();
}
int confirmar_si_no_2 () {
    char aux[64];
    leer_cadena("Esta seguro de que es la opcion a borrar? Y/N: ",aux, sizeof(aux));
    if (strcmp(aux, "Y") == 0 || strcmp(aux, "y") == 0) {
        return 1;
    }
    if (strcmp(aux, "N") == 0 || strcmp(aux, "n") == 0) {
        return 0;
    }
    return confirmar_si_no_2 ();
}