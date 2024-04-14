/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"
#include <limits.h>

static const int EXPECTED_DIM_VALUE = 2;

static const char* CITY_NAMES[CITIES] = {
    "Cordoba", "Rosario", "Posadas", "Tilcara", "Bariloche"};
static const char* SEASON_NAMES[SEASONS] = {"low", "high"};

void array_dump(BakeryProductTable a)
{
    for (unsigned int city = 0u; city < CITIES; ++city)
    {
        for (unsigned int season = 0u; season < SEASONS; ++season)
        {
            fprintf(stdout, "%s in %s season: flour (%u,%u) Yeast (%u,%u) Butter (%u,%u) Sales value %u",
                    CITY_NAMES[city], SEASON_NAMES[season], a[city][season].flour_cant,
                    a[city][season].flour_price, a[city][season].yeast_cant,
                    a[city][season].yeast_price, a[city][season].butter_cant,
                    a[city][season].butter_price, a[city][season].sale_value);
            fprintf(stdout, "\n");
        }
    }
}

unsigned int profit (BakeryProduct product) {
    unsigned int profit;
    unsigned int cost = (product.flour_cant * product.flour_price) + (product.yeast_cant * product.yeast_price) + (product.butter_cant * product.butter_price);
    if (cost > product.sale_value) {
        profit = 0;
    }
    else {
        profit = product.sale_value - cost;
    }
    return profit;
}

unsigned int best_profit(BakeryProductTable a)
{
    unsigned int max_profit = 0u;
    for (unsigned int city = 0u; city < CITIES; ++city){
        for (unsigned int season = 0u; season < SEASONS; ++season){
            if (profit(a[city][season]) > max_profit){
                max_profit = profit(a[city][season]);
            }
        }
    }
    return max_profit;
}

void array_from_file(BakeryProductTable array, const char* filepath)
{
    FILE* file = NULL;

    file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int k_city; 
    unsigned int k_season;
    while (!feof(file))
    {
        int res = fscanf(file," ##%u??%u ", &k_city, &k_season);
        if (res != EXPECTED_DIM_VALUE)
        {
            fprintf(stderr, "Invalid file.\n");
            exit(EXIT_FAILURE);
        }
       BakeryProduct bakery = bakery_product_from_file(file);
       array[k_city][k_season] = bakery;

    }
    fclose(file);
}

//Probando