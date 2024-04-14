#include <stdio.h>
#include <assert.h>

int main (void) {

    int x, y, aux_x;

    printf ("Ingrese el valor de x\n");
    scanf ("%d", &x);

    printf ("Ingrese el valor de y\n");
    scanf ("%d", &y);

    int X = x;

    int Y = y;

    assert ((x == X) && (y == Y) && (X * Y != 0));

    aux_x = x;

    x = y * x;

    y = aux_x * y;

    assert ((x == X * Y) && (x == y));

    printf ("El valor de x es %d y el valor de y es %d\n", x, y);

    return 0;
}