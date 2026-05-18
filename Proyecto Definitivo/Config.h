#ifndef PROYECTO_DEFINITIVO_CONFIG_H
#define PROYECTO_DEFINITIVO_CONFIG_H

#include <windows.h>

typedef struct {
    int com;
    int baud;
    char datos[64];
    char formato[4]; // "TXT" o "BIN"
} Configuracion;

int cargar_config(Configuracion *cfg);
void guardar_config(Configuracion *cfg);
void configurar_puerto(Configuracion *cfg);
HANDLE aplicar_config(Configuracion *cfg);
int elegir_baudrate(void);
extern Configuracion cfg;
#endif //PROYECTO_DEFINITIVO_CONFIG_H