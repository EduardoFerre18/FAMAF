#include <stdio.h>
#include <stdbool.h> 
int main (void) {
    int x,y;
    printf("Ingrese un valor para x\n");
    scanf("%d" , &x);
    printf("Ingrese un valor para y\n");
    scanf("%d" , &y);
    x= x+y;
    printf("El valor de x es %d y el valor de y es %d\n", x, y+y);
    
    return 0;
    
}    
    
    
    /*
    |    programa    |usuario ingresa un σ0|produce una salida σ|
    |1.b ejecucion 1 |x→2, y→5             |x→7, y→10           |
    |1.b ejecucion 2 |x→5, y→10            |x→15, y→20          |
    |1.b ejecucion 3 |x→20, y→2            |x→22, y→4           | 
    
    */
