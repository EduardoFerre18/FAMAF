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
        
        
void imprimeArreglo(int a[], int n_max) {

    int i = 0;
    
    while (i < n_max) {
        
        printf("Elemento %d: %d\n", i, a[i]);
        
        i = i + 1;
    }

}



void intercambiar(int a[], int tam, int i, int j) {
    int aux;
    if ( (i < tam) && (j < tam)) {
        aux = a[i];
        a[i] = a[j];
        a[j] = aux;
        imprimeArreglo(a, tam);
    }
    else {
    printf ("Las posiciones no estan en el rango indicado\n");
    }
}

int main (void) {
    int i; 
    
    int j;

    int a[N];
    
    pedirArreglo(a, N);

    printf("Ingrese el valor de la posicion i\n");
    scanf("%d", &i);
    
    printf("Ingrese el valor de la posicion j\n");
    scanf("%d", &j);
    
    intercambiar (a, N, i, j);       
    return 0;
}







