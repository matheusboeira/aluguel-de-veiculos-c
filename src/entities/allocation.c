#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "headers/allocation.h"
#include "../global/utils.h"

void printRent(Allocation *allocation, User *users, Car *cars) {
    printf(BLUE "[DADOS DA LOCAÇÃO]\n" OFF);
    printf("   Nome do cliente: " YELLOW_U "%s" OFF, (users+allocation->userId)->name);
    printf(" [ID: " YELLOW_U "%d" OFF "]\n", allocation->userId + 1);
    printf("   Placa do carro: " YELLOW_U "%s" OFF, (cars+allocation->carId)->licensePlate);
    printf(" [ID: " YELLOW_U "%d" OFF "]\n", allocation->carId + 1);
    printf("   Data de locação: ");
    printDate(allocation->dateStart);
    printf("\n   Data de devolução: ");
    printDate(allocation->dateEnd);
    printf("\n   Quilometragem máxima: %.1lf", allocation->maxKm);
    printf("\n");
}

void periodAllocation(Date date) {
    printf("\nPeríodo de locação: ");
    printf(BLUE);
    printDate(now());
    printf("~");
    printDate(date);
    printf(" - [%02ld] dia(s)." OFF, differenceBetween(date, now()));
}

void initializeRenting(Allocation *allocation) {
    for (int i = 0; i < QUANTITY_OF_VEHICLES; i++) {
        (allocation+i)->userId = -1;
        (allocation+i)->carId = -1;
    }
}