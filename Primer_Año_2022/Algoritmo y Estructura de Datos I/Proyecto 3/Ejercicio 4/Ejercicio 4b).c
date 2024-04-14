#include <stdio.h>
#include <stdbool.h> 
int main (void)
    {
        int x,y,z,m;
        printf("Ingrese un valor para x\n");
        scanf("%d" , &x);
        printf("Ingrese un valor para y\n");
        scanf("%d" , &y);
        printf("Ingrese un valor para z\n");
        scanf("%d" , &z);
        printf("Ingrese un valor para m\n");
        scanf("%d" , &m);

        if (x<y) {
            m=x;
        }
        else {
            m=y;
        }
        if (m<z) {}
        else {
            m=z;
        }
        printf("Entonces el valor de x es %d, de y es %d, de z es %d y de m es %d \n", x, y, z, m);

        return 0;

    }


/*

Los estados finalmente quedan:
[|σ0 : (x→ 5 ,y→ 4 ,z→ 8 ,m→ 0 ) |]
[|σ1 : (x→ 5 ,y→ 4 ,z→ 8 ,m→ 4 ) |]
[|σ2 : (x→ 5 ,y→ 4 ,z→ 8 ,m→ 4 ) |]

El programa dados 3 enteros, calcula el minimo de ellos y lo guarda en la variable m.
Es decir m es el minimo numero de los 3 enteros.



*/