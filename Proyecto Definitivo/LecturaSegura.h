//
// Created by Josemi on 12/05/2026.
//

#ifndef PROYECTO_DEFINITIVO_LECTURASEGURA_H
#define PROYECTO_DEFINITIVO_LECTURASEGURA_H
typedef struct {
    char id[32];
    char nombre[32];
    int precio;
    int stock;
} Elementos;

int leer_entero(const char* mensaje);
void leer_cadena(const char* mensaje, char* destino, int tam_max);
int subir_productos(Elementos *productos);
int buscador_ID(Elementos *productos,int NProd, char *id);
int confirmar(const char *mensaje);
int  guardar_fichero(Elementos *productos, int NProd);
#endif //PROYECTO_DEFINITIVO_LECTURASEGURA_H