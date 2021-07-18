escalona: graph.o main.o
	gcc -o escalona graph.o main.o erro.o

erro.o: erro.c
	gcc -c erro.c -Wall

main.o: main.c
	gcc -c main.c -Wall

graph.o: graph.c erro.o
	gcc -c graph.c -Wall

clean:
	rm -rf *.o escalona
	clear