#include <stdio.h>
#include "stats.h"
int main(void) {
    int a[] = {3, -1, 8, 8, 2};
    size_t n = sizeof(a)/sizeof(a[0]);

    printf("max=%d\n", max_int(a, n));
    printf("min=%d\n", min_int(a, n));
    printf("media=%.2f\n", media_int(a, n));

    double b[] = {1.0, 2.0, 3.0, 4.0};
    size_t m = sizeof(b)/sizeof(b[0]);

    normaliza(b, m);
    printf("normalizado: ");
    for (size_t i = 0; i < m; ++i) printf("%.3f ", b[i]);
    printf("\n");

    return 0;
}