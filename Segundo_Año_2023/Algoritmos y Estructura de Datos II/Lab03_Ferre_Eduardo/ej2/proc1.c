#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y) {
    
    if (x >= 0) {
        y = x; 
    }
    
    else {
        y = -x;
    
    }
    
}

int main(void) {
   int a=0, res=0;
   a = -10;
   absolute(a, res);
   printf("El resultado es %d\n", res);
   
   
    return EXIT_SUCCESS;
}


//El valor que muestra por pantalla es 0. No coincide con el lenguaje del teorico-practico, porque este devuelve 10.
