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

struct cantidad_t {
int n_multiplos_dos;
int n_multiplos_tres;
};

struct cantidad_t contar_multiplos(int a[], int tam) {

    struct cantidad_t res;
    int i = 0;
    int mult_2 = 0;
    int mult_3 = 0;

    while (i < tam) {

        if ((a[i] % 2) == 0) {
            mult_2 = mult_2 + 1;
        }
        if ((a[i] % 3) == 0) {
            mult_3 = mult_3 + 1;
        }

        i = i+1;

    }

    res.n_multiplos_dos = mult_2;
    res.n_multiplos_tres = mult_3;

    return res;


}


int main (void) {

    int a[N];
    pedirArreglo (a, N);
    struct cantidad_t resultado;

    resultado = contar_multiplos (a, N);

    printf ("Hay %d multiplos de 2 y %d multiplos de 3\n", resultado.n_multiplos_dos, resultado.n_multiplos_tres);

    return 0;


}
