//
// Created by Josemi on 12/05/2026.
//

#ifndef PROYECTO_DEFINITIVO_LECTURASEGURA_H
#define PROYECTO_DEFINITIVO_LECTURASEGURA_H
#include "SerialPC.h"

typedef struct {
    char id[32];
    char nombre[32];
    int precio;
    int stock;
} Elementos;

int leer_entero(const char* mensaje);
void leer_cadena(const char* mensaje, char* destino, int tam_max);
int seleccionar_producto(Elementos *productos, int NProd, char *elecID, int *cant);
void proceso_monedero(HANDLE puerto, Elementos *productos, int i, int cant, int NProd);
int buscador_ID(Elementos *productos,int NProd, char *id);
int confirmar(const char *mensaje);
int leer_tecla_monedero(HANDLE puerto);
void mostrar_cambio(const char *str);
void pausa(void);
int verificar_contrasena(void);
int subir_productos_bin(Elementos *productos, const char *fichero);
int subir_productos_txt(Elementos *productos, const char *fichero);
int guardar_fichero_bin(Elementos *productos, int NProd, const char *fichero);
int guardar_fichero_txt(Elementos *productos, int NProd, const char *fichero);
#endif //PROYECTO_DEFINITIVO_LECTURASEGURA_H