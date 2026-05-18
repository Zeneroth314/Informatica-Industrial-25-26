#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "Config.h"
#include "LecturaSegura.h"

#define FICHERO_CONFIG "config.cfg"

int cargar_config(Configuracion *cfg) {
    FILE *f = fopen(FICHERO_CONFIG, "r");
    if (!f) return 0;

    char linea[64];
    while (fgets(linea, sizeof(linea), f)) {
        if (strncmp(linea, "COM=", 4) == 0)
            cfg->com = atoi(linea + 4);
        else if (strncmp(linea, "BAUD=", 5) == 0)
            cfg->baud = atoi(linea + 5);
        else if (strncmp(linea, "DATOS=", 6) == 0) {
            strncpy(cfg->datos, linea + 6, 63);
            // Quitar salto de linea
            cfg->datos[strcspn(cfg->datos, "\r\n")] = '\0';
        }
        else if (strncmp(linea, "FORMATO=", 8) == 0) {
            strncpy(cfg->formato, linea + 8, 3);
            cfg->formato[strcspn(cfg->formato, "\r\n")] = '\0';
        }
    }
    fclose(f);
    return 1;
}

void guardar_config(Configuracion *cfg) {
    FILE *f = fopen(FICHERO_CONFIG, "w");
    if (!f) {
        printf("Error: no se pudo guardar la configuracion.\n");
        return;
    }
    fprintf(f, "COM=%d\n", cfg->com);
    fprintf(f, "BAUD=%d\n", cfg->baud);
    fprintf(f, "DATOS=%s\n", cfg->datos);
    fprintf(f, "FORMATO=%s\n", cfg->formato);
    fclose(f);
    printf("Configuracion guardada correctamente.\n");
}
int elegir_baudrate(void) {
    int bauds[] = {9600, 19200, 38400, 57600, 115200};
    printf("Seleccione baudrate:\n");
    printf("1: 9600\n");
    printf("2: 19200\n");
    printf("3: 38400\n");
    printf("4: 57600\n");
    printf("5: 115200\n");
    int op = 0;
    while (op < 1 || op > 5) {
        op = leer_entero("Opcion: ");
        if (op < 1 || op > 5) printf("Error: opcion no valida\n");
    }
    return bauds[op - 1];
}

void configurar_puerto(Configuracion *cfg) {
    int puerto_valido = 0;

    while (!puerto_valido) {
        system("cls");
        printf("===== CONFIGURACION DEL PUERTO SERIE =====\n");
        printf("Puertos COM van del 1 al 20.\n");
        printf("Consulte el Administrador de dispositivos\n");
        printf("para ver que puerto tiene el STM32.\n\n");
        fflush(stdout);

        cfg->com  = leer_entero("Introduzca el numero de puerto COM: ");
        cfg->baud = elegir_baudrate();

        // Verificar que el puerto abre correctamente
        HANDLE test = aplicar_config(cfg);
        if (test != INVALID_HANDLE_VALUE) {
            CloseHandle(test);
            puerto_valido = 1;
        } else {
            printf("Puerto COM%d no disponible o incorrecto.\n", cfg->com);
            if (!confirmar("Desea intentarlo con otro puerto")) {
                break; // sale aunque sea incorrecto
            }
        }
    }

    leer_cadena("Nombre del fichero de datos (ej: productos.txt): ", cfg->datos, 64);

    printf("Formato del fichero:\n");
    printf("1: TXT\n");
    printf("2: BIN\n");
    fflush(stdout);
    int fmt = 0;
    while (fmt < 1 || fmt > 2) {
        fmt = leer_entero("Opcion: ");
        if (fmt < 1 || fmt > 2) printf("Error: opcion no valida\n");
    }
    strcpy(cfg->formato, fmt == 1 ? "TXT" : "BIN");

    guardar_config(cfg);
    pausa();
}

HANDLE aplicar_config(Configuracion *cfg) {
    char nombre[20];
    sprintf(nombre, "\\\\.\\COM%d", cfg->com);

    HANDLE puerto = CreateFile(nombre, GENERIC_READ | GENERIC_WRITE,
                               0, NULL, OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL, NULL);

    if (puerto == INVALID_HANDLE_VALUE) {
        printf("Error: no se pudo abrir COM%d\n", cfg->com);
        return INVALID_HANDLE_VALUE;
    }

    DCB dcb = {0};
    dcb.DCBlength = sizeof(DCB);
    GetCommState(puerto, &dcb);
    dcb.BaudRate = cfg->baud;
    dcb.ByteSize = 8;
    dcb.Parity   = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    SetCommState(puerto, &dcb);

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout         = 50;
    timeouts.ReadTotalTimeoutConstant    = 1000;
    timeouts.ReadTotalTimeoutMultiplier  = 10;
    SetCommTimeouts(puerto, &timeouts);

    printf("Puerto COM%d abierto a %d baudios.\n", cfg->com, cfg->baud);
    return puerto;
}