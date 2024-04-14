#include <stdio.h>
#include <stdbool.h> 

int main (void) {
    int x,y;
    printf("Ingrese un valor para x\n");
    scanf("%d" , &x);
    printf("Ingrese un valor para y\n");
    scanf("%d" , &y);
    if (x>=y) {
        x=0;
    }
    else {
        x=2;
    }
    printf("El resultado de x es %d y el resultado de y es %d\n", x, y);
        
    return 0;

}
