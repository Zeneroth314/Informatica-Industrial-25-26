#include <stdio.h>

#include "funciones.h"

int main(void) {
    int n;
    leer_entero("Edad: ", &n);
    printf("El valor es: %d",n);
}
