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

struct s_suma_t {
int suma_pares;
int suma_impares;
int suma_total;
};

struct s_suma_t sumas(int a[], int tam) {

    int i = 0;

    struct s_suma_t res;

    int sum_pares = 0;

    int sum_impares = 0;

    int sum_total = 0;

    while (i < tam) {

        if ((a[i] % 2) == 0) {
            sum_pares = sum_pares + a[i];
        }

        if ((a[i] % 2) != 0) {
            sum_impares = sum_impares + a[i];
        }

        i = i + 1;
    }

    sum_total = sum_pares + sum_impares;

    res.suma_pares = sum_pares;
    res.suma_impares = sum_impares;
    res.suma_total = sum_total;

    return res;

}

int main (void) {

    struct s_suma_t resultado;    
    
    int a[N];

    pedirArreglo (a, N);

    resultado = sumas (a, N);

    printf ("El resultado de las sumas pares es %d, de las sumas impares es %d y la suma total es %d\n", resultado.suma_pares, resultado.suma_impares, resultado.suma_total);

    return 0;

}