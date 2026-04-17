#ifndef PROPUESTA_PRACTICA_FUNCIONES_H
#define PROPUESTA_PRACTICA_FUNCIONES_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    char id;
    char nombre[32];
    float precio;
    int stock;
} Producto;


int leer_entero(const char *prompt, int *out);
int leer_float(const char *prompt, float *out);
int leer_cadena(const char *prompt, char *dst, size_t cap);
void prompt_menu();
int leer_menu(const char *prompt, int *out);
#endif //PROPUESTA_PRACTICA_FUNCIONES_H