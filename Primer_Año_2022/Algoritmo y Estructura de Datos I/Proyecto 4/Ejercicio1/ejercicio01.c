#include <stdio.h>
#include <assert.h>

void holaHasta(int n) {
    int i = 0;
    
    while (i<n) {
        printf("Hola\n");
        i=i+1;           
    }
    
}

int pedirEntero(void){
    int n;
    
    printf("Ingrese cuantas veces desea imprimir Hola \n");
    scanf("%d", &n);
    
    return n;
}

int main (void) {
    int n = pedirEntero();
    
    assert (n>0);

    holaHasta (n);
    
    return 0;
    
}
