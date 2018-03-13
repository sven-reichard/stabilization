CXXFLAGS = -Wall -O3 -I/home/sven/include
LDFLAGS = -L/home/sven/lib

all: test weisfeiler mobius benzene
	./test
clean:
	rm -f weisfeiler mobius benzene *.o test
test: test.o
	g++ -o test -L/home/sven/lib test.o -lxunit
test.o: test.cpp
