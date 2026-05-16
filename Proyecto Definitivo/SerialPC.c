#include <stdio.h>
#include "SerialPC.h"

HANDLE abrir_puerto(int num_puerto) {
    char nombre[20];
    sprintf(nombre, "\\\\.\\COM%d", num_puerto);

    HANDLE puerto = CreateFile(nombre,
        GENERIC_READ | GENERIC_WRITE,
        0, NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (puerto == INVALID_HANDLE_VALUE) {
        printf("Error: no se pudo abrir COM%d\n", num_puerto);
        return INVALID_HANDLE_VALUE;
    }

    // Configurar baudrate, bits, paridad
    DCB dcb = {0};
    dcb.DCBlength = sizeof(DCB);
    GetCommState(puerto, &dcb);
    dcb.BaudRate = CBR_9600;
    dcb.ByteSize = 8;
    dcb.Parity   = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    SetCommState(puerto, &dcb);

    // Timeout para no quedarse colgado esperando
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout         = 50;
    timeouts.ReadTotalTimeoutConstant    = 1000;
    timeouts.ReadTotalTimeoutMultiplier  = 10;
    SetCommTimeouts(puerto, &timeouts);

    printf("Puerto COM%d abierto correctamente\n", num_puerto);
    return puerto;
}

void cerrar_puerto(HANDLE puerto) {
    CloseHandle(puerto);
}

int enviar_datos(HANDLE puerto, int cant, int precio) {
    char buf[32];
    DWORD escritos;
    sprintf(buf, "%d;%d\n", cant, precio);
    WriteFile(puerto, buf, strlen(buf), &escritos, NULL);
    return escritos;
}

int recibir_total(HANDLE puerto) {
    char buf[32];
    DWORD leidos;
    int i = 0;
    char c;

    while (1) {
        ReadFile(puerto, &c, 1, &leidos, NULL);
        if (leidos == 0) {
            printf("Timeout: el STM32 no respondio\n");
            return -1;
        }
        if (c == '\n') break;
        if (i < 31) buf[i++] = c;
    }
    buf[i] = '\0';

    // Convertir string a int manualmente
    int total = 0;
    for (i = 0; buf[i] >= '0' && buf[i] <= '9'; i++) {
        total = total * 10 + (buf[i] - '0');
    }
    return total;
}
int enviar_moneda(HANDLE puerto, int moneda, int acumulado, int total) {
    char buf[32];
    DWORD escritos;
    sprintf(buf, "%d;%d;%d\n", moneda, acumulado, total);
    WriteFile(puerto, buf, strlen(buf), &escritos, NULL);
    return escritos;
}

void recibir_respuesta_monedero(HANDLE puerto, char *buf) {
    DWORD leidos;
    int i = 0;
    char c;
    while (1) {
        ReadFile(puerto, &c, 1, &leidos, NULL);
        if (leidos == 0 || c == '\n' || c == '\r') break;
        if (i < 63) buf[i++] = c;
    }
    buf[i] = '\0';
}
int comprobar_boton(HANDLE puerto) {
    char buf[32];
    DWORD escritos, leidos;
    char c;
    int i = 0;

    WriteFile(puerto, "0;0;0\n", 6, &escritos, NULL);

    while (1) {
        ReadFile(puerto, &c, 1, &leidos, NULL);
        if (leidos == 0 || c == '\n' || c == '\r') break;
        if (i < 31) buf[i++] = c;
    }
    buf[i] = '\0';

    if (strcmp(buf, "CANCEL") == 0) {
        // Enviar comando de apagado de LED
        WriteFile(puerto, "9;9;9\n", 6, &escritos, NULL);
        // Leer confirmación
        i = 0;
        while (1) {
            ReadFile(puerto, &c, 1, &leidos, NULL);
            if (leidos == 0 || c == '\n' || c == '\r') break;
        }
        return 1;
    }
    return 0;
}
void iniciar_monedero(HANDLE puerto) {
    DWORD escritos, leidos;
    char c;
    WriteFile(puerto, "8;8;8\n", 6, &escritos, NULL);
    // Leer confirmación
    while (1) {
        ReadFile(puerto, &c, 1, &leidos, NULL);
        if (leidos == 0 || c == '\n' || c == '\r') break;
    }
}