#ifndef PROPUESTA_PRACTICA_FUNCIONES_H
#define PROPUESTA_PRACTICA_FUNCIONES_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    char id[32];
    char nombre[32];
    float precio;
    int stock;
} Producto;


int leer_entero(const char *prompt, int *out);
int leer_float(const char *prompt, float *out);
int leer_cadena(const char *prompt, char *dst, size_t cap);
void prompt_menu();
int leer_menu(const char *prompt, int *out);
void tabla();
int guardar_fichero(Producto *productos, int i);
int subir_productos();
#endif //PROPUESTA_PRACTICA_FUNCIONES_H