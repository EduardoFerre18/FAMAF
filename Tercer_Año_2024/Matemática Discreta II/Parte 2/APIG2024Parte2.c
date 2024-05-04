#include "API2024Parte2.h"

// Funcion auxiliar que calcula el maximo elemento en arr
color MaxElem(color arr[], u32 n){
    color mx = arr[0];

    for (u32 i = 1; i < n; i++){
        if (arr[i] > mx) mx = arr[i];
    }

    return mx;
}
 
// Funcion para hacer countingsort segun
// el digito representado por exp
void countSort(color arr[], u32 n, u32 exp){
    color output[n];
    u32 i, count[10] = { 0 };
 
    for (i = 0; i < n; i++){
        count[(arr[i] / exp) % 10]++;
    }
 
    for (i = 1; i < 10; i++){
        count[i] += count[i - 1];
    }
 
    for (int j = n - 1; j >= 0; j--) {
        output[count[(arr[j] / exp) % 10] - 1] = arr[j];
        count[(arr[j] / exp) % 10]--;
    }

    for (i = 0; i < n; i++){
        arr[i] = output[i];
    }
}

// Funcion que ordena arr usando radixsort,
// que en este caso tiene complejidad O(n)
// donde n es el largo de arr
void radixsort(color arr[], u32 n){
    color m = MaxElem(arr, n);

    for (u32 exp = 1; m / exp > 0; exp *= 10){
        countSort(arr, n, exp);
    }
}

u32 Greedy(Grafo G, u32* Orden){
    u32 n = NumeroDeVertices(G);
    int *apariciones = calloc(n, sizeof(int));

    if(apariciones == NULL){
        return UINT32_MAX;
    }

    // Verifico que Orden induce una
    // biyeccion en 0, ..., n-1
    for(u32 i = 0; i < n; i++){

        if(Orden[i] >= n){
            free(apariciones);
            return UINT32_MAX;
        }

        apariciones[Orden[i]]++;

        if(apariciones[Orden[i]] > 1){
            free(apariciones);
            return UINT32_MAX;
        }
    }

    free(apariciones);
    color *coloreo = calloc(n, sizeof(color));

    if(coloreo == NULL){
        return UINT32_MAX;
    }

    u32 cantColores = 0;

    for(u32 i = 0; i < n; i++){
        u32 v = Orden[i];
        color *coloresVecinos = calloc(Grado(v, G), sizeof(color));

        if(coloresVecinos == NULL){
            free(coloreo);
            return UINT32_MAX;
        }

        for(u32 j = 0; j < Grado(v, G); j++){
            u32 w = Vecino(j, v, G);
            coloresVecinos[j] = coloreo[w];
        }

        radixsort(coloresVecinos, Grado(v, G));
        color c = 1;

        for(u32 j = 0; j < Grado(v, G); j++){
            if(c == coloresVecinos[j]) c++;
        }

        coloreo[v] = c;

        if(c > cantColores){
            cantColores = c;
        }
        
        free(coloresVecinos);
    }

    for(u32 i = 0; i < n; i++){
        AsignarColor(coloreo[i], i, G);
    }

    free(coloreo);
    return cantColores;
}



//Funciones de orden


// Estructura para GulDukat
typedef struct {
    u32 color;
    u32 grado;
    u32 indice;
    u32 min_grado;
    u32 max_grado;
} Vertice;

// Funciones de comparación para qsort
int comparar_divisible_por_4(const void *a, const void *b) {
    Vertice *verticeA = (Vertice *)a;
    Vertice *verticeB = (Vertice *)b;
    if(verticeB->max_grado == verticeA->max_grado){
        return verticeB->color - verticeA->color;
    }
    return verticeB->max_grado - verticeA->max_grado;
}

int comparar_par_no_divisible_por_4(const void *a, const void *b) {
    Vertice *verticeA = (Vertice *)a;
    Vertice *verticeB = (Vertice *)b;
    if((verticeB->max_grado + verticeB->min_grado) == (verticeA->max_grado + verticeA->min_grado)){
        return verticeB->color - verticeA->color;
    }
    return (verticeB->max_grado + verticeB->min_grado) - (verticeA->max_grado + verticeA->min_grado);
}

int comparar_impar(const void *a, const void *b) {
    Vertice *verticeA = (Vertice *)a;
    Vertice *verticeB = (Vertice *)b;
    if(verticeB->min_grado == verticeA->min_grado){
        return verticeB->color - verticeA->color;
    }
    return verticeB->min_grado - verticeA->min_grado;
}

