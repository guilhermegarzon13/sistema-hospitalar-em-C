all: main.o lista.o triagem.o historico.o IO.o
	gcc main.o lista.o triagem.o historico.o IO.o -o programa -std=c99 -Wall


main.o: main.c
	gcc -c main.c -o main.o -std=c99 -Wall

lista.o: lista.c
	gcc -c lista.c -o lista.o -std=c99 -Wall

triagem.o: triagem.c
	gcc -c triagem.c -o triagem.o -std=c99 -Wall

historico.o: historico.c
	gcc -c historico.c -o historico.o -std=c99 -Wall

IO.o: IO.c
	gcc -c IO.c -o IO.o -std=c99 -Wall


run: all
	./programa

clean:
	rm -f main.o lista.o triagem.o historico.o IO.o programa
