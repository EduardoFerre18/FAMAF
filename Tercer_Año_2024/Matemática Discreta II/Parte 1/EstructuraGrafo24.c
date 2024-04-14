#include "APIG24.h"
#include "EstructuraGrafo24.h"
#include <assert.h>

u32 max(u32 a, u32 b){
    return (a > b) ? a : b;
}

Pila ConstruirPila(){
    Pila p = (Pila)malloc(sizeof(PilaSt));
    if(p == NULL){
        printf("Error: No se pudo asignar memoria para la pila\n");
        return NULL;
    }
    p->tamagno = 0;
    p->pos_libre = 0;
    p->capacidad = 100;
    p->elementos = calloc(100, sizeof(u32));
    if(p->elementos == NULL){
        printf("Error: No se pudo asignar memoria para la pila\n");
        free(p);
        return NULL;
    }
    return p;
}

void DestruirPila(Pila p){
    if(p != NULL){
        free(p->elementos);
        free(p);
        p = NULL;
    }
}

int Apilar(Pila p, u32 e){
    if(p->tamagno == p->capacidad){
        u32 *temp = p->elementos;
        p->elementos = realloc(p->elementos, (p->capacidad) * 2 * sizeof(u32));
        if(p->elementos == NULL){
            printf("Error: No se pudo asignar memoria para la pila\n");
            p->elementos = temp;
            return 0;
        }
        p->capacidad *= 2;
    }
    p->elementos[p->pos_libre] = e;
    p->tamagno++;
    p->pos_libre++;
    return 1;
}

u32 ElemEn(Pila p, u32 i){
    return p->elementos[i];
}

u32 Tamagno(Pila p){
    return p->tamagno;
}

//Funciones de construccion y destruccion de grafo

GrafoSt* ConstruirGrafo() {
    GrafoSt* grafo = (GrafoSt*)malloc(sizeof(GrafoSt));
    if (grafo == NULL) {
        printf("Error: No se pudo asignar memoria para el grafo\n");
        return NULL;
    }
    u32 num_vertices = 0;
    u32 num_lados = 0;
    // Ignorar líneas de comentario al principio del archivo
    int ch;
    while ((ch = getchar()) != EOF) {
        if (ch == 'c') {
            // Ignorar la línea completa
            while (getchar() != '\n');
        } else if (ch == 'p') {
            // Formato p edge n m
            if(scanf(" edge %u %u", &num_vertices, &num_lados) != 2){
                fprintf(stderr, "Error: Formato de entrada inválido\n");
                free(grafo);
                return NULL;
            }
            break; // Salgo del bucle cuando se encontró 'p'
        } else {
            // Si se encuentra un carácter que no es 'c' o 'p', generar error
            fprintf(stderr, "Error: Entrada inválida. Se esperaba 'c' o 'p'\n");
            free(grafo);
            return NULL;
        }
    }
    grafo->num_vertices = num_vertices;
    grafo->num_lados = num_lados;
    grafo->delta = 0;
    // calloc inicializa el arreglo con 0's
    grafo->colores = calloc(num_vertices, sizeof(u32));
    if(grafo-> colores == NULL){
        printf("Error: No se pudo asignar memoria para el grafo\n");
        free(grafo);
        return NULL;
    }
    grafo->vecinos = calloc(num_vertices, sizeof(Pila));
    if(grafo-> vecinos == NULL){
        printf("Error: No se pudo asignar memoria para el grafo\n");
        free(grafo->colores);
        free(grafo);
        return NULL;
    }
    // Inicializar pilas de vecinos
    for (u32 i = 0; i < grafo->num_vertices; i++) {
        grafo->vecinos[i] = ConstruirPila();
        if(grafo->vecinos[i] == NULL){
            printf("Error: No se pudo asignar memoria para el grafo\n");
            // Destruyo las pilas que se habian iniciado
            for(u32 j = 0; j < i; j++){
                DestruirPila(grafo->vecinos[j]);
            }
            free(grafo->vecinos);
            free(grafo->colores);
            free(grafo);
            return NULL;
        }
    }
    u32 lineas_leidas = 0;
    while(lineas_leidas < grafo->num_lados){
        u32 v, w;
        if(scanf(" e %u %u", &v, &w) != 2){
            fprintf(stderr, "Error: Formato de entrada inválido. %u lineasleidas\n", lineas_leidas);
            for(u32 i = 0; i < grafo->num_vertices; i++){
                DestruirPila(grafo->vecinos[i]);
            }
            free(grafo->vecinos);
            free(grafo->colores);
            free(grafo);
            return NULL;
        }
        if(!Apilar(grafo->vecinos[v], w) || !Apilar(grafo->vecinos[w], v)){
            for(u32 i = 0; i < grafo->num_vertices; i++){
                DestruirPila(grafo->vecinos[i]);
            }
            free(grafo->vecinos);
            free(grafo->colores);
            free(grafo);
            return NULL;
        }
        grafo->delta = max(grafo->delta, max(Tamagno(grafo->vecinos[v]), Tamagno(grafo->vecinos[w])));
        lineas_leidas++;
    }
    return grafo;
}


void DestruirGrafo(Grafo G){
    if (G != NULL) {
        for(u32 i = 0; i < G->num_vertices; i++){
            DestruirPila(G->vecinos[i]);
        }
        free(G->vecinos);
        free(G->colores);
        free(G);
        G = NULL;
    }
}

//Funciones para extraer datos del grafo

u32 NumeroDeVertices(Grafo G) {
    return G->num_vertices;
}

u32 NumeroDeLados(Grafo G) {
    return G->num_lados;
}

u32 Delta(Grafo G) {
    return G->delta;
}

//Funciones de extraccion de informacion de vertices 

u32 Grado(u32 i, Grafo G) {
    if (i < G->num_vertices) {
        return Tamagno(G->vecinos[i]);
    } else {
        return 0; // No puede haber vértices con índices mayores o iguales al número de vértices
    }
}

color Color(u32 i, Grafo G) {
    if (i < G->num_vertices) {
        return G->colores[i];
    } else {
        return UINT32_MAX; // Devuelvo el máximo valor para indicar que el índice está fuera de rango
    }
}

u32 Vecino(u32 j, u32 i, Grafo G) {
    if (i < G->num_vertices && j < Tamagno(G->vecinos[i])) {
        return ElemEn(G->vecinos[i], j);
    } else {
        return UINT32_MAX; // Devuelvo el máximo valor para indicar que el índice está fuera de rango
    }
}

// Funciones para asignar colores

void AsignarColor(color x, u32 i, Grafo G){
    if(i < G->num_vertices){
        G->colores[i] = x;
    }
}

// ¿Tiene que ser O(1)?
void ExtraerColores(Grafo G, color* Color){
    for(u32 i = 0; i < G->num_vertices; i++){
        Color[i] = G->colores[i];
    }
    // Solucion O(1), pero deja al grafo inconsistente
    //Color = G->colores;
    //G-> colores = NULL;
}

void ImportarColores(color* Color, Grafo G){
    free(G->colores);
    G->colores = Color;
    Color = NULL;
}




