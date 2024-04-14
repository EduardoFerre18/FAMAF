#include <stdio.h>
#include <assert.h>

#define N 5

void pedirArreglo(int a[], int n_max) {

    int i;

    i = 0;

    int e;

    e = 0;

    while (i<n_max) {

        printf("Introduzca el elemento en la posicion %d\n", i);
        scanf("%d", &e);

        a[i] = e;

        i= i+1;

    }

}

struct paridad_t {
int n_pares;
int n_impares;
};

struct paridad_t contar_paridad (int a[], int tam) {

    struct paridad_t res;

    int pares = 0;

    int impares = 0;

    int i = 0;

    while (i < tam) {

        if ((a[i] % 2) == 0) {
            pares = pares + 1;
        }

        else {
            impares = impares + 1;
        }
        
    i = i + 1;        
    }

    res.n_pares = pares;
    res.n_impares = impares;

    return res;

}


int main (void){
    
    int a[N];
    
    pedirArreglo (a, N);

    struct paridad_t resultado;

    resultado = contar_paridad (a,N);

    printf ("Hay %d pares y %d impares\n", resultado.n_pares, resultado.n_impares);

    return 0;

}