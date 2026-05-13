#ifndef PROYECTO_DEFINITIVO_ADMINISTRADOR_H
#define PROYECTO_DEFINITIVO_ADMINISTRADOR_H
#include "LecturaSegura.h"

void administrador(Elementos *productos, int *NProd);
int buscador_ID_admin(Elementos *productos, int NProd);
int anadir_ID_admin(Elementos *productos, int NProd);
void modificar_ID_admin(Elementos *productos, int NProd);
int borrar_producto(Elementos *productos, int NProd);
#endif //PROYECTO_DEFINITIVO_ADMINISTRADOR_H