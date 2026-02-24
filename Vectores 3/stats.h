#ifndef STATS_H
#define STATS_H
#include <stddef.h>
int max_int(const int *v, size_t n);
int min_int(const int *v, size_t n);
double media_int(const int *v, size_t n);

/* Normaliza en el propio vector:
v[i] = (v[i] - media) / desviacion
Si n==0 o desviacion==0, no hace nada.
*/

void normaliza(double *v, size_t n);
#endif