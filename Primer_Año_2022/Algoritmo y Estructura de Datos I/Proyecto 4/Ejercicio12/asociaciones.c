#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#define N 4

typedef char clave_t;
typedef int valor_t;

struct asoc {
clave_t clave;
valor_t valor;
};

void pedirArreglo(struct asoc a[], int n_max) {

    int i = 0;

    struct asoc as; 
    
    clave_t e = ' ';
    
    valor_t v = 0;

    while (i<n_max) {
    
        printf("Introduzca la clave en la posicion %d\n", i);
        
        scanf( " %c", &e);

        printf("Introduzca el valor en la posicion %d\n", i);
        
        scanf("%d", &v);
        
        as.clave = e;
        as.valor = v;
        
        a[i] = as;
        
        i= i+1;
        
    }
}

bool asoc_existe (struct asoc a[], int tam, clave_t c){

    int i = 0;

    while (i < tam) { 
            
            if (a[i].clave == c) {
                return true;
            }

            i=i+1;
            

    }

    return false;
}

int main (void) {
    
    struct asoc a[N];
    
    clave_t c;

    int res;

    pedirArreglo(a, N);
    
    printf ("Ingrese la clave que desea ver si esta en el arreglo %c\n", c);
    scanf (" %c", &c);
    
    res = asoc_existe (a, N, c);
    
    printf ("La clave esta en el arreglo si devuelve (1) y sino (0): \n%d\n", res);
    return 0;
}