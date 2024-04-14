#ifndef ESTRUCTURAGRAFO24_H
#define ESTRUCTURAGRAFO24_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef unsigned int u32;
typedef u32 color;

// Funcion auxiliar para determinar
// el maximo entre dos variables u32
u32 max(u32 a, u32 b);

typedef struct{
    u32 tamagno;
    u32 capacidad;
    u32 pos_libre;
    u32 *elementos;
}PilaSt;

typedef PilaSt* Pila;

// Asigna nueva memoria para una pila
// con capacidad inicial de 100 elementos.
// Si falla, devuelve NULL
Pila ConstruirPila();

// Libera toda la memoria asociada a p
void DestruirPila(Pila p);

// Apila el elemento e en la pila p. Si no hay
// capacidad suficiente, se duplica la capacidad
// de p y se agrega e.
// Devuelve 1 si tiene exito, caso contrario no
// se altera el estado de la pila y se devuelve
// 0
int Apilar(Pila p, u32 e);

// Devuelve el elemento i-esimo de p
// (el orden esta definido por como se fueron
// apilando los elementos en p)
u32 ElemEn(Pila p, u32 i);

// Devuelve la cantidad de elementos de p
u32 Tamagno(Pila p);

typedef struct {
    u32 num_vertices;
    u32 num_lados;
    color *colores;
    u32 delta;
    Pila *vecinos;
} GrafoSt;


#endif
