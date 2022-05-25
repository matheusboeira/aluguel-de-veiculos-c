#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../global/utils.h"
#include "headers/vehicle.h"

/**
 * Daily price for car rental by category.
 */
#define PRICE_SPORTING 200.0
#define PRICE_SEDAN 150.0
#define PRICE_CROSSOVER 100.0
#define PRICE_SUV 175.0
#define PRICE_PICAPE 125.0

/**
 * Max kilometers by category.
 */
#define MAX_KM_SPORTING 600.0
#define MAX_KM_SEDAN 800.0
#define MAX_KM_CROSSOVER 400.0
#define MAX_KM_SUV 450.0
#define MAX_KM_PICAPE 300.0

/**
 * Kilometer value by category.
 */
#define VALUE_KM_SPORTING 12.5
#define VALUE_KM_SEDAN 10.0
#define VALUE_KM_CROSSOVER 7.5
#define VALUE_KM_SUV 10.0
#define VALUE_KM_PICAPE 11.0

int vehiclesByCategory;

void printCar(Car *car) {
    printf("\033[7;33m\n[CARRO]:\n\033[0m");
    printf("  ID: \033[4;33m%d\033[0m\n", car->id);
    printf("  Placa: %s\n", car->licensePlate);
    printf("  Modelo: %s\n", car->model);
    printf("  Ano: %d\n", car->year);
    printf("  Quilometragem: %.2lf Km\n", car->kilometers);
}

double getPriceByCategory(char *category) {
    if (strcmp(category, "ESPORTIVO") == 0) return PRICE_SPORTING;
    if (strcmp(category, "SEDAN") == 0) return PRICE_SEDAN;
    if (strcmp(category, "CROSSOVER") == 0) return PRICE_CROSSOVER;
    if (strcmp(category, "SUV") == 0) return PRICE_SUV;
    if (strcmp(category, "PICAPE") == 0) return PRICE_PICAPE;
    return -1;
}

double getPriceKilometerByCategory(char *category) {
    if (strcmp(category, "ESPORTIVO") == 0) return VALUE_KM_SPORTING;
    if (strcmp(category, "SEDAN") == 0) return VALUE_KM_SEDAN;
    if (strcmp(category, "CROSSOVER") == 0) return VALUE_KM_CROSSOVER;
    if (strcmp(category, "SUV") == 0) return VALUE_KM_SUV;
    if (strcmp(category, "PICAPE") == 0) return VALUE_KM_PICAPE;
    return -1;
}

double getMaxKmByCategory(int categoryOption) {
    switch (categoryOption) {
        case 1: return MAX_KM_SPORTING;            
        case 2: return MAX_KM_SEDAN;            
        case 3: return MAX_KM_CROSSOVER;             
        case 4: return MAX_KM_SUV;
        case 5: return MAX_KM_PICAPE;
        default: return -1;
    }
}

void printCarByCategory(Car *cars, char *category) {
    vehiclesByCategory = 0;
    int index = 0;

    for (int i = 0; i < QUANTITY_OF_VEHICLES; i++) {
        if (strcmp((cars+i)->category, category) == 0 && (cars+i)->isRented != 1) {
            vehiclesByCategory++;

            if (vehiclesByCategory == 1) {
                printf("CATEGORIA: " BLUE "[%s]\n" OFF, category);
            }
            printf(YELLOW_F "\n[CARRO #%d]:\n" OFF, ++index);
            printf("  ID: " YELLOW_U "%d\n" OFF, (cars+i)->id);
            printf("  Placa: %s\n", (cars+i)->licensePlate);
            printf("  Modelo: %s\n", (cars+i)->model);
            printf("  Ano: %d\n", (cars+i)->year);
            printf("  Quilometragem: %.2lf Km\n", (cars+i)->kilometers);
        }
    }
    if (vehiclesByCategory == 0) {
        printf(RED "\nNão há veículos disponíveis para esta categoria.\n" OFF);
    }
}

void printCars(Car *cars) {
    for (int i = 0; i < QUANTITY_OF_VEHICLES; i++) {
        printf(YELLOW_F "\n[CARRO #%d]:\n" OFF, (i + 1));
        printf("  ID: %d\n", (cars+i)->id);
        printf("  Placa: %s\n", (cars+i)->licensePlate);
        printf("  Marca: %s\n", (cars+i)->brand);
        printf("  Modelo: %s\n", (cars+i)->model);
        printf("  Ano: %d\n", (cars+i)->year);
        printf("  Quilometragem: %.2lf Km\n", (cars+i)->kilometers);
        printf("  Categoria: %s\n", (cars+i)->category);
        printf("  Alugado: ");
        (cars+i)->isRented == 1 ? printf("Sim\n") : printf("Não\n");
    }
}
