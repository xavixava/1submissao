#   Compiler, Compiler Flags

CC = gcc
CFLAGS = -g -Wall  

#   Sources
SOURCES = main.c 

#   Objects  ('make' automatically compiles .c to .o)
OBJECTS = main.o graph.o list.o

aedmaps: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

main.o: main.c graph.h list.h

graph.o: graph.c graph.h list.h 

list.o: list.c list.h

clean:
	rm -f *.o  aedmaps


FILES = $(shell ls ../test/*.txt)

VALG = valgrind --leak-check=full

valgrind: aedmaps
	$(VALG) ./aedmaps

t:
	for F in ${FILES}; do  ./aedmaps $${F} ; done;


tv:
	for F in ${FILES}; do ${VALG} ./aedmaps $${F} ; done;


tt:
	for F in ${FILES}; do  time ./aedmaps $${F} ; done;