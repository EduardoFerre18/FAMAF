#include <stdio.h>
#include <stdbool.h> 

void imprimeHola(void) {
    printf("Hola\n");
}

void imprimeChau(void) {
    printf("Chau\n");
}

int main () {
    imprimeHola();
    imprimeHola();
    imprimeChau();
    imprimeChau();
    return 0;
}