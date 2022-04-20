CC=g++
DEPS=rank_support.h 
CFLAGS=-std=c++20 -stdlib=libc++ -I ~/include 
LIB=-L ~/lib -lsdsl -ldivsufsort -ldivsufsort64

make: main.o rank_support.o
	$(CC) -o rank.exe main.o rank_support.o $(LIB)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o  $@ $<

clean: 
	rm *.o rank.exe