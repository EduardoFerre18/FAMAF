#include <stdio.h>
#define N 5

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
        
int sumatoria(int a[], int tam) {
    int i = 0;
    
    int res = 0;
    
    while (i < tam) {
    
        res = res + a[i];
        i = i + 1;
    }
    return res;
}

int main (void) { 
    int a[N];
    pedirArreglo(a, N);
    printf("El resultado de la sumatoria es %d\n", sumatoria (a, N));
    return 0;
}
    
