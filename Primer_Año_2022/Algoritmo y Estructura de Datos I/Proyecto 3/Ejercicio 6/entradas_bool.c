#include <stdbool.h> 
#include <stdio.h>

bool pedirBooleano(void) {
    int temp;
    bool x;
    printf("Ingrese el valor de su booleano \n");
    scanf("%d", &temp);
    x=temp;
    
    return x;
}

void imprimeBooleano(bool x) {
    if (x==false) {
        printf("Usted ingreso False\n");
    }
    else {
        printf("Usted ingreso True\n");
    }
}

int main (void) {
    imprimeBooleano (pedirBooleano());
    return 0;
}