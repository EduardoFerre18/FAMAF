#include <stdio.h>
#include <stdbool.h>
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


bool todos_multiplos(int a[], int tam, int k) {

    int i = 0;

    while (i < tam) {

        if ((a[i] % a[k]) != 0) {
            return false;
        }

        i = i+1;

    }

return true;


}

int main (void) {

    int k;
    
    int a[N];

    pedirArreglo (a, N);

    printf ("Ingrese el valor de k\n");
    scanf ("%d", &k);

    assert ((k >= 0) && (k < N) && (a[k] != 0));

    int res = todos_multiplos (a, N, k);

    printf ("Los elementos del arreglos son multiplos de %d si devuelve (1) y sino devuelve (0): \n%d\n", a[k], res);

    return 0;

}
