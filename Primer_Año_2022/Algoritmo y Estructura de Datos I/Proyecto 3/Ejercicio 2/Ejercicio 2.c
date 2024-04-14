#include <stdio.h>
#include <stdbool.h>
int main (void) {
    int x,y,z,b,w;
    printf("Ingrese un valor para x\n");
    scanf("%d" , &x);
    printf("Ingrese un valor para y\n");
    scanf("%d" , &y);
    printf("Ingrese un valor para z\n");
    scanf("%d" , &z);
    printf("Ingrese un valor para b\n");
    scanf("%d" , &b);
    printf("Ingrese un valor para w\n");
    scanf("%d" , &w);

    printf("Usted ingreso x=%d, y=%d, z=%d, b=%d, w=%d; entonces x%4 == 0=%d\n", x, y, z, b, w, x%4 == 0);
    printf("Usted ingreso x=%d, y=%d, z=%d, b=%d, w=%d; entonces x+y == 0 && y-x == (-1)*z=%d\n", x, y, z, b, w, ((x+y) == 0) && ((y-x) == ((-1)*z)) );
    printf("Usted ingreso x=%d, y=%d, z=%d, b=%d, w=%d; entonces ! b && w=%d\n", x, y, z, b, w, !b && w);

return 0;

}


/*
Los valores de las variables son:
x→4, y→-4, z→8, b→1, w→0
*/