#include <stdio.h>
#include <stdbool.h> 

int pedirEntero (void) {
    int x;
    printf("Ingrese un entero\n");
    scanf("%d", &x);

    return x;
}

void imprimeEntero (int x) {
    printf("Usted ingreso %d\n", x);
}

int min (int x, int y, int z, int m) {
    
    if (x<y) {
        m=x;
    }
    else {
        m=y;
    }
    if (m<z) {}
    else {
        m=z;
    };
    return x,y,z,m;

}

int main () {
    int x = pedirEntero();
    int y = pedirEntero();
    int z = pedirEntero();
    int m = pedirEntero();

    printf("El resultado es %d\n",min (x, y, z, m) ); 
    return 0;
    
}

/*
En esta nueva version, el codigo de la funcion main queda mucho mas corto y legible. Luego, escribiendo la funcion min (que es lo que hace el programa en si), acorta todavia mas el codigo de la funcion main.

Se pueden reescribir varios programas usando mas funciones. Como el del la division de dos enteros, o saber si un numero es primo o no.

*/


