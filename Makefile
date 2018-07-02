CXXFLAGS = -Wall -O3 -I/home/sven/include -I. -g -ggdb
LDFLAGS = -L/home/sven/lib

all: weisfeiler mobius benzene stabilize check-t increase-arity decrease-arity\
	rank
clean:
	rm -f weisfeiler tensor mobius benzene check-t *.o test
test: test.o
	g++ -o test -L/home/sven/lib test.o -lxunit
stabilize: tensor.o tuples.o main.o
	g++ -o stabilize tensor.o tuples.o main.o
check-t: tensor.o tuples.o check-t.o
	g++ -o check-t tensor.o tuples.o check-t.o
increase-arity: tensor.o tuples.o increase-arity.o
	g++ -o increase-arity tensor.o tuples.o increase-arity.o
decrease-arity: tensor.o tuples.o decrease-arity.o
	g++ -o decrease-arity tensor.o tuples.o decrease-arity.o
rank: tensor.o tuples.o rank.o
	g++ -o rank tensor.o tuples.o rank.o
test.o: test.cpp

depend:
	makedepend $(CXXFLAGS) *.cpp
# DO NOT DELETE

check-t.o: ./tensor.h
increase-arity.o: ./tensor.h
main.o: ./tensor.h
tensor.o: ./tensor.h ./collection.h ./tuples.h
test.o: /home/sven/include/xunit.h /home/sven/include/xunit/TestCaseTest.h
test.o: /home/sven/include/xunit/TestCase.h
test.o: /home/sven/include/xunit/TestResult.h
test.o: /home/sven/include/xunit/TestFailure.h
test.o: /home/sven/include/xunit/WasRun.h
test.o: /home/sven/include/xunit/TestSuite.h
tuples.o: ./tuples.h

