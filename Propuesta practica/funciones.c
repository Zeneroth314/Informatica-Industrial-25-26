//
// Created by Josemi on 03/03/2026.
//

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

int prompt_menu() {
    printf("========== MENU ==========\n");
    printf("1: Introducir edad.\n");
    printf("2: Introducir altura (m).\n");
    printf("3: Introducir nombre.\n");

    //  Pequeño experimento para limpiar main.c usando un prompt ya diseñado aparte.
}