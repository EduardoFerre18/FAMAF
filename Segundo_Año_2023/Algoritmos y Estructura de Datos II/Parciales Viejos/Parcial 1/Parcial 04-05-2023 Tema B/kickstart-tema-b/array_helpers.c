/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "array_helpers.h"
static const int EXPECTED_DIM_VALUE = 2;

static const char* CITY_NAMES [CITIES] = {
  "Cordoba", "Rosario", "Posadas", "Tilcara", "Bariloche"
};
static const char* SEASON_NAMES [SEASONS] = {"Low", "High" };


/**
* @brief returns true when reach last line in products file
* @return True when is the last line of the file, False otherwise
*/
/*static bool is_last_line(unsigned int city) {
  return city == CITIES - 1u;
}*/

void array_dump(BakeryProductTable a) {
  for (unsigned int city = 0u; city < CITIES; ++city) {
    for(unsigned int season = 0u; season < SEASONS; ++season){
      fprintf(stdout, "%s in season %s: Yeast (%u,%u) Butter (%u,%u) flour (%u,%u) Sales value %u",
        CITY_NAMES[city], SEASON_NAMES[season], a[city][season].flour_cant, 
        a[city][season].flour_price, a[city][season].butter_cant,
        a[city][season].butter_price,  a[city][season].yeast_cant,
        a[city][season].yeast_price, a[city][season].sale_value
      );
      fprintf(stdout, "\n");   
    }
  }
}

unsigned int profit(BakeryProduct b){
  unsigned int cost = 0u;
  unsigned int profit = 0u;
  cost = (b.butter_cant * b.butter_price) + (b.flour_cant * b.flour_price) + (b.yeast_cant * b.yeast_price);
  if (b.sale_value > cost) {
    profit = b.sale_value - cost;
  }
  else {
    profit = 0;
  }
  return profit;
}


unsigned int worst_profit(BakeryProductTable a) {
  unsigned int min_profit = INT_MAX;
  for (unsigned int city = 0; city < CITIES; city++){
    for (unsigned int season = 0; season < SEASONS; season++)
      if (profit(a[city][season]) < min_profit) {
        min_profit = profit(a[city][season]);
      }
  }
  return min_profit;
}

void array_from_file(BakeryProductTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }
  
  unsigned int city;
  unsigned int season;
  while(!feof(file)) {
    int res = fscanf(file," ##%u??%u ", &city, &season);
    if (res != EXPECTED_DIM_VALUE) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    BakeryProduct product = bakery_product_from_file(file);
    array[city][season] = product;
  
  }


  fclose(file);
}
