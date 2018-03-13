CXXFLAGS = -Wall -O3 -I$(HOME)/include
LDFLAGS = -L$(HOME)/lib

all: test weisfeiler mobius benzene
	./test
clean:
	rm -f weisfeiler mobius benzene
test: test.o
	g++ -o test -L$(HOME)/lib test.o -lxunit
test.o: test.cpp
