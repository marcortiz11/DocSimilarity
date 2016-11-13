all: main.cpp
	g++ -std=c++11 main.cpp -o main
clean: main
	rm -f main *.o
