#include <stdio.h>
#include <stdbool.h>

typedef struct _persona {
char *nombre;
int edad;
float altura;
float peso;
} persona_t;

float peso_promedio (persona_t arr[], unsigned int longitud) {

    float promedio_peso;
    float suma_peso = 0;
    unsigned int i = 0;

    while (i < longitud) {
        suma_peso = suma_peso + arr[i].peso;
        i = i+1;
    }    

    promedio_peso = suma_peso / longitud;

    return promedio_peso;

}

persona_t persona_de_mayor_edad(persona_t arr[], unsigned int longitud) {

    unsigned int i = 0;
    
    int mayor = -1000;
    
    persona_t mayor_edad;  

    while (i < longitud) {

            if (arr[i].edad > mayor) {
                mayor = arr[i].edad;
                mayor_edad = arr[i];
            }
            
            i = i+1;
    }
    return mayor_edad;
}

persona_t persona_de_menor_altura(persona_t arr[], unsigned int longitud) {

    unsigned int i = 0;
    
    float bajo = 1000;
    
    persona_t menor_altura;  

    while (i < longitud) {

            if (arr[i].altura < bajo) {
                bajo = arr[i].altura;
                menor_altura = arr[i];
            }
            i = i+1;
    }
    return menor_altura;
}

int main(void) {
    persona_t p1 = {"Paola", 21, 1.85, 75};
    
    persona_t p2 = {"Luis", 54, 1.75, 69};
    
    persona_t p3 = {"Julio", 40, 1.70, 80};
    
    unsigned int longitud = 3;
    
    persona_t arr[] = {p1, p2, p3};
    
    printf("El peso promedio es %f\n", peso_promedio(arr, longitud));
    
    persona_t p4 = persona_de_mayor_edad(arr, longitud);
    
    printf("El nombre de la persona con mayor edad es %s\n", p4.nombre);
    
    persona_t p5 = persona_de_menor_altura(arr, longitud);
    
    printf("El nombre de la persona con menor altura es %s\n", p5.nombre);
        
    return 0;
}



