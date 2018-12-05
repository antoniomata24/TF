
#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -Wall -ansi -std=c99 -g

#  Sources
SOURCES =  main.c file.c list.c grafs.c oper.c

#  Objects
OBJECTS = main.o file.o list.o grafs.o oper.o

%.o: %.c

tuktuk: $(OBJECTS)
	$(CC) -g -o $@ $(OBJECTS)

main.o: define.h main.c
	$(CC) -g -c main.c
file.o: file.h file.c
	$(CC) -g -c file.c
list.o : list.h list.c
	$(CC) -g -c list.c
oper.o : oper.h oper.c
	$(CC) -g -c oper.c

grafs.o : grafs.h grafs.c
	$(CC) -g -c grafs.c

clean::
	rm -f *.o *.walks core a.out tuktuk *~

depend::
	makedepend $(SOURCES)
# DO NOT DELETE
