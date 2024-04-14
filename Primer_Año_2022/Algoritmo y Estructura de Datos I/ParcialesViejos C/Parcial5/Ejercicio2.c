#include <stdio.h>
#include <assert.h>



struct color_t {
int rojo;
int verde;
int azul;
};


struct color_t calcular_color(int color_id)   {

    struct color_t res;

    assert ((color_id >= 0) && (color_id < 16777215) );
    
    int v_azul = (color_id / 65536);
    int v_verde = (color_id % 65536) / 256;
    int v_rojo = (color_id % 65536) % 256;

    res.azul = v_azul;
    res.verde = v_verde;
    res.rojo = v_rojo;

    return res;
}

int main (void) {

    struct color_t resultado;
    
    int color_id;

    printf("Ingrese un identificador de color\n");
    scanf ("%d", &color_id);

    if ((color_id < 0)|| (color_id >16777215 )) {
        printf ("Usted ingreso un identificador negativo o mayor que 16777215\n");
    }
    else {
        resultado = calcular_color (color_id);
        printf("El valor azul es %d, el valor verde es %d y el valor rojo es %d", resultado.azul, resultado.verde, resultado.rojo);
    }

    return 0;




}