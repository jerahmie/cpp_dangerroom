# Makefile for cuberoot
#
CC=gcc
CPP=g++
CPPFLAGS=-I. -Wall -O2 -fPIC
CCFLAGS= -fPIC
DEPS = cuberoot.h

all: cuberoot_main libcuberoot.so


%.o: %.cpp $(DEPS)
	$(CPP) -c -o $@ $< $(CPPFLAGS)

cuberoot_main.o: cuberoot_main.cpp
	$(CPP) -c -o $@ $^ $(CPPFLAGS)

cuberoot_main: cuberoot.o cuberoot_main.o
	$(CPP) -o cuberoot_main cuberoot.o cuberoot_main.o

libcuberoot.so: cuberoot.o
	$(CC) -shared -o $@ $^ $(CCFLAGS)

.PHONY: clean
clean:
	rm -r *.o cuberoot_main libcuberoot.so
