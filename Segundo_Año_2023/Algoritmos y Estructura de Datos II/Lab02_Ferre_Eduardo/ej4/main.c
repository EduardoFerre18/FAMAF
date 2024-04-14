#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función para convertir de binario a hexadecimal
void binToHex(char* bin_num) {
    int decimal_num = strtol(bin_num, NULL, 2);  // Convierte el binario a decimal
    char hex_num[20];  // Almacena el número hexadecimal resultante
    sprintf(hex_num, "%X", decimal_num);  // Convierte el decimal a hexadecimal
    printf("El número hexadecimal es: %s\n", hex_num);
}

// Función para convertir de hexadecimal a binario
void hexToBin(char* hex_num) {
    int decimal_num = strtol(hex_num, NULL, 16);  // Convierte el hexadecimal a decimal
    char bin_num[65];  // Almacena el número binario resultante
    _itoa(decimal_num, bin_num, 2);  // Convierte el decimal a binario

    // Agrega espacios cada 4 dígitos en el número binario
    int len = strlen(bin_num);
    printf("El número binario es: ");
    for (int i = 0; i < len; i++) {
        printf("%c", bin_num[i]);
        if ((i + 1) % 4 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    int choice;
    char num[65];

    // Menú de opciones
    while (1) {
        printf("Calculadora de conversión de Binario a Hexadecimal y viceversa\n");
        printf("1. Convertir de Binario a Hexadecimal\n");
        printf("2. Convertir de Hexadecimal a Binario\n");
        printf("3. Salir\n");
        printf("Ingresa tu elección (1/2/3): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Ingresa un número binario: ");
                scanf("%s", num);
                binToHex(num);
                break;
            case 2:
                printf("Ingresa un número hexadecimal: ");
                scanf("%s", num);
                hexToBin(num);
                break;
            case 3:
                printf("¡Hasta luego!\n");
                exit(0);
            default:
                printf("Opción inválida. Por favor, selecciona una opción válida (1/2/3).\n");
                break;
        }
    }

    return 0;
}
