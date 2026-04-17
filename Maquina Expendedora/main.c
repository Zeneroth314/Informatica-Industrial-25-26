#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funciones.h"

int main(void) {
    int n;
    int x;
    int salir;
    x=0;
    salir = 0;
    prompt_menu();
        while (!x) {
            leer_menu("Elija una opcion:  ", &n);
            if (n < 1 || n > 4) {
                printf("Opcion no valida. Intentelo de nuevo. \n");
                prompt_menu();
            }
            else x = 1;
        }
        while (!salir) {
            switch (n) {
                case 1:
                    x=0;
                    n=0;
                    printf("Listar \n");
                    prompt_menu();
                    while (!x) {
                        leer_menu("Elija una opcion:  ", &n);
                        if (n < 1 || n > 4) {
                            printf("Opcion no valida. Intentelo de nuevo. \n");
                            prompt_menu();

                        }
                        else x = 1;
                    }
                    break;
                case 2:
                    n=0;
                    x=0;
                    printf("Anadir \n");
                    prompt_menu();
                    while (!x) {
                        leer_menu("Elija una opcion:  ", &n);
                        if (n < 1 || n > 4) {
                            printf("Opcion no valida. Intentelo de nuevo. \n");
                            prompt_menu();

                        }
                        else x = 1;
                    }
                    break;
                case 3:
                    x=0;
                    n=0;
                    printf("Modificar \n");
                    while (!x) {
                        prompt_menu();
                        leer_menu("Elija una opcion:  ", &n);
                        if (n < 1 || n > 4) {
                            printf("Opcion no valida. Intentelo de nuevo. \n");
                            prompt_menu();

                        }
                        else x = 1;
                    }
                    break;
                case 4:
                    n=0;
                    salir = 1;
            }
        }

        return 0;
}