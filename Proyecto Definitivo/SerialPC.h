#ifndef SERIALPC_H
#define SERIALPC_H

#include <windows.h>

HANDLE abrir_puerto(int num_puerto);
void   cerrar_puerto(HANDLE puerto);
int    enviar_datos(HANDLE puerto, int cant, int precio);
int    recibir_total(HANDLE puerto);
int    enviar_moneda(HANDLE puerto, int moneda, int acumulado, int total);
void   recibir_respuesta_monedero(HANDLE puerto, char *buf);
#endif