#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../global/utils.h"
#include "headers/user.h"

int getUser(User *users, long long cnh) {
    for (int i = 0; i < QUANTITY_OF_USERS; i++) {
        if ((users+i)->cnh == cnh) {
            return i;
        }
    }
    return -1;
}
