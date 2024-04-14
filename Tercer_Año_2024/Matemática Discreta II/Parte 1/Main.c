#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "APIG24.h"
#include "EstructuraGrafo24.h"


// Main de testeo 
int main() {
    GrafoSt* grafo = ConstruirGrafo();
    if (grafo != NULL) {
        printf("Grafo construido correctamente:\n");
        printf("Número de vértices: %u\n", NumeroDeVertices(grafo));
        printf("Número de lados: %u\n", NumeroDeLados(grafo));
        printf("Delta del grafo: %u\n", Delta(grafo));
        /*printf("Grados de los vértices:\n");
        for (u32 i = 0; i < grafo->num_vertices; i++) {
            printf("Vértice %u: %u\n", i, Grado(i, grafo));
        }
        printf("Vecinos de los vértices:\n");
        for (u32 i = 0; i < grafo->num_vertices; i++) {
            printf("Vértice %u: ", i);
            for (u32 j = 0; j < Grado(i, grafo); j++) {
                printf("%u ", Vecino(j, i, grafo));
            }
            printf("\n");
        }*/
        color *colores = calloc(NumeroDeVertices(grafo), sizeof(color));
        assert(colores != NULL);
        for (u32 i = 0; i < NumeroDeVertices(grafo); i++) {
            colores[i] = NumeroDeVertices(grafo) - (i + 1);
        }
        ImportarColores(colores, grafo);
        //printf("Colores de los vertices:\n");
        /*for (u32 i = 0; i < NumeroDeVertices(grafo); i++) {
            printf("Vértice %u: %u\n", i, Color(i, grafo));
        }*/
        AsignarColor(35, 0, grafo);
        color *nuevosColores = calloc(NumeroDeVertices(grafo), sizeof(color));
        assert(nuevosColores != NULL);
        ExtraerColores(grafo, nuevosColores);
        
        /*printf("[");
        for (u32 i = 0; i < NumeroDeVertices(grafo); i++) {
            printf(" %u", nuevosColores[i]);
        }
        printf(" ]\n");*/
        free(nuevosColores);
        DestruirGrafo(grafo);
    } else {
        printf("No se pudo construir el grafo\n");
    }
    return 0;
}