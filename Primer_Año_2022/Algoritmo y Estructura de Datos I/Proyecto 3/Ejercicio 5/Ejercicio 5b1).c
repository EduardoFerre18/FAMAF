#include <stdio.h>
#include <stdbool.h> 

int main (void) {
    int x,y,i;
    printf("Ingrese un valor para x\n");
    scanf("%d" , &x);
    printf("Ingrese un valor para y\n");
    scanf("%d" , &y);
    printf("Ingrese un valor para i\n");
    scanf("%d" , &i);
    i=0;

    while (x>=y) {
        x=x-y;
        i=i+1;
    }
    printf("El resultado es %d\n", i);
    return 0;
}
    
/*
(x→10 ,y→3 ,i→2 ) luego de iter. 1,
(x→7 ,y→3 ,i→3 ) luego de iter. 2,
(x→4 ,y→3 ,i→4 ) luego de iter. 3,
(x→1 ,y→3 ,i→4 ) luego de iter. 4,
Este programa calcula cuantas veces entra y en x, es decir el cociente de dividir x con y, siendo i el cociente de esta division.
*/
