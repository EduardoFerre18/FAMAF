#include <stdio.h>
#include <stdbool.h> 

int main (void) {
    int x,i,res;
    printf("Ingrese un valor para x\n");
    scanf("%d" , &x);
    printf("Ingrese un valor para i\n");
    scanf("%d" , &i);
    printf("Ingrese un valor para res\n");
    scanf("%d" , &res);
    i=2;
    res= true;
    while ((i<x) && res) {
        res = (res) && ((x%i)!=0 );
        i=i+1;
    }
    printf("El resultado final es %d\n", res);
    return 0;
        
}

/*
(x→5 ,i→3 ,res→True ),luego de iter. 1
(x→5 ,i→4 ,res→True ),luego de iter. 2
(x→5 ,i→5 ,res→True ),luego de iter. 3
Lo que este programa hace es  decirme si el valor que ingreso a x es un numero primo.
*/