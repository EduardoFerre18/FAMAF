#include <stdio.h>
#include <limits.h>
#define N 4

int minimo_pares(int a[], int tam) {

    int minimo = INT_MAX;
    
    int i = 0;
    
    while(i < tam) {
    
        if((a[i] < minimo) && (a[i] % 2 == 0)) {
        
            minimo = a[i];
        }
        i = i + 1;
    }
    return minimo;
}

int minimo_impares(int a[], int tam) {

    int minimo = INT_MAX;
    
    int i = 0;
    
    while(i < tam) {
    
        if((a[i] < minimo) && (a[i] % 2 != 0)) {
        
            minimo = a[i];
        
        }
        
        i = i + 1;
    
    }
    
    return minimo;

}

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
        

int main (void) {

    int a[N];

    pedirArreglo(a, N);
    
    int minimo_par = minimo_pares (a, N);
    
    int minimo_impar = minimo_impares (a, N);

    if(minimo_par >= minimo_impar) {
    
        printf("El minimo es: %d\n", minimo_impar);
    
    }
    
    else {
    
        printf("El minimo es: %d\n", minimo_par);
    
    }
    return 0;
}
