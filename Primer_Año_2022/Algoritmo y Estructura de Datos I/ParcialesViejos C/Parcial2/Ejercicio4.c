#include <stdio.h>
#include <assert.h>

#define N 4

struct producto_t {
int codigo;
int cantidad;
};


void pedirArreglo(struct producto_t a[], int n_max) {

    int i  = 0;
    int cod = 0;
    int can = 0;
    struct producto_t prod;
    

    while (i<n_max) {
    
        printf("Introduzca el codigo en la posicion %d\n", i);
        scanf("%d", &cod);

        printf("Introduzca la cantidad en la posicion %d\n", i);
        scanf("%d", &can);

        prod.codigo = cod;
        prod.cantidad = can;
        
        a[i] = prod;
        
        i= i+1;
        
    }
    
}


struct stats_t {
float cantidad_media;
int cantidad_minima;
int cantidad_maxima;
};

struct stats_t calcular_estadisticas(struct producto_t a[], int tam) {

    int i = 1;
    float media = a[0].cantidad;
    int minima = a[0].cantidad;
    int maxima = a[0].cantidad;
    struct stats_t res;

    while (i < tam) {

        if (a[i].cantidad < minima) {
            minima = a[i].cantidad;
        }
        if (a[i].cantidad > maxima) {
            maxima = a[i].cantidad;
        }

        media = media + a[i].cantidad;
        i = i + 1;        
    }

    media = media / tam;

    res.cantidad_media = media;
    res.cantidad_minima = minima;
    res.cantidad_maxima = maxima;

    return res;


}


int main (void) {

    struct producto_t a[N];
    
    pedirArreglo (a, N);
    
    struct stats_t resultado;

    resultado = calcular_estadisticas (a, N);

    printf ("La cantidad media es %f, la cantidad maxima es %d y la cantidad minima es %d\n", resultado.cantidad_media, resultado.cantidad_maxima, resultado.cantidad_minima);

    return 0;


}