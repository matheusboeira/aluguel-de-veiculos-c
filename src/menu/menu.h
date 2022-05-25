#ifndef MENU_H
#define MENU_H

/**
 * This function is responsible for displaying the menu
 * after the program has initialized.
 */
void menu();

/**
 * This function is responsible for displaying the category 
 * of cars in the menu.
 */
void menuCategory();

/**
 * This function is responsible for display a renting vehicles
 * screen. The user will choose the vehicle to rent.
 */
void vehicleRental();

/**
 * This function is responsible for delivering and setting the vehicle
 * to available to be part of the list of 'vehicleRental()'.
 */
void vehicleDelivery();

/**
 * This function is responsible to search a vehicle considering
 * the category and points of the user.
 */
void search();

/**
 * This function is responsible to transform all data of the array
 * of cars into text and output a report file.
 */
void vehicleReport();

#endif