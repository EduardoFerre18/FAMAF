#include <stdio.h>
#include <stdbool.h>
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

bool existe_positivo(int a[], int tam) {

    int i = 0;
    
    while (i < tam) {
    
        if (a[i] > 0) {
        
            return true;
        
        }
        
        i = i + 1;
        
    }
    
    return false;

}

bool todos_positivos(int a[], int tam) {

    int i = 0;
    
    while (i < tam) {
    
        if (a[i] <= 0) {
        return false;
        
        }
    i = i + 1;
    }
    return true;

}
        
int main (void) {

    bool resultado;
    
    int resultado2;
    
    int eleccion;
    
    int a[N];
    
    pedirArreglo(a, N);
    
    printf("Seleccione funcion: existe positivo (ingrese 0), todos positivos (ingrese un numero distinto de 0)\n");
    
    scanf("%d", &eleccion);
    
    if(eleccion == 0) {
        
        resultado = existe_positivo(a, N);
    }
    
    else {
    
        resultado = todos_positivos(a, N);
    
    }
    resultado2 = resultado;
    
    printf("El resultado es: %d\n", resultado2);
    
    return 0;
}
