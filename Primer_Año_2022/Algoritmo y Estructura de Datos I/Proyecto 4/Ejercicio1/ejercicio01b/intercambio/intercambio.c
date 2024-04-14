#include <stdio.h>
#include <assert.h>

int main (void) {

    int A, B, x, y, z;
    
    printf("Ingrese el valor de x\n");
    
    scanf("%d", &A);
    
        
    printf("Ingrese el valor de y\n");
    
    scanf("%d", &B);
    
    x = A;
    
    y = B;
    
    z = x;
    
    x = y;
    
    y = z;
    
    assert (x == B && y ==A);
    
    printf("La variable x tiene el valor %d\n", x);
    
    printf("La variable y tiene el valor %d\n", y);
    
    return 0;
    
}
