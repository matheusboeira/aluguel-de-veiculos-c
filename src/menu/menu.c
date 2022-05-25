#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "../entities/headers/user.h"
#include "../entities/headers/vehicle.h"
#include "../entities/headers/allocation.h"
#include "../global/utils.h"
#include "menu.h"

/* start */
void menu() {
    printf("\nMenu de opções:\n");
    printf("\n\t1 - Locação de Veículo");
    printf("\n\t2 - Entrega de Veículo");
    printf("\n\t3 - Busca de Veículo");
    printf("\n\t4 - Relatório");
    printf("\n\t0 - Encerrar\n");
    printf(YELLOW "\nEscolha uma opção acima: " OFF);
}

/* categories of cars */
void categoryMenu() {
    printf("\nMenu de opções:\n");
    printf("\n\t1 - Esportivo");
    printf("\n\t2 - Sedan");
    printf("\n\t3 - Crossover");
    printf("\n\t4 - SUV");
    printf("\n\t5 - Picape");
    printf("\n\t0 - Sair\n");
    printf(YELLOW "\nPor favor, escolha uma categoria: " OFF);
}

/* report options */
void reportMenu() {
    printf("\nMenu de opções:\n");
    printf("\n\t1 - Visualizar Relatório");
    printf("\n\t2 - Gerar Arquivo de Relatório");
    printf("\n\t0 - Sair\n");
    printf(YELLOW "\nPor favor, escolha uma categoria: " OFF);
}

void deliveryMenu() {
    printf("\nMenu de opções:\n");
    printf("\n\t1 - Visualizar locações\n");
    printf("\t2 - Devolução de veículos\n");
    printf("\t0 - Sair\n");
    printf(YELLOW "\nDigite uma das opções acima: " OFF);
}

char *categoriesOptions(int categoryOption) {
    switch (categoryOption) {
        case 1: return "ESPORTIVO";                
        case 2: return "SEDAN";                
        case 3: return "CROSSOVER";               
        case 4: return "SUV"; 
        case 5: return "PICAPE";  
        default: return "SAIR";
    }
}

/* case 1 */
void vehicleRental(User *users, Car *cars, Allocation *allocations) {
    clear();

    /* user informations */
    int userId;
    long long cnh;

    /* car choice */
    int carId;

    /* options */
    int categoryOption;
    char *category = malloc(50 * sizeof(char));
    double categoryMaxKm;
    char confirmLocation;
    char backToCategories;

    /* handlers */
    int userNotFound;
    int backToMenu;
    int attempt = 0;

    /* date */
    int day, month, year;

    do {
        backToMenu = userNotFound = 0;

        printf(BLUE "\n[LOCAÇÃO DE VEÍCULO]\n" OFF);
        printf(YELLOW "\nDigite a CNH: " OFF);
        scanf("%lld", &cnh);

        userId = getUser(users, cnh);

        if (userId == -1) {
            clear();
            printf(RED "\n* Usuário não encontrado em nosso sistema.\n" OFF);
            userNotFound = 1;
        } else {
            clear();
            printf(YELLOW "\nUsuário identificado: " OFF GREEN_U "%s\n" OFF, (users+userId)->name);
            Menu: categoryMenu();
            scanf("%d", &categoryOption);
            buffer();

            if (categoryOption < 0 || categoryOption > 5) {
                clear();
                printf(RED "\n* Por favor, escolha uma categoria válida [%d].\n" OFF, ++attempt);
                goto Menu;
            }
            category = categoriesOptions(categoryOption);
            categoryMaxKm = getMaxKmByCategory(categoryOption);
            
            if (strcmp(category, "SAIR") == 0) break;
            
            clear();
            do {
                printCarByCategory(cars, category);

                /** Canceling if there's no vehicles in the list */
                if (vehiclesByCategory == 0) break;
                
                printf(BLUE "\nPreço desta categoria é de " OFF);
                printf(GREEN "R$ %.2lf" OFF BLUE "/dia.\n" OFF, getPriceByCategory(category));
                printf(YELLOW "\nSelecione o carro a ser alugado (ID): " OFF);
                scanf("%d", &carId);
                buffer();
                clear();

                if (carId > 0 && carId <= QUANTITY_OF_VEHICLES && strcmp((cars+carId-1)->category, category) == 0 
                        && (cars+carId-1)->isRented == 0) {
                    printf(BLUE "[INFORMAÇÕES DO VEÍCULO]\n" OFF);
                    printCar((cars+carId-1));

                    Date date;
                    int validDate;

                    do {
                        validDate = 1;

                        printf(YELLOW "\nInforme a data de devolução (## ## ####): " OFF);
                        scanf("%d %d %d", &day, &month, &year);
                        buffer();

                        date = setDate(day, month, year);
                        
                        if (differenceBetween(date, now()) <= 0) {
                            clear();
                            printf(RED "\nData inválida, anterior ou equivalente ao dia de hoje.\n");
                            validDate = 0;
                        } else {
                            clear();
                            printf(BLUE "[INFORMAÇÕES DO VEÍCULO]\n" OFF);
                            printCar((cars+carId-1));
                        }
                    } while (validDate == 0);
                        
                    periodAllocation(date);

                    printf(GREEN_B "\n\nDeseja realmente alugar este carro? (S/N): " OFF);
                    scanf("%c", &confirmLocation);
                    buffer();
                    clear();

                    if (tolower(confirmLocation) == 's') {
                        (cars+carId-1)->isRented = 1;

                        for (int i = 0; i < QUANTITY_OF_VEHICLES; i++) {
                            if ((allocations+i)->userId == -1) {
                                (allocations+i)->userId = userId;
                                (allocations+i)->carId = carId - 1; // array index starts in 0
                                (allocations+i)->dateStart = now();
                                (allocations+i)->dateEnd = date;
                                (allocations+i)->maxKm = categoryMaxKm;
                                printRent((allocations+i), users, cars);
                                break;
                            }
                        }
                        printf(GREEN "\n> Locação concluída com sucesso!\n" OFF);
                        break;
                    } else {
                        printf(YELLOW_W "\n* Operação cancelada.\n\033[0m");
                        printf(YELLOW "\nDeseja retornar ao menu de categorias? (S/N): " OFF);
                        scanf("%c", &backToCategories);
                        buffer();
                        clear();
                    }
                } else {
                    clear();
                    printf(RED "* Selecione um ID válido.\n\n" OFF);
                    carId = -1;
                }
            } while (carId < 1);
        }
    } while (backToMenu == 1 || userNotFound == 1 || backToCategories == 's');
}

