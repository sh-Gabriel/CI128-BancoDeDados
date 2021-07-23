escalona: graph.o main.o log.o output.o equivalente.o
	gcc -o escalona graph.o main.o erro.o log.o output.o equivalente.o -lm

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

output.o: output.c graph.o erro.o
	gcc -c output.c -Wall

clean:
	rm -rf *.o escalona logs
	clear
