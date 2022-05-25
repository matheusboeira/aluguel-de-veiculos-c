#ifndef ALLOCATION_H
#define ALLOCATION_H

#include "user.h"
#include "vehicle.h"
#include "../../global/utils.h"

typedef struct Allocation {
    int userId;
    int carId;
    Date dateStart;
    Date dateEnd;
    double maxKm;
} Allocation;

/**
 * Print a representation of a car rented.
 */
void printRent(Allocation *allocation, User *users, Car *cars);

/**
 * This function will calculate the days between
 * 'now' and a date specified and print in stdout.
 */
void periodAllocation(Date date);

/**
 * Initiliazing the allocation array.
 */
void initializeRenting(Allocation *allocation);

#endif