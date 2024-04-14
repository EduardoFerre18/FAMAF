#include <stdio.h>
#include <stdbool.h>

int pedirEntero (void)
    {
        int x;
        
        printf("Ingrese un entero \n");
        
        scanf("%d", &x);

        return x;
    }

bool esPrimo (int x) {
    int i = 2;
    bool res = true;

    while ((i < x) && res) {
            res = res && ((x % i) != 0);
            i = i+1;

    }

    return res;

}

int nesimo_primo(int N) {
    int i = 1;

    int x = 2;

    while (i < N) {
        x = x+1;
        if (esPrimo(x)) {
            i=i+1;
        }
        
    }

    return x;
}


int main (void) {

    int x = pedirEntero();

    while (x < 0) {
        printf ("Usted ingreso un entero negativo, ingrese uno positivo\n");
    
        x=pedirEntero();
    }

    int resultado = nesimo_primo (x);
    printf("el n-esimo primo es %d", resultado);

    return 0; 
}