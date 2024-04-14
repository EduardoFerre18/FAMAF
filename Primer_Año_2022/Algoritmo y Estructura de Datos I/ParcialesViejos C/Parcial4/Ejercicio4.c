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


bool hay_asoc (int key, struct asoc_t a[], int tam) {

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
    
    int key;
    
    struct asoc_t a[N];

    pedirArreglo (a, N);

    printf ("Ingrese el valor de la key\n");
    scanf ("%d", &key);

    int res = hay_asoc (key, a, N);

    printf ("Si en el arreglo esta la clave key devuelve (1) y en caso de que no este devuelve (0): \n%d\n", res);

    return 0;


}