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

int suma_mayores (int a[], int tam, int k) {

    int i = 0;
    int res = 0;

    while (i < tam) {

        if (a[i] > a[k]) {

            res = res + a[i];
        }
        
        i = i+1;

    }

    return res;

}


int main (void) {
    
    int a[N];

    int k;
    
    pedirArreglo (a, N);

    printf ("Ingrese el valor de k\n");
    scanf ("%d", &k);

    assert ((k >= 0) && (k < N));

    printf ("El resultado de la suma es %d", suma_mayores (a, N, k));

    return 0;

}