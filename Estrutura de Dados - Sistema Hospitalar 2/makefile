all: programa

programa: main.o AVL.o heap.o IO.o
	gcc main.o AVL.o heap.o IO.o -o programa -std=c99 -Wall

main.o: main.c dados.h AVL.h heap.h IO.h
	gcc -c main.c -o main.o -std=c99 -Wall

AVL.o: AVL.c AVL.h dados.h
	gcc -c AVL.c -o AVL.o -std=c99 -Wall

heap.o: heap.c heap.h dados.h
	gcc -c heap.c -o heap.o -std=c99 -Wall


IO.o: IO.c IO.h AVL.h heap.h dados.h
	gcc -c IO.c -o IO.o -std=c99 -Wall

run: programa
	./programa

clean:
	rm -f main.o AVL.o heap.o IO.o programa
