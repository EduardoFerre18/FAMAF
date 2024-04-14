#include <stdio.h>
#include <stdbool.h> 

int main (void) {
    int i;
    printf("Ingrese un valor para i\n");
    scanf("%d" , &i);
    while (i!=0){
        i=i-1;
    }

    printf("El resultado es %d\n", i);
    return 0;

}