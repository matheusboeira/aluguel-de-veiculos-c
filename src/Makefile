# -*- Makefile -*-
all: main.o menu.o user.o vehicle.o utils.o allocation.o
	gcc -o ../out/application main.o menu.o user.o vehicle.o utils.o allocation.o -Wall -Wextra -std=c11
	make clean

menu.o:
	gcc -c menu/menu.c -Wall -Wextra -std=c11

main.o:
	gcc -c main.c -Wall -Wextra -std=c11

user.o:
	gcc -c entities/user.c -Wall -Wextra -std=c11

vehicle.o:
	gcc -c entities/vehicle.c -Wall -Wextra -std=c11

utils.o:
	gcc -c global/utils.c -Wall -Wextra -std=c11

allocation.o:
	gcc -c entities/allocation.c -Wall -Wextra -std=c11

clean:
	rm -f main.o menu.o vehicle.o utils.o user.o allocation.o
