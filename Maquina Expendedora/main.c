#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funciones.h"

int main(void) {
    int n;
    typedef struct {
        int id;
        char nombre[32];
        float precio;
        int stock;
    } Producto;

    prompt_menu();

    leer_entero("Elija una opcion:  ", &n);
    while (n > 4) {
        printf("Opcion no valida. Intentelo de nuevo.\n");
        prompt_menu();
        leer_entero("Elija una opcion:  ", &n);
    }
    switch (n) {
        case 1:

            break;

        case 2:
            char entrada[30]
            leer_cadena("Introduzca el ID: ", &n);


            break;

        case 3:

            break;

        case 4:

            break;
    }

}
