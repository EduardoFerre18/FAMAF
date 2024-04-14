#include <stdio.h>
#include <assert.h>

int absoluto (int x){
    if (x>=0){
        x = x;
    }
    else {
    x = -x;       
    }
    return x;
}

int main (void) {
    int x, m;

    printf("Ingrese el valor de x\n");
    scanf("%d", &x);
    
    m = absoluto(x);
    
    assert (((m==x)&&(x>=0))||((m==-x)&&(x<0)));
    
    printf("El valor absoluto de %d es %d\n", x, m);
    
    return 0;
}


/*

Para compilar un archivo .c escribir en la terminal:
$> gcc -Wall -Wextra -std=c99 miarchivo.c -o miprograma
Para ejecutar escribir:
$> ./miprograma
Para compilar para gdb se debe agregar el flag -g al momento de compilar .c escribir en la
terminal:
$> gcc -Wall -Wextra -std=c99 -g miarchivo.c -o miprograma


*/