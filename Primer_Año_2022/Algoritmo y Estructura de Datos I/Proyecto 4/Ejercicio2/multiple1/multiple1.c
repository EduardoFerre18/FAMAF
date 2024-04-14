#include <stdio.h>
#include <assert.h>

int main (void) {

    int x, y, aux;
    
    printf("Ingrese el valor de x\n");
    
    scanf("%d", &x);
    
    printf("Ingrese el valor de y\n");
    
    scanf("%d", &y);
    
    aux = x;
    
    x = x + 1;
    
    y = aux + y;
    
    printf("El valor de x es %d, el de y es %d\n", x, y);
    
    return 0;
    
}
