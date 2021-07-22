escalona: graph.o main.o log.o equivalente.o
	gcc -o escalona graph.o main.o erro.o log.o equivalente.o

erro.o: erro.c
	gcc -c erro.c -Wall

log.o: log.c
	gcc -c log.c -Wall

main.o: main.c
	gcc -c main.c -Wall

equivalente.o: equivalente.c
	gcc -c equivalente.c -Wall

graph.o: graph.c erro.o
	gcc -c graph.c -Wall

clean:
	rm -rf *.o escalona logs
	clear
