#include <stdio.h>
int main(void) {
    int x = 5;
    int *p = &x;

    printf("x =      %d\n", x);
    printf("&x =      %p\n", (void*)&x);
    printf("p =      %p\n", (void*)p);
    printf("*p =      %d\n", *p);

    *p = 12;
    printf("x =      %d\n",x);
    return 0;
}
