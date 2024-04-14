#include <stdio.h>

int suma_hasta(int N){
    int r = (N*(N+1))/2;
    
    return r;
}

int main (void){
    int N;
    
    printf("Ingrese hasta donde desea sumar\n");
    scanf("%d", &N);
    
    if (N>=0) {
        printf("La sumatoria hasta %d es %d\n", N, suma_hasta (N));
    }
    
    else {
    printf("Error el numero es negativo\n");
    }
    
    return 0;
}        
