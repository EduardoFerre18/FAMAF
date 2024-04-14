#include <stdio.h>
#include <stdbool.h> 
int main (void) {
    int x, y, z;
    printf("Ingrese un valor para x\n");
        scanf("%d" , &x);
        printf("Ingrese un valor para y\n");
        scanf("%d" , &y);
        printf("Ingrese un valor para z\n");
        scanf("%d" , &z);

    printf("Usted ingreso x=%d, y=%d, z=%d; entonces x+y+1=%d\n", x, y, z, x+y+1);
    printf("Usted ingreso x=%d, y=%d, z=%d; entonces z*z+y*45-15*x=%d\n", x, y, z, z*z+y*45-15*x);
    printf("Usted ingreso x=%d, y=%d, z=%d; entonces y-2==(x * 3 + 1)%5=%d\n", x, y, z, y-2==(x * 3 + 1)%5);
    printf("Usted ingreso x=%d, y=%d, z=%d; entonces y/ 2*x=%d\n", x, y, z, y/ (2*x));
    printf("Usted ingreso x=%d, y=%d, z=%d; entonces y<x*z=%d\n", x, y, z, y< (x*z));   
        
return 0;
}

/*
Si ingresamos: (x→7, y→3, z→5) tenemos:
x+y+1=11
z*z+y*45-15*x= 55
y-2==(x * 3 + 1)%5= 0
y/ 2*x= 0
y<x*z= 1

Si ingresamos: (x→1, y→10, z→8) tenemos:
x+y+1=11
z*z+y*45-15*x= 55
y-2==(x * 3 + 1)%5= 0
y/ 2*x= 0
y<x*z= 1


En la ultimna expresion el resultado es un tipo Bool, pero en el lenguaje "C", no tenemos los tipos Bool, en todo caso el 0 esta definido como el False y cualquier numero distinto de 0 es True.

*/