#include <stdio.h>
#include <limits.h>
#define N 4

void pedirArreglo(float a[], int n_max) {

    int i = 0;
    
    float e;
    
    while (i<n_max) {
    
        printf("Introduzca el elemento en la posicion %d\n", i);
        
        scanf("%f", &e);
        
        a[i] = e;
        
        i= i+1;
        
    }

}

struct datos_t {
float maximo;
float minimo;
float promedio;
};

struct datos_t stats(float a[], int tam) {

    struct datos_t resultado;
    
    int i = 1;
    
    float max = a[0];
    
    float min = a[0];
    
    float prom = a[0];

    while (i< tam) {

        if (a[i] < min ) {

            min = a[i];
        }

        if (a[i] > max) {

            max = a[i];
        }

        prom = prom + a[i];
        
        i = i+1;
    }
    
    prom = prom / tam;

    resultado.minimo  = min;
    resultado.maximo =  max;
    resultado.promedio = prom;

    return resultado;

}

int main (void) {
    
    float a[N];
    
    struct datos_t resultado;

    pedirArreglo(a, N);   
    
    resultado = stats (a, N);
    
    printf ("El minimo del arreglo es %f, el maximo es %f y el promedio es %f", resultado.minimo, resultado.maximo, resultado.promedio);
    
    return 0;
}
