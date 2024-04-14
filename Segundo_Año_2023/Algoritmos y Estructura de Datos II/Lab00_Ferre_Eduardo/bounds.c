#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

void pedirArreglo (int a[], int n) {

    int i = 0;
    
    int e;
    
    while (i < n) {
    
        printf ("Ingrese el elemento en la posicion %d\n", i);
        
        scanf("%d", &e);
        
        a[i]= e;
        
        i = i+1;
        
        
    }
}


struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length) {

    struct bound_data res;
    
    res.is_upperbound = true;
    
    res.is_lowerbound = true;
    
    res.exists = false;
    
    res.where = length + 1;
    
    int i;
    
    for (i =0; i < length; i++){
    
        if (value < arr[i]) {
        
            res.is_upperbound = false;
        
        }
        
        if (value > arr[i]) {
        
            res.is_lowerbound = false;
        
        }
        
        if (value == arr[i] && res.exists == false){
        
            res.exists = true;
            
            res.where = i;
        
        }
    
    }
   
    return res;
}

int main(void) {

    //int a[ARRAY_SIZE] = {0, -1, 9, 4};

    //int value=9;
    //
    
    // TODO: COMPLETAR - Pedir entrada al usuario
    
    int a[ARRAY_SIZE];
    
    pedirArreglo(a, ARRAY_SIZE);
    
    int value;
    
    printf ("Ingrese el valor de value \n");
    scanf ("%d", &value);
    
    //
    struct bound_data result = check_bound(value, a, ARRAY_SIZE);

    // TODO: REEMPLAZAR LO SIGUIENTE LUEGO POR LA SALIDA QUE PIDE EL ENUNCIADO
    
    if (result.exists == true){
    
        if (result.is_upperbound == true){
    
            printf("El valor es maximo\n");
    
        }
        
        if (result.is_lowerbound == true){
    
            printf("El valor es minimo\n");
    
        }
        
        printf("La posicion es %d\n", result.where);
    
    }
    
    else {
    
        if (result.is_upperbound == true){
    
            printf("El valor es cota superior\n");
    
        }
        
        if (result.is_lowerbound == true){
    
            printf("El valor es cota inferior\n");
    
        }
    
    }

    return EXIT_SUCCESS;
}

