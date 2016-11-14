all: main.cpp Shingles.cpp
	g++ -std=c++11 -o main.o main.cpp Shingles.cpp

test_all: test_docstore test_shinglestream

test_docstore:
	g++ -std=c++11 -o test/test_docstore test/test_docstore.cpp docstore.cpp
	./test/test_docstore

test_shinglestream:
	g++ -std=c++11 -o test/test_shinglestream test/test_shinglestream.cpp docstore.cpp shinglestream.cpp
	./test/test_shinglestream

clean:
	rm -f *.o
