#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "funciones.h"

int main(void) {
    Producto productos[24]; //cantidad de productos que hay en el programa.
    int i = 0;              // contador para escribir.
    int n = 0;
    int x=0;                  // x hace la verificación de que lo que entra al menú sea en el rango de 1 a 4, es la confirmación
    int salir2 = 0;
    int salir3 = 0;
    int salir=0;              // salir hace verificación de que salga
    char aux[64];               // auxiliar para leer en añadir
    float aux2;
    int escritura;
    int aux3;
    aux2= 0;
    aux3 = 0;
    salir = 0;
        while (!salir) {
            n=0;
            salir2 = 0;
            prompt_menu();
            while (!x) {
                leer_menu("Elija una opcion:  ", &n);
                if (n < 1 || n > 4) {
                    printf("Opcion no valida. Intentelo de nuevo. \n");
                    prompt_menu();
                }
                else x = 1;
            }
            switch (n) {
                case 1:
                    x=0;
                    n=0;
                    for (escritura = 0; escritura < i; escritura++) {
                        printf("%d: %s\n",escritura, productos[escritura].nombre);
                    }
                    break;
                case 2:
                    n=0;
                    x=0;
                        for (;!salir2;i++) {
                            leer_cadena("Introduzca el ID: ", aux, sizeof(aux));
                            productos[i].id = aux[0];
                            leer_cadena("Introduzca el nombre: ", aux, sizeof(aux));
                            strcpy(productos[i].nombre, aux);
                            leer_float("Introduzca el precio: ", &aux2);
                            productos[i].precio = aux2;
                            aux2 = 0;
                            leer_entero("Introduzca el stock: ", &aux3);
                            productos[i].stock = aux3;
                            aux3 = 0;
                            leer_cadena("Desea continuar anadiendo? Y/N: ",aux, sizeof(aux));
                            salir3 = 0;
                            while (!salir3) {
                                if (strcmp(aux, "Y") == 0 || strcmp(aux, "y") == 0) {
                                    salir2 = 0;
                                    salir3 = 1;
                                }
                                else if (strcmp(aux, "N") == 0 || strcmp(aux, "n") == 0) {
                                    salir2 = 1;
                                    salir3 = 1;
                                }
                                else {
                                    leer_cadena("Opcion no valida.\n Desea continuar anadiendo? Y/N: ",aux, sizeof(aux));
                                    salir3 = 0;
                                }
                            }
                        }
                    break;
                case 3:
                    x=0;
                    n=0;
                    printf("Modificar \n");
                    break;
                case 4:
                    n=0;
                    salir = 1;
            }
        }

        return 0;
}