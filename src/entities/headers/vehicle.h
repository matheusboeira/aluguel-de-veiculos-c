#ifndef VEHICLE_H
#define VEHICLE_H

typedef struct Car {
    int id;
    char licensePlate[10];
    char brand[50];
    char model[50];
    int year;
    double kilometers;
    char category[50];
    int isRented;
} Car;

/**
 * Counting vehicles by category to make sure that
 * has cars to rent.
 */
extern int vehiclesByCategory;

/**
 * Print a representation of a car.
 */
void printCar(Car *car);

/**
 * Get actual price of a specified category.
 */
double getPriceByCategory(char *category);

/**
 * Get actual kilometer price value by category. I'll be used
 * to calculate the excess mileage.
 */
double getPriceKilometerByCategory(char *category);

/**
 * Get actual max kilometers of a specified category.
 */
double getMaxKmByCategory(int categoryOption);

/**
 * Print all cars that has part of the particular 
 * category requested, considering if it's not rented.
 * 
 * @param cars an array of cars
 * @param category category to search for
 */
void printCarByCategory(Car *cars, char *category);

/**
 * Print a 'list' of cars. 
 * 
 * @param cars an array with all cars stored
 */
void printCars(Car *cars);

#endif