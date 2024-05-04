#include "APIG24.h"
#include "API2024Parte2.h"
#include<assert.h>
#include <time.h>

//Ordenes iniciales
u32* OrdenNatural(Grafo G) {
    u32 n = NumeroDeVertices(G);
    u32* orden = malloc(n * sizeof(u32));
    if(orden == NULL){
        return NULL;
    }
    for (u32 i = 0; i < n; i++) {
        orden[i] = i;
    }
    return orden;
}

u32* OrdenInverso(Grafo G) {
    u32 n = NumeroDeVertices(G);
    u32* orden = malloc(n * sizeof(u32));
    if(orden == NULL){
        return NULL;
    }
    for (u32 i = 0; i < n; i++) {
        orden[i] = n - i - 1;
    }
    return orden;
}

u32* OrdenParesImpares(Grafo G) {
    u32 n = NumeroDeVertices(G);
    u32* orden = malloc(n * sizeof(u32));
    if (orden == NULL) {
        return NULL; 
    }
    u32 i = 0;
    for(u32 j = 0; j < n; j++){
        if(((n-1)-j) % 2 == 0) orden[i++] = ((n-1)-j);
    }
    u32 k = 1;
    for(u32 j = i; j < n; j++){
        orden[j] = k;
        k += 2;
    }
    return orden;
}

u32 *grados;

int cmpGrado(const void* a, const void* b) {
    u32* vertice_a = (u32*)a;
    u32* vertice_b = (u32*)b;
    return grados[*vertice_b] - grados[*vertice_a];
}

u32* OrdenGrado(Grafo G) {
    u32 n = NumeroDeVertices(G);
    u32* orden = malloc(n * sizeof(u32));
    if(orden == NULL){
        return NULL;
    }
    grados = malloc(n * sizeof(u32));
    if(grados == NULL){
        free(orden);
        return NULL;
    }
    for (u32 i = 0; i < n; i++) {
        orden[i] = i;
        grados[i] = Grado(i, G);
    }
    qsort(orden, n, sizeof(u32), cmpGrado);
    free(grados);
    return orden;
}

// Primero todos los pares en orden creciente
// luego todos los impares en orden creciente
u32* OrdenExtra(Grafo G) {
    u32 n = NumeroDeVertices(G);
    u32* orden = malloc(n * sizeof(u32));
    if(orden == NULL){
        return NULL;
    }
    u32 i = 0;
    for(u32 j = 0; j < n; j++){
        if(j % 2 == 0) orden[i++] = j;
    }
    u32 k = 1;
    for(u32 j = i; j < n; j++){
        orden[j] = k;
        k += 2;
    }
    return orden;
}

// Función para elegir aleatoriamente entre GulDukat y ElimGarak
char ElegirOrdenamiento(Grafo G, u32* Orden) {
    srand(time(NULL));
    return rand() % 2 == 0 ? GulDukat(G, Orden) : ElimGarak(G, Orden);
}

int main() {
    Grafo G = ConstruirGrafo();
    assert(G != NULL);
    u32 *Ordenes[5] = {OrdenNatural(G), OrdenInverso(G),
                        OrdenParesImpares(G), OrdenGrado(G), OrdenExtra(G)};
    
    typedef struct {
        u32 colores;
        color *coloreo;
    } resultado;

    resultado corridasIniciales[5];

    for(u32 i = 0; i < 5; i++){
        u32 cantColores = Greedy(G, Ordenes[i]);
        assert(cantColores != UINT32_MAX);
        printf("Orden inicial %d con %d colores\n", i, cantColores);
        for(u32 j = 0; j < 50; j++){
            u32 gul = GulDukat(G, Ordenes[i]);
            assert(gul == '0');
            cantColores = Greedy(G, Ordenes[i]);
            assert(cantColores != UINT32_MAX);
            printf("Orden Guldukat con %d colores\n", cantColores);
            u32 elim = ElimGarak(G, Ordenes[i]);
            assert(elim == '0');
            cantColores = Greedy(G, Ordenes[i]);
            assert(cantColores != UINT32_MAX);
            printf("Orden ElimGarak con %d colores\n", cantColores);
        }
        color * coloreo = calloc(NumeroDeVertices(G), sizeof(color));
        assert(coloreo != NULL);
        ExtraerColores(G, coloreo);
        resultado res = {cantColores, coloreo};
        corridasIniciales[i] = res;
    }

    u32 minima = 0;

    for(u32 i = 0; i < 5; i++){
        if(corridasIniciales[i].colores < corridasIniciales[minima].colores){
            minima = i;
        }
    }

    ImportarColores(corridasIniciales[minima].coloreo, G);
    u32 *Orden = calloc(NumeroDeVertices(G), sizeof(u32));
    assert(Orden != NULL);

    for(u32 i = 0; i < 500; i++){
        assert(ElegirOrdenamiento(G, Orden) == '0');
        u32 coloresRand = Greedy(G, Orden);
        assert(coloresRand != UINT32_MAX);
        printf("Orden aleatorio uso %d colores\n", coloresRand);
    }

    for(u32 i = 0; i < 5; i++){
        free(Ordenes[i]);
    }
    for(u32 i = 0; i < 5; i++){
        free(corridasIniciales[i].coloreo);
    }
    free(Orden);
    DestruirGrafo(G);
    return 0;
}



