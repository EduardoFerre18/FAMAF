#include <stdio.h>
#include <assert.h>
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

struct sum_t {
int inferior;
int superior;
};


struct sum_t suma_acotada(int cota, int array[], int tam) {

    struct sum_t res;
    
    int i = 0;

    int inf = 0;

    int sup = 0;

    while ( i < tam) {

        if ( array[i] < cota) {
            inf = inf + array[i];
        }

        if ( array[i] >= cota) {
            sup = sup + array[i];
        }

    i= i + 1;

    }

    res.inferior = inf;
    res.superior = sup;

    return res;
}

int main (void) {

    struct sum_t resultado;
    
    int array[N], cota;

    pedirArreglo (array, N);

    printf ("Ingrese el valor de la cota\n");
    scanf ("%d", &cota);

    resultado = suma_acotada (cota, array, N);

    printf ("El resultado de los elementos menores a %d es %d y la suma de los elementos mayores o iguales a %d es %d\n", cota, resultado.inferior, cota, resultado.superior);

    return 0;

}