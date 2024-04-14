#include <stdio.h>
#include <assert.h>

int main (void) {
    
    int x, y, z, aux_x, aux_y;

    printf ("Ingrese el valor de x\n");
    scanf ("%d", &x);

    printf ("Ingrese el valor de y\n");
    scanf ("%d", &y);

    printf ("Ingrese el valor de z\n");
    scanf ("%d", &z);

    int X = x;
    int Y = y;
    int Z = z;

    assert ((x == X) && (y == Y) && (z == Z) && (Y > X) && (X > 0));

    aux_x = x;

    aux_y = y;

    x = aux_y;

    y = z;

    z = (aux_x / aux_y) + (aux_x % aux_y);

    assert ((x == Y ) && (y == Z) && (z == X));

    printf ("El valor de x es %d, el valor de y es %d y el valor de z es %d\n", x, y, z);

    return 0;

}