#include <stdio.h>
#include <stdbool.h> 
int main (void) {
    int x;
    printf("Ingrese un valor para x\n");
    scanf("%d" , &x);
    x=5;
    printf("El valor de x es %d", x);
    return 0;

}


/*
|    programa    |usuario ingresa un σ0|produce una salida σ|
|1.a ejecucion 1 |(x→ 1)               |(x→ 5)              |
|1.a ejecucion 2 |(x→ 7)               |(x→ 5)              |
|1.a ejecucion 3 |(x→ 4935)            |(x→ 5)              | 


*/