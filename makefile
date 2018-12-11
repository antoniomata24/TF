#
#  File name: makefile
#
#  Author: Rafael Abranches, 90174
#					 António Mata, 90022
#
#  Release date: 2018/12/11
#
#  Description: Makefile for the program tuktuk
#
#  Usage:
#     1) To generate the executable file for the program tuktuk,
#       run
#         $ make
#
#     2) To clean all object files and the executable file of tuktuk,
#        run
#         $ make clean
#

#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -Wall -ansi -std=c99 -O3

#  Sources
SOURCES =  main.c file.c list.c heap.c oper.c

#  Objects
OBJECTS = main.o file.o list.o heap.o oper.o

%.o: %.c

tuktuk: $(OBJECTS)
	$(CC) -O3 -o $@ $(OBJECTS)

main.o: define.h main.c
	$(CC) -O3 -c main.c
file.o: file.h file.c
	$(CC) -O3 -c file.c
list.o : list.h list.c
	$(CC) -O3 -c list.c
oper.o : oper.h oper.c
	$(CC) -O3 -c oper.c

heap.o : heap.h heap.c
	$(CC) -O3 -c heap.c

clean::
	rm -f *.o core a.out tuktuk *~

depend::
	makedepend $(SOURCES)
# DO NOT DELETE