/* case 2 */
void vehicleDelivery(User *users, Car *cars, Allocation *allocations) {
    /* login informations */
    int userId;
    int carId;
    int allocationId;
    int found;

    /* informations */
    double km;
    int points;
    double daily;
    double excessMileage = 0.0;
    double totalToPay;

    /* options */
    int menuOption;
    char returnToMenu;
    char viewCars;

    /* control */
    int counter = 0;
    int exit;
    int invalidKm;

    do {
        exit = 0;
        clear();

        deliveryMenu();
        scanf("%d", &menuOption);
        buffer();

        switch (menuOption) {
            case 1: 
                counter = 0;
                clear();

                for (int i = 0; i < QUANTITY_OF_VEHICLES; i++) {
                    if ((allocations+i)->userId != -1 && (allocations+i)->carId != -1) {
                        printRent((allocations+i), users, cars);
                        printf("\n");
                        counter++;
                    }
                }

                if (counter == 0) {
                    clear();
                    printf(RED "\n* Nenhum veículo alugado encontrado.\n\n" OFF);
                }
                printf(YELLOW "Retornar ao menu? (S/N): " OFF);
                scanf("%c", &returnToMenu);
                buffer();
                menuOption = (returnToMenu == 's') ? -1 : 0;
                break;
            case 2:
                counter = 0;

                for (int i = 0; i < QUANTITY_OF_VEHICLES; i++) {
                    if ((allocations+i)->userId != -1 && (allocations+i)->carId != -1) {
                        counter++;
                    }
                }

                clear();
                do {
                    if (counter == 0) {
                        printf(RED "\n* Nenhum veículo alugado encontrado.\n" OFF);
                        break;
                    }
                    found = 0;

                    printf(BLUE "[ENTREGA DE VEÍCULO]\n" OFF);
                    printf(YELLOW "\nDigite o ID do cliente e ID do carro, respectivamente (# #): " OFF);
                    scanf("%d %d", &userId, &carId);
                    buffer();

                    if (userId < 1 || userId > QUANTITY_OF_USERS || carId < 1 || carId > QUANTITY_OF_VEHICLES) {
                        clear();
                        printf(RED "\n* Dados informados inválidos.\n" OFF);
                        userId = -1;
                        carId = -1;
                    } 
                    
                    if (userId > 0 || carId > 0) {
                        for (int i = 0; i < QUANTITY_OF_USERS; i++) {
                            if ((allocations+i)->userId == userId-1 && (allocations+i)->carId == carId-1) {
                                allocationId = i;
                                found = 1;
                                printf("\n");
                                clear();
                                printRent((allocations+i), users, cars);
                                break;
                            }
                        }
                    }

                    if (found == 0) {
                        clear();
                        printf(RED "\n* Nenhuma relação encontrada, entre novamente com os dados.\n" OFF);

                        printf(YELLOW "\nDeseja visualizar as locações? (S/N): " OFF);
                        scanf("%c", &viewCars);
                        buffer();

                        if (tolower(viewCars) == 's') {
                            clear();

                            printf(YELLOW_F "\n[LISTA DE LOCAÇÕES]\n\n" OFF);
                            for (int i = 0; i < QUANTITY_OF_VEHICLES; i++) {
                                if ((allocations+i)->userId != -1 && (allocations+i)->carId != -1) {
                                    printRent((allocations+i), users, cars);
                                    printf("\n");
                                    counter++;
                                }
                            }
                        }
                    }
                } while (userId == -1 || carId == -1 || found != 1 || counter == 0);
                break;
            case 0:
                exit = 1;
                break;
            default: 
                clear();
                printf(RED "* Selecione um ID válido.\n\n" OFF);
                menuOption = -1;
        }
    } while (menuOption == -1);

    if (exit == 0 && counter > 0) {
        do {
            printf(YELLOW "\nInforme os quilômetros rodados: " OFF);
            scanf("%lf", &km);
            buffer();

            if (km > 0) {
                invalidKm = 0;

                daily = differenceBetween(
                    (allocations+allocationId)->dateEnd,
                    (allocations+allocationId)->dateStart
                );

                if (km > (allocations+allocationId)->maxKm) {
                    excessMileage = km - (allocations+allocationId)->maxKm;
                }
                points = (int) km;

                /* updating points */
                (users+userId-1)->points += points;

                /* reallocating car into list and updating km */
                (cars+carId-1)->isRented = 0;
                (cars+carId-1)->kilometers += km;

                /* allocation reset */
                (allocations+allocationId)->userId = -1;
                (allocations+allocationId)->carId = -1;

                totalToPay = daily * getPriceByCategory((cars+carId-1)->category);
                totalToPay += excessMileage * getPriceKilometerByCategory((cars+carId-1)->category);

                printf(YELLOW_F "\nTotal a pagar:" OFF " " GREEN_U "R$ %.2f\n" OFF, totalToPay);
                
                printf(GREEN "\nDevolução concluída com sucesso!" OFF " ");
                printf(YELLOW_U "\nPontuação do cliente atualizada para %lld pontos.\n" OFF, (users+userId-1)->points);
            } else {
                clear();
                invalidKm = 1;
                printf(RED "\n* Quilometragem inválida.\n" OFF);
            }
        } while (invalidKm == 1);
    }   
}

