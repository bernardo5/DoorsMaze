doorsmaze: main.o funcoes.o filasListas.o ficheiro.o heap.o
	gcc -g -Wall -ansi -pedantic -o doorsmaze heap.o ficheiro.o filasListas.o funcoes.o main.o

main.o: main.c estruturas.h heap.h funcoes.h ficheiro.h
	gcc -g -Wall -ansi -pedantic -c main.c

funcoes.o: funcoes.c estruturas.h heap.h filasListas.h funcoes.h
	gcc -g -Wall -ansi -pedantic -c funcoes.c

filasListas.o: filasListas.c estruturas.h filasListas.h ficheiro.h
	gcc -g -Wall -ansi -pedantic -c filasListas.c

ficheiro.o: ficheiro.c estruturas.h ficheiro.h
	gcc -g -Wall -ansi -pedantic -c ficheiro.c

heap.o: heap.c estruturas.h heap.h
	gcc -g -Wall -ansi -pedantic -c heap.c

clean:
	rm -f *.o *.~ doorsmaze *.gch
