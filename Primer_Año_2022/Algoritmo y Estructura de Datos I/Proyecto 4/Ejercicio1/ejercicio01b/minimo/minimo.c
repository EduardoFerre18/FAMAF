#include <stdio.h>
#include <assert.h>

int minimo (int x, int y) {
    int m;
    
    if (x <= y) {
        m = x;
    }
    
    else {
        m = y;
    }
    
    return m;

}

int main (void) {
    int x, y, m;
    
    printf("Ingrese el valor de x\n");
    
    scanf("%d", &x);
    
    printf("Ingrese el valor de y\n");
    
    scanf("%d", &y);
    
    m = minimo(x, y);
    
    assert ((m == x && x <= y) || (m == y && y <= x));
    
    printf("El minimo entre x e y es %d\n", m);

    return 0;

}
