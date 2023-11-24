DSSimul: main.o algorithm.o
	gcc -o DSSimul main.o algorithm.o

main.o: main.c algorithm.h
	gcc -c main.c

algorithm.o: algorithm.c algorithm.h
	gcc -c algorithm.c

clean:
	rm -f *.o DSSimul
