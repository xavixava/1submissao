#	$(foreach file,$(FILES),./labconn $(file);)
# https://stackoverflow.com/questions/1490949/how-to-write-loop-in-a-makefile
#----------------------------------------------------------------------
#   Compiler, Compiler Flags

CC = gcc
CFLAGS = -g -Wall  

#   Sources
SOURCES = main.c 

#   Objects  ('make' automatically compiles .c to .o)
OBJECTS = main.o graph.o list.o

proj: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

main.o: main.c graph.h main.h list.h

graph.o: graph.c graph.h list.h defs.h

list.o: list.c list.h

clean:
	rm -f *.o  proj


FILES = $(shell ls ../test/*.txt)

VALG = valgrind --leak-check=full

valgrind: proj
	$(VALG) ./proj

t:
	for F in ${FILES}; do  ./proj $${F} ; done;


tv:
	for F in ${FILES}; do ${VALG} ./proj $${F} ; done;


tt:
	for F in ${FILES}; do  time ./proj $${F} ; done;