#include <stdio.h>

void pedirArreglo(int a[], int n_max) {
    int i = 0;
    
    int e;
    
    while (i<n_max) {
    
        printf("Introduzca el elemento en la posicion %d\n", i);
        
        scanf("%d", &e);
        
        a[i] = e;
        
        i= i+1;
        
    }
    
}
        
        
void imprimeArreglo(int a[], int n_max) {
    int i = 0;

    while (i < n_max) {
        
        printf("Elemento %d: %d\n", i, a[i]);
        
        i = i + 1;
    }

}


int main (void) {
    
    int n_max;
    
    printf("Ingrese el tamaño del arreglo\n");
    
    scanf("%d", &n_max);
    
    int a[n_max];
    
    pedirArreglo(a, n_max);
    
    imprimeArreglo(a, n_max);
    
    return 0;
}
    
