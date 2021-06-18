main: main.c MyLib.o
	gcc main.c ./lib/*.o -I ./include -o main 

MyLib.o: ./src/functions.c
	gcc -c ./src/functions.c -I ./include -o ./lib/MyLib.o

.PHONY:
clean:
	rm -rf ./lib/*
	rm -rf main