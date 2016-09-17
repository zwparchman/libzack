OFLAGS =  -O3
CC=g++
STD=-std=c++14
CFLAGS= -g -c -W -Wall -Wextra $(STD) -Wno-missing-field-initializers -Wshadow \
				$(OFLAGS) -I. -isystem ./googletest/googletest/include
LFLAGS= -g $(STD) $(OFLAGS) -pthread -L.

.PHONY:clean 

Objects= main.o
SObjects= Timer.o


all : libzacklib.so program

libzacklib.so : $(SObjects) 
	$(CC) -fpic -shared $(LFLAGS) -olibzacklib.so Timer.o

Timer.o : Timer.cpp Timer.hpp
	$(CC) -fpic $(CFLAGS) Timer.cpp

program: $(Objects) $(SObjects) libzacklib.so *hpp *cpp libgtest.a
	$(CC) $(LFLAGS) -o program $(Objects) -L. -lzacklib libgtest.a

$(Objects): %.o: %.cpp
	$(CC) $(CFLAGS) $<

dbg: program
	gdb program

run: program
	./program

time: program
	time ./program

cache: program
	rm c*grind* -f
	valgrind --tool=cachegrind ./program

call: program
	rm c*grind* -f
	valgrind --tool=callgrind ./program

inspect: 
	kcachegrind c*grind\.out\.*

libgtest.a:
	( cd googletest/googletest && \
	cmake . && \
	make && \
	cp libgtest.a ../../ )

clean:
	rm -f *o 
	rm -f program
	rm -f c*grind\.out\.*

