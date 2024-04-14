#include <stdio.h>

#define N 4

struct persona_t {
int dni;
float altura;
};

void pedirArreglo(struct persona_t a[], int n_max) {

    int i;
    
    i = 0;
    
    struct persona_t persona; 
    
    int docni = 0;
    
    float alt = 0;

    while (i<n_max) {
    
        printf("Introduzca el dni en la posicion %d\n", i);
        
        scanf( " %d", &docni);

        printf("Introduzca la altura en la posicion %d\n", i);
        
        scanf("%f", &alt);
        
        persona.dni = docni;
        persona.altura = alt;
        
        a[i] = persona;
        
        i= i+1;
        
    }
}

struct stats_t {
float altura_media;
float altura_minima;
float altura_maxima;
};


struct stats_t calcular_estadisticas(struct persona_t a[], int tam) {

    struct stats_t res;

    int i = 1;

    float promedio = a[0].altura;

    float minima = a[0].altura;

    float maxima = a[0].altura;

    while (i < tam) {
        if (a[i].altura < minima ) {
            minima = a[i].altura;
            

        }
        else if (a[i].altura > maxima ) {
            maxima = a[i].altura;
            
        }

    promedio = promedio + a[i].altura;
    i = i+1;
    }

    promedio = promedio / tam;

    res.altura_media = promedio;
    res.altura_minima = minima;
    res.altura_maxima = maxima;

    return res;

}


int main (void) {

    struct persona_t a[N];

    pedirArreglo (a, N);

    struct stats_t resultado;

    resultado = calcular_estadisticas (a, N);

    printf("La altura promedio es %f, la altura maxima es %f y la altura minima es %f\n", resultado.altura_media, resultado.altura_maxima, resultado.altura_minima );

    return 0;


}
