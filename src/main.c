#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

#include "menu/menu.h"
#include "global/utils.h"
#include "entities/headers/user.h"
#include "entities/headers/vehicle.h"
#include "entities/headers/allocation.h"

void finalize(Car *cars, User *users);

int main() {
    setlocale(LC_ALL, ".utf8");

    int menuOption, attempt = 0;
    char returnToMain;

    Car *cars = malloc(VECTOR_SIZE * sizeof *cars);
    User *users = malloc(VECTOR_SIZE * sizeof *users); 
    Allocation *allocations = malloc(VECTOR_SIZE * sizeof(allocations));
    
    loadDatabases(cars, users);
    initializeRenting(allocations);
    
    do {
        Menu: menu();
        scanf("%d", &menuOption);
        buffer();

        if (menuOption < 0 || menuOption > 4) {
            clear();
            printf(RED "\n* Por favor, escolha uma opção válida [%d].\n" OFF, ++attempt);
            goto Menu;
        }

        switch (menuOption) {
            case 1:
                vehicleRental(users, cars, allocations);
                break;
            case 2:
                vehicleDelivery(users, cars, allocations);
                break;
            case 3:
                search(cars);
                break;
            case 4:
                vehicleReport(cars);
                break;
            case 0:
                finalize(cars, users);
                return(EXIT_SUCCESS);
        }

        printf(WHITE_U "\nDeseja retornar ao menu principal? (S/N)" OFF ": ");
        scanf("%c", &returnToMain);
        clear();
    } while (tolower(returnToMain) == 's');

    finalize(cars, users);
    return(EXIT_SUCCESS);
}

void finalize(Car *cars, User *users) {
    clear();
    free(cars);
    free(users);
    printf(END "\nPrograma encerrado.\n\n" OFF);
    system("pause");
}