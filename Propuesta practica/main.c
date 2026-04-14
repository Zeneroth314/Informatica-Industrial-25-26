#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funciones.h"

int main(void) {
    int n;
    int edad;
    float altura;
    char nombre[125];

    prompt_menu();

    leer_entero("Elija una opcion:  ", &n);
        while (n > 3) {
            printf("Opcion no valida. Intentelo de nuevo.\n");
            prompt_menu();
            leer_entero("Elija una opcion:  ", &n);
        }
    switch (n) {
        case 1: leer_entero("Introduzca su edad:  ", &edad);
            printf("Su edad es: %d.\n", edad);
            break;

        case 2: leer_float("Introduzca su altura (m):  ", &altura);
            printf("Su altura es: %f.\n", altura);
            break;

        case 3: leer_cadena("Introduzca su nombre: ", &nombre, sizeof(nombre));
            printf("Su nombre es: %s.\n", nombre);
            break;
    }

}
