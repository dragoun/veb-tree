CC = g++
CXXFLAGS += -g -Wall -pedantic

all: test

test: test.o veb.o
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $<

.PHONY: clean cleanest

clean:
	rm -f *.o

cleanest: clean
	rm -f test

test.o: test.cpp
veb.o: veb.cpp veb.hpp
