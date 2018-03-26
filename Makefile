CXXFLAGS = -Wall -O3 -I/home/sven/include -g -ggdb
LDFLAGS = -L/home/sven/lib

all: test weisfeiler mobius benzene tensor
	./test
clean:
	rm -f weisfeiler tensor mobius benzene *.o test
test: test.o
	g++ -o test -L/home/sven/lib test.o -lxunit
test.o: test.cpp
