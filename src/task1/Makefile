CC=g++
DEPS=
CFLAGS=-std=c++20 -stdlib=libc++ -I ../../include
LIB=-L ~/lib -lsdsl -ldivsufsort -ldivsufsort64 -lz -lbz2 -pthread 

make: main.o
	$(CC) -o buildsa main.o $(LIB)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o  $@ $<

clean: 
	rm *.o buildsa