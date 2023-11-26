DSSimul: main.o algorithms.o
	gcc -o DSSimul main.o algorithms.o

mains.o: main.c
	gcc -c main.c

algorithms.o: algorithms.c
	gcc -c algorithms.c

clean:
	rm -f *.o DSSimul
