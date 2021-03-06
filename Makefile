all: mainJaccard mainSignatures mainLHS

test_all: test_shuffler test_jaccard test_docstore test_shinglestream

mainJaccard:
	g++ -std=c++11 -o mainJaccard.o mainJaccard.cpp jaccard.cpp docstore.cpp shinglestream.cpp

mainLHS:
	g++ -std=c++11 -o mainLHS.o mainLHS.cpp jaccard.cpp docstore.cpp shinglestream.cpp Signatures.cpp shuffler.cpp

mainSignatures:
	g++ -std=c++11 -o mainSignatures.o mainSignatures.cpp jaccard.cpp docstore.cpp shinglestream.cpp Signatures.cpp shuffler.cpp

test_signature:
	g++ -std=c++11 -o test/test_signatures.o test/test_signatures.cpp Signatures.cpp shuffler.cpp jaccard.cpp shinglestream.cpp
	./test/test_signatures.o

test_shuffler:
	g++ -std=c++11 -o test/test_shuffler.o test/test_shuffler.cpp shuffler.cpp
	./test/test_shuffler.o

test_jaccard:
	g++ -std=c++11 -o test/test_jaccard.o test/test_jaccard.cpp jaccard.cpp
	./test/test_jaccard.o

test_docstore:
	g++ -std=c++11 -o test/test_docstore.o test/test_docstore.cpp docstore.cpp
	./test/test_docstore.o

test_shinglestream:
	g++ -std=c++11 -o test/test_shinglestream.o test/test_shinglestream.cpp docstore.cpp shinglestream.cpp
	./test/test_shinglestream.o

clean:
	find . -type f -name '*.o' -delete
