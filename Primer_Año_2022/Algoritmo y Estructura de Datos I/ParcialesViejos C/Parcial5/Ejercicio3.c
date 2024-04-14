#include <stdio.h>
#define N 4


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
int total_multiplo;
int total_no_multiplo;
};



struct sum_t suma_multiplo(int mul, int a[], int tam) {

    struct sum_t res;
    int i = 0;
    int suma_mult = 0;
    int suma_nmult = 0;

    while (i < tam) {

        if ((a[i] % mul) == 0) {

            suma_mult = suma_mult + a[i];
        }
        else {

            suma_nmult = suma_nmult + a[i];
        }

    i = i+1;

    }

    res.total_multiplo = suma_mult;
    res.total_no_multiplo = suma_nmult;

    return res;
}


int main (void) {

    struct sum_t resultado;
    
    int a[N], mul;

    pedirArreglo (a, N);

    printf ("Ingrese el numero del cual quiere calcular la suma de sus multiplos y no multiplos\n");
    scanf ("%d", &mul);

    resultado = suma_multiplo (mul, a, N);

    printf ("El resultado de la suma de los multiplos de %d es %d y la suma de los no multiplos de %d es %d", mul, resultado.total_multiplo, mul, resultado.total_no_multiplo);

    return 0;

}


