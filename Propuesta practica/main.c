#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funciones.h"

int main(void) {
    int n;
    int edad;
    float altura;
    int nombre;

    printf("========== MENU ==========\n");
    printf("1: Introducir edad.\n");
    printf("2: Introducir altura (m).\n");
    printf("3: Introducir nombre.\n");

    leer_entero("Elija una opción:  ", &n);
        while (n > 3 && n < 1) {
            printf("Opción inválida\n");
            printf("========== MENU ==========\n");
            printf("1: Introducir edad.\n");
            printf("2: Introducir altura (m).\n");
            printf("3: Introducir nombre.\n");
            leer_entero("Elija una opción:  ", &n);
        }
    switch (n) {
        case 1: leer_entero("Introduzca su edad:  ", &edad);
            printf("Su edad es: %d.\n", edad);

        case 2: leer_float("Introduzca su altura (m):  ", &altura);
            printf("Su altura es: %f.\n", edad);

        //case 3: leer_cadena("Introuzca su nombre: \n", &nombre);//
    }

}
