#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "utils.h"

FILE *file;

int QUANTITY_OF_USERS;
int QUANTITY_OF_VEHICLES;

time_t timeA, timeB;
struct tm tA, tB, *tptr;

void readFile(char *filename) {
    file = fopen(filename, "r");
}

void writeFile(char *filename, Car *cars) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    file = fopen(filename, "w");
    fprintf(file, "Relatório gerado em: %02d/%02d/%04d %02d:%02d:%02d\n\n", 
        tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900, tm->tm_hour, tm->tm_min, tm->tm_sec);

    for (int i = 0; i < QUANTITY_OF_VEHICLES; i++) {
        fprintf(file, "[CARRO #%d]:\n", (i + 1));
        fprintf(file, "  ID: %d\n", (cars+i)->id);
        fprintf(file, "  Placa: %s\n", (cars+i)->licensePlate);
        fprintf(file, "  Marca: %s\n", (cars+i)->brand);
        fprintf(file, "  Modelo: %s\n", (cars+i)->model);
        fprintf(file, "  Ano: %d\n", (cars+i)->year);
        fprintf(file, "  Quilometragem: %.2lf Km\n", (cars+i)->kilometers);
        fprintf(file, "  Categoria: %s\n", (cars+i)->category);
        fprintf(file, "  Alugado: ");
        (cars+i)->isRented == 1 ? fprintf(file, "Sim\n\n") : fprintf(file, "Não\n\n");
    }
    fclose(file);

    printf("\n\033[1;32m> Relatório gerado com sucesso!\033[0m\n");
}

void getUsersFromDatabase(User *users) {
    readFile(FILE_USERS);
    
    fscanf(file, "%d", &QUANTITY_OF_USERS);

    for (int i = 0; i < QUANTITY_OF_USERS; i++) {
        fscanf(file, FILE_FORMAT_USERS,
            &(users+i)->id, 
            (users+i)->name, 
            &(users+i)->cnh,
            &(users+i)->points);
    }
    fclose(file);
}

void getVehiclesFromDatabase(Car *cars) {
    readFile(FILE_VEHICLES);
    
    fscanf(file, "%d", &QUANTITY_OF_VEHICLES);

    for (int i = 0; i < QUANTITY_OF_VEHICLES; i++) {
        fscanf(file, FILE_FORMAT_VEHICLES,
            &(cars+i)->id,
            (cars+i)->licensePlate,
            (cars+i)->brand,
            (cars+i)->model,
            &(cars+i)->year,
            &(cars+i)->kilometers,
            (cars+i)->category,
            &(cars+i)->isRented);
    }
    fclose(file);
}

void loadDatabases(Car *cars, User *users) {
    getVehiclesFromDatabase(cars);
    getUsersFromDatabase(users);
}

Date setDate(int day, int month, int year) {
    Date date;

    date.day = (day > 0 && day <= 31) ? day : now().day;
    date.month = (month > 0 && month <= 12) ? month : now().month;
    date.year = (year > 0) ? year : now().year;
    
    return date;
}

void printDate(Date date) {
    printf("%02d/%02d/%04d", date.day, date.month, date.year);
}

Date now() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    Date now;
    now.day = tm->tm_mday;
    now.month = tm->tm_mon + 1;
    now.year = tm->tm_year + 1900;
    return now;
}

long differenceBetween(Date date1, Date date2) {
    struct tm d = { 0 }, dd = { 0 };
    long days;

    dd.tm_year = date1.year - 1900; /* years since 1900 */
    dd.tm_mon = date1.month;
    dd.tm_mday = date1.day;
 
    d.tm_year = date2.year - 1900;
    d.tm_mon = date2.month;
    d.tm_mday = date2.day;

    days = difftime(mktime(&dd), mktime(&d)) / 86400;
    return days;
}

void clear() {
    system("cls||clear");
}

void buffer() {
    fflush(stdin);
}
