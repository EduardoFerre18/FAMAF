#include <stdio.h>
#include <assert.h>

int main (void) {

    int r; 
    
    int s;
    
    int aux;

    printf ("Ingrese el valor de r\n");
    scanf ("%d", &r);

    printf ("Ingrese el valor de s\n");
    scanf ("%d", &s);

    int R = r;

    int S = s;

    assert ((r == R) && (s == S) && (S > R ));

    aux = r;

    r = s - r;

    s = aux + s;

    assert ((r == S - R) && (s == R + S ));

    printf ("El valor de r es %d y el valor de s es %d", r,s);

    return 0;

}