char GulDukat(Grafo G, u32* Orden) {
    u32 n = NumeroDeVertices(G);
    color r = 0;
    for (u32 i = 0; i < n; i++) {
        color color = Color(i, G);
        if (color > r) {
            r = color;
        }
    }
    r = r + 1;

    //Creo 3 listas de vertices
    Vertice *divisible_por_4 = malloc(n * sizeof(Vertice));
    Vertice *par_no_divisible_por_4 = malloc(n * sizeof(Vertice));
    Vertice *impar = malloc(n * sizeof(Vertice));

    if (divisible_por_4 == NULL || par_no_divisible_por_4 == NULL || impar == NULL) {
        free(divisible_por_4);
        free(par_no_divisible_por_4);
        free(impar);
        return '1';
    }

    u32 count_divisible_por_4 = 0;
    u32 count_par_no_divisible_por_4 = 0;
    u32 count_impar = 0;

    u32 min_grado[r];
    u32 max_grado[r];
    for (u32 i = 0; i < r; i++) {
        min_grado[i] = UINT32_MAX;
        max_grado[i] = 0;
    }

    //calculo m(x) y M(x)
    for (u32 i = 0; i < n; i++) {
        color color = Color(i, G);
        u32 grado = Grado(i, G);

        // Actualizar min_grado y max_grado
        if (grado < min_grado[color]) {
            min_grado[color] = grado;
        }
        if (grado > max_grado[color]) {
            max_grado[color] = grado;
        }
    }

    // Segunda pasada para llenar las listas de vértices
    for (u32 i = 0; i < n; i++) {
        color color = Color(i, G);
        u32 grado = Grado(i, G);

        Vertice vertice = {color, grado, i, min_grado[color], max_grado[color]};

        if (color % 4 == 0) {
            divisible_por_4[count_divisible_por_4] = vertice;
            count_divisible_por_4++;
        } else if (color % 2 == 0) {
            par_no_divisible_por_4[count_par_no_divisible_por_4] = vertice;
            count_par_no_divisible_por_4++;
        } else {
            impar[count_impar] = vertice;
            count_impar++;
        }
    }

    // Ordeno listas con qsort
    qsort(divisible_por_4, count_divisible_por_4, sizeof(Vertice), comparar_divisible_por_4);
    qsort(par_no_divisible_por_4, count_par_no_divisible_por_4, sizeof(Vertice), comparar_par_no_divisible_por_4);
    qsort(impar, count_impar, sizeof(Vertice), comparar_impar);

    // Lleno el array Orden con los vértices en el orden correcto
    u32 index = 0;
    for (u32 i = 0; i < count_divisible_por_4; i++) {
        Orden[index] = divisible_por_4[i].indice;
        index++;
    }
    for (u32 i = 0; i < count_par_no_divisible_por_4; i++) {
        Orden[index] = par_no_divisible_por_4[i].indice;
        index++;
    }
    for (u32 i = 0; i < count_impar; i++) {
        Orden[index] = impar[i].indice;
        index++;
    }

    free(divisible_por_4);
    free(par_no_divisible_por_4);
    free(impar);

    return '0';
}

// Arreglos globales para ElimGarak
u32 *colorConteo;
color *colores;

// Funciones de comparacion para ElimGarak
int cmp1(const void* a, const void* b) {
    u32* vertice_a = (u32*)a;
    u32* vertice_b = (u32*)b;
    if(colorConteo[colores[*vertice_b] - 1] == colorConteo[colores[*vertice_a] - 1]){
        return colores[*vertice_b] - colores[*vertice_a];
    }
    return (colorConteo[colores[*vertice_a] - 1] - colorConteo[colores[*vertice_b] - 1]);
}

int cmp2(const void* a, const void* b) {
    u32* vertice_a = (u32*)a;
    u32* vertice_b = (u32*)b;
    if(colores[*vertice_a] == 1) return 1;
    else if(colores[*vertice_b] == 1) return -1;
    else if(colores[*vertice_a] == 2) return 1;
    else if(colores[*vertice_b] == 2) return -1;
    else return 0;
}

char ElimGarak(Grafo G, u32* Orden){
    u32 n = NumeroDeVertices(G);
    colores = calloc(n, sizeof(color));

    if(colores == NULL){
        return '1';
    }

    color cantColores = 0;

    for(u32 i = 0; i < n; i++){
        Orden[i] = i;
        colores[i] = Color(i, G);
        if(Color(i, G) > cantColores) cantColores = Color(i, G);
    }

    colorConteo = calloc(cantColores, sizeof(u32));

    if(colorConteo == NULL){
        free(colores);
        return '1';
    }

    for(u32 i = 0; i < n; i++){
        colorConteo[Color(i, G) - 1]++; 
    }

    qsort(Orden, n, sizeof(u32), cmp1);
    qsort(Orden, n, sizeof(u32), cmp2);
    free(colores);
    free(colorConteo);
    return '0';
}
