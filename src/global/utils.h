#ifndef UTILS_H
#define UTILS_H

/* Colors used */
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define GREEN_B "\033[5;32m"
#define GREEN_U "\033[4;32m"
#define YELLOW "\033[1;33m"
#define YELLOW_U "\033[4;33m"
#define YELLOW_W "\033[2;33m"
#define YELLOW_F "\033[7;33m"
#define BLUE "\033[1;36m"
#define BLUE_U "\033[4;36m"
#define WHITE_U "\033[4;37m"
#define END "\033[7;33m"
#define OFF "\033[0m"

#include <stdio.h>

#include "../entities/headers/user.h"
#include "../entities/headers/vehicle.h"

/**
 * The directory path to access the database files. Note
 * that the reference path is for 'main.c', not in this file.
 */
#define FILE_USERS "../database/users.csv"
#define FILE_VEHICLES "../database/vehicles.csv"

/**
 * The path to write the report file.
 */
#define REPORT_FILE "../out/reports/report.txt"

/**
 * The format of the database files. I'll be responsible for
 * populating the structs with specific format.
 */
#define FILE_FORMAT_USERS "%d;%119[^;];%lld;%lld"
#define FILE_FORMAT_VEHICLES "%d;%9[^;];%49[^;];%49[^;];%d;%lf;%49[^;];%d"

/**
 * Determining the size to use in malloc function.
 */
#define VECTOR_SIZE 100

/**
 * Variable 'date' that'll represent a 
 * date in the format ##/##/####. To set it,
 * call 'setDate()' function.
 */
typedef struct Date {
    int day;
    int month;
    int year;
} Date;

/**
 * Variable 'file' that'll be used to open, read and write files.
 */
extern FILE *file;

/**
 * Variables responsible for storing the first line of the database
 * files. These variables will be used to set an simple iteration 
 * through the data.
 */
extern int QUANTITY_OF_USERS;
extern int QUANTITY_OF_VEHICLES;

/**
 * This functions will be responsible for getting all the data from the
 * database file and put it in a variable with a pointer.
 */
void getUsersFromDatabase(User *users);
void getVehiclesFromDatabase(Car *cars);
void loadDatabases(Car *cars, User *users);

/**
 * Function responsible for reading a database file.
 * 
 * @param filename the filename path
 */
void readFile(char *filename);

/**
 * Function responsible for writing in a file a content passed by parameter.
 * 
 * @param filename the filename path
 * @param content the content to write
 */
void writeFile(char *filename, Car *cars);

/**
 * @brief Set the Date struct
 * 
 * @param day the day
 * @param month the month
 * @param year the year
 * 
 * @return Date return the date 'struct'
 */
Date setDate(int day, int month, int year);

/**
 * Print the date.
 * 
 * @param date the date to print
 */
void printDate(Date date);

/**
 * Get today's date.
 */
Date now();

/**
 * Calculate the difference between two dates and
 * return the days.
 */
long differenceBetween(Date date1, Date date2);

/**
 * Clears the console.
 */
void clear();

/**
 * Handlers input buffer.
 */
void buffer();

#endif