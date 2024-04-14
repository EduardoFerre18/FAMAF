#include <stdio.h>
#include <assert.h>

int main (void) {

    int x, y, z, aux_x, aux_y;

    printf("Ingrese el valor de x\n");
    scanf("%d", &x);
    
    printf("Ingrese el valor de y\n");
    scanf("%d", &y);
    
    printf("Ingrese el valor de z\n");
    scanf("%d", &z);
    
    aux_x = x;
    
    aux_y = y;
    
    x = y;
    
    y = y + aux_x + z;
    
    z = aux_y + aux_x;
    
    printf("El valor de x es %d, el de y es %d y el de z es %d\n", x, y, z);
    
    return 0;
    
}
