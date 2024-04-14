/*
  @file main.c
  @brief Defines main program function
*/

/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "array_helpers.h"
#include "weather_utils.h"

/**
 * @brief print usage help
 * @param[in] program_name Executable name
 */
void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Load climate data from a given file in disk.\n"
           "\n"
           "The input file must exist in disk and every line in it must have the following format:\n\n"
           "<year> <month> <day> <temperature> <high> <low> <pressure> <moisture> <precipitations>\n\n"
           "Those elements must be integers and will be copied into the multidimensional integer array 'a'.\n"
           "The dimensions of the array are given by the macro tclimate.\n"
           "\n\n",
           program_name);
}

/**
 * @brief reads file path from command line
 *
 * @param[in] argc amount of command line arguments
 * @param[in] argv command line arguments
 *
 * @return An string containing read filepath
 */
char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

/**
 * @brief Main program function
 *
 * @param[in] argc amount of command line arguments
 * @param[in] argv command line arguments
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* create an array with the type of tclimate */
    WeatherTable array;

    /* parse the file to fill the array and obtain the actual length */
    array_from_file(array, filepath);

    /* show the ordered array in the screen */
    
    array_dump(array);
    
    printf("\n");
    printf("La menor temperatura historica registrada en Cordoba es %dº\n", his_min_temp(array));
    
    
    printf("\n");
    int max_temps[YEARS];
    procedimiento(array, max_temps);
    printf("La mayor temperatura máxima registrada por año en Córdoba es:\n");
    for (int i = 0; i < YEARS; i++) {
        printf("Año %d: %dº\n", i + 1980, max_temps[i]);
    }
    
    printf("\n");
    printf("Las mayores precipitaciones por año son: \n"); 
    month_t max_precipitation_months[YEARS];
    proc(array, max_precipitation_months);
    for (int i = 0; i < YEARS; i++) {
        printf("En el año %d el mes %d fue el de mayor precipitaciones\n", i + 1980, max_precipitation_months[i]);
    }

       

    return (EXIT_SUCCESS);
}
