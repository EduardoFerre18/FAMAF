#include <stdio.h>
#include <assert.h>

int main (void) {

    int s;

    int r;

    int aux;

    printf ("Ingrese el valor de s\n");
    scanf("%d", &s);

    printf ("Ingrese el valor de r\n");
    scanf("%d", &r);

    int S = s;

    int R = r;

    assert ((r == R) && (s == S) && (S > R));

    aux = s;

    s = 2 * r - 2 * s;

    r = 2 * r + aux;

    assert ((s == 2 * R - 2 * S) && (r = 2 * R + S) );
    
    printf ("El valor de s es %d y el valor de r es %d",s, r);

    return 0;



}

/*
s = 4 y r = 2

s = 2 * 2 - 2 * 4 = -4

r = 2 * 2 + 4 = 8


*/