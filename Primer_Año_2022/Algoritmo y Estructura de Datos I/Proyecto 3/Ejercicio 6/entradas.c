#include <stdio.h>
#include <stdbool.h> 

int pedirEntero (void) {
    int x;
    printf("Ingrese un entero \n");
    scanf("%d", &x);
    return x;
}

void imprimeEntero (int x) {
    printf("Usted ingreso %d\n", x);
}

int main (void) {
    imprimeEntero (pedirEntero());
    return 0;

}
