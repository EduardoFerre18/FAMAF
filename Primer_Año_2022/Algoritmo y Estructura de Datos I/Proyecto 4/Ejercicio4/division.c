#include <stdio.h>
#include <assert.h>

struct div_t {

    int cociente;
    int resto;
};

struct div_t division(int x, int y) {

    struct div_t par;
    
    int q = 0;
    
    assert (y != 0);
    
    while (x >= y)  {
        x = x - y;
        q = q + 1; 
    }
    
    par.cociente = q;
    
    par.resto = x;
    
    return par;

}

int main (void){
    
    int dividendo;
    
    int divisor;
    
    printf("Introduzca el dividendo\n");
    scanf("%d", &dividendo);
    
    printf("Introduzca el divisor\n");
    scanf("%d", &divisor);
    
    if (divisor <= 0 || dividendo <=0) {
    
        printf("Error, ni el divisior ni el dividendo pueden ser negativos ni cero\n");
    
    }
    
    else {
    
        struct div_t resultado = division(dividendo, divisor);
    
        printf("El cociente es %d, el resto es %d\n", resultado.cociente, resultado.resto);
    
    }
    
    return 0;
    
}
