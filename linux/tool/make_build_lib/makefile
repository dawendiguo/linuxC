all:main

LIB=libmylib.a
CC=gcc
CFLAGS= -g 

main: main.o $(LIB)
	$(CC) -o main main.o -L. -lmylib
.c.o:
	$(CC) $(CFLAGS) -c $(@D)/$(<F) -o $(@D)/$(@F)
$(LIB):lib1/say1.o lib2/say2.o lib3/say3.o
	ar -rv $(LIB) $?
