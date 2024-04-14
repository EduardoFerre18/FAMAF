#include <stdio.h>
#include <assert.h>

int pedirSegundos (void) {
    int segs;
    printf("Ingrese la cantidad de segundos\n");
    scanf("%d", &segs);
    return segs;
}

struct lapso_t {
int horas;
int minutos;
int segundos;
};

struct lapso_t calcular_lapso(int segs) {

    assert (segs >= 0);
    
    struct lapso_t res;
    
    int hor = (segs / 3600);

    int mins = (segs % 3600) / 60;

    segs = (segs % 3600) % 60;

    res.horas = hor;
    res.minutos = mins;
    res.segundos = segs;

    return res;

}


int main (void) {

    int segs = pedirSegundos ();

    struct lapso_t resultado;

    if (segs < 0) {
        printf ("Usted ingreso una cantidad de segundos negativa\n");
    }

    else {

        resultado = calcular_lapso (segs);

        printf ("La cantidad de horas es %d, la cantidad de minutos es %d y la cantidad de segundos es %d\n", resultado.horas, resultado.minutos, resultado.segundos); 

    }

    return 0;





}