/* case 3 */
void search(Car *cars) {
    /* options */
    int categoryOption;
    char *category = malloc(50 * sizeof(char));
    char backToCategories;

    /* handlers */
    int attempt = 0;

    clear();
    do {
        Menu: categoryMenu();
        scanf("%d", &categoryOption);
        buffer();

        if (categoryOption < 0 || categoryOption > 5) {
            clear();
            printf(RED "\n* Por favor, escolha uma categoria válida [%d].\n" OFF, ++attempt);
            goto Menu;
        }
        category = categoriesOptions(categoryOption);

        if (strcmp(category, "SAIR") == 0) break;
        clear();

        printCarByCategory(cars, category);

        printf(YELLOW "\nDeseja retornar ao menu de categorias? (S/N): " OFF);
        scanf("%c", &backToCategories);
        buffer();
        clear();
    } while (backToCategories == 's');
}

/* case 4 */
void vehicleReport(Car *cars) {
    clear();
    /* options */
    int menuOption;
    
    /* handlers */
    int attempt = 0;

    do {
        reportMenu();
        scanf("%d", &menuOption);
        buffer();

        clear();

        switch (menuOption) {
            case 1:
                printCars(cars);
                break;
            case 2:
                writeFile(REPORT_FILE, cars);
                break;
            case 0:
                break;
            default:
                clear();
                printf(RED "\n* Por favor, escolha uma opção válida [%d].\n\n" OFF, ++attempt);
                menuOption = -1;
        }
    } while (menuOption == -1);
}