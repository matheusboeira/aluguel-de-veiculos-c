#ifndef USER_H
#define USER_H

typedef struct User {
    int id;
    char name[50];
    long long cnh;
    long long points;
} User;

/**
 * Check if the user exists. If yes, return the position
 * of the user in the array. If not, return -1.
 * 
 * @param users the users to check in database
 */
int getUser(User *users, long long cnh);

#endif