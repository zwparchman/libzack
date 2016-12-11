OFLAGS =  -O3
CC=g++
STD=-std=c++14
CFLAGS= -g -c -W -Wall -Wextra $(STD) -Wno-missing-field-initializers -Wshadow \
				$(OFLAGS) -I.
LFLAGS= -g $(STD) $(OFLAGS) -pthread -L.

.PHONY:clean 

Objects= main.o
SObjects= Timer.o


all : libzacklib.so program libzacklib.a visual_color_test

visual_color_test: build_color.py color_main.cpp
	gcc color_main.cpp -o visual_color_test

color.h: build_color.py
	./build_color.py > color.h

libzacklib.so : $(SObjects)  *hpp
	$(CC) -fpic -shared $(LFLAGS) -olibzacklib.so Timer.o

libzacklib.a: $(SObjects) *hpp
	ar r libzacklib.a $(SObjects)

Timer.o : Timer.cpp Timer.hpp
	$(CC) -fpic $(CFLAGS) Timer.cpp

program: $(Objects) $(SObjects) libzacklib.so *hpp *cpp
	$(CC) $(LFLAGS) -o program $(Objects) -L. -lzacklib /home/zack/src/googletest/googletest/build/libgtest.a

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

clean:
	rm -f *o 
	rm -f program
	rm -f c*grind\.out\.*

