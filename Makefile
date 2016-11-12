all: main.cpp
	g++ main.cpp -o main
clean: main
	rm -f main *.o
