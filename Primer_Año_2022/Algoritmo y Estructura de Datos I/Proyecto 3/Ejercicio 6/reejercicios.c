#include <stdio.h>
#include <stdbool.h> 
int pedirEntero (void)
    {
        int x;
        printf("Ingrese un entero\n");
        scanf("%d", &x);

        return x;
    }


void imprimeEntero (int x)
    {
        printf("Usted ingreso %d\n", x);
    }


int div (int x, int y, int i)
    {
        i= 0;
        while (x>=y){
            x=x-y;
            i=i+1;
        }
        
    return x,y,i;

    }

int es_primo (int x, int y, int i)
    {
        y=2;
        i= true;
        while ((y<x) && i) {
            i= (i) && ((x%y)!=0 );
            y=y+1;
        }

            return x,y,i;
        
    
    }

int main ()
    {
        int x = pedirEntero();
        int y = pedirEntero();
        int i = pedirEntero();        
        printf("El resultado es %d\n",es_primo (x, y, i) ); 
    
        return 0;
    
    }