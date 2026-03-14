main: main.o
	g++ main.cpp -o main

clean:
	rm -rf *o main
