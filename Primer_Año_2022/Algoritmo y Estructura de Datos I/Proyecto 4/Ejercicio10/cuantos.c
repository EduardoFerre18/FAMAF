#include <stdio.h>
#include <limits.h>
#define N 4

void pedirArreglo(int a[], int n_max) {

    int i = 0;
    
    int e ;
    
    while (i<n_max) {
    
        printf("Introduzca el elemento en la posicion %d\n", i);
        
        scanf("%d", &e);
        
        a[i] = e;
        
        i= i+1;
        
    }
    
}

struct comp_t {
    int menores;
    int iguales;
    int mayores;
};


struct comp_t cuantos(int a[], int tam, int elem) {
    struct comp_t resultado;
    
    int i = 0;
    
    int menor = 0;
    
    int igual = 0;
    
    int mayor = 0;
    
    while (i < tam){
        
        if ( a[i] < elem ) {
        
            menor = menor + 1;
        }
        
        if ( a[i] == elem) {
            
            igual = igual + 1;
        }
        
        if ( a[i] > elem) {
            mayor = mayor + 1;
        }
        i = i+1;
    }

    resultado.menores = menor;
    resultado.iguales = igual;
    resultado.mayores = mayor;
    
    return resultado;

}
        
int main (void) {

    int a[N];
    
    int elem;
    
    struct comp_t resultado;

    pedirArreglo(a, N);
    
    printf("Ingrese el elemento\n");
    scanf("%d", &elem);
    
    resultado = cuantos(a, N, elem);
    
    printf("Hay %d menores, %d iguales y %d mayores\n", resultado.menores, resultado.iguales, resultado.mayores);
        
    return 0;
}
