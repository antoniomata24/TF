
#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -Wall -ansi -std=c99 -O3

#  Sources
SOURCES =  main.c file.c list.c grafs.c oper.c

#  Objects
OBJECTS = main.o file.o list.o grafs.o oper.o

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

grafs.o : grafs.h grafs.c
	$(CC) -O3 -c grafs.c

clean::
	rm -f *.o *.walks core a.out tuktuk *~

depend::
	makedepend $(SOURCES)
# DO NOT DELETE
