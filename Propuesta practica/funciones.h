//
// Created by Josemi on 03/03/2026.
//

#ifndef PROPUESTA_PRACTICA_FUNCIONES_H
#define PROPUESTA_PRACTICA_FUNCIONES_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int leer_entero(const char *prompt, int *out);
int leer_float(const char *prompt, float *out);
int leer_cadena(const char *prompt, char *dst, size_t cap);
int prompt_menu();
#endif //PROPUESTA_PRACTICA_FUNCIONES_H