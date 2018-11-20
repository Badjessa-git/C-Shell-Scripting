CFLAGS=-g -Wall -Wextra -Wwrite-strings
LFLAGS=-g

bib: bib.o bibFuncs.o
	gcc ${LFLAGS} -o bib bib.o bibFuncs.o

bibFuncs.o: bibFuncs.c bibFuncs.h
	gcc ${CFLAGS} -c bibFuncs.c

bib.o: bib.c
	gcc ${CFLAGS} -c bib.c

clean:	
	rm -f ./*.o
	rm -f ./*~