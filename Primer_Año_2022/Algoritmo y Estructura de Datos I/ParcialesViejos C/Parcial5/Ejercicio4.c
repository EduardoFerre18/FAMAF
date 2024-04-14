#include <stdio.h>
#include <stdbool.h>
#define N 4


struct asoc_t {
int clave;
int valor;
};

void pedirArreglo(struct asoc_t a[], int n_max) {


    int i = 0;
    
    int clav, val;
    
    while (i<n_max) {
    
        printf("Introduzca la clave en la posicion %d\n", i);
        scanf("%d", &clav);

        printf("Introduzca el valor en la posicion %d\n", i);
        scanf("%d", &val);

        a[i].clave = clav;
        a[i].valor = val;
        
        i= i+1;
        
    }
    
}

bool hay_asoc(int key, struct asoc_t a[], int tam) {

    int i = 0;
    
    while (i < tam) {
        if (a[i].clave == key) {
            return true;
        } 
        i = i+1;
    }

    return false;
}

int main (void) {

    int res, key;
    struct asoc_t a[N];
    pedirArreglo (a, N);
    printf ("Ingrese la clave que desea saber si esta en el arreglo\n");
    scanf ("%d", &key);

    res =  hay_asoc (key, a, N);

    printf ("Si la clave esta en el arreglo devuelve (1) y si no esta (0) \n%d\n", res);

}