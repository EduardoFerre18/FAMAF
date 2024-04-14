#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int *y) {
 
    if (x < 0){
    
        *y = -x;
    }
}

int main(void) {
    int a=0, res=0;  // No modificar esta declaración
    
    a = -10;
    
    absolute(a, &res);
    
    printf("El resultado es %d\n", res);
    
    return EXIT_SUCCESS;
}

//El parametro *y de absolute() es de tipo in porque estamos leyendo esa direccion de memoria y no la estamos modificando

//Es posible implementar todos esos tipos de parametro en funciones de C

