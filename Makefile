all: main.cpp Shingles.cpp
	g++ -std=c++11 -o main main.cpp Shingles.cpp
clean: main
	rm -f main *.o
