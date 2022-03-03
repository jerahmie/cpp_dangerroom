CPP=g++
CPPFLAGS=-Wall -Werror -O2


.PHONY: all
all: prob1 prob2

prob1: hello_world.cpp
	$(CPP) $(CPPFLAGS) -o prob1 hello_world.cpp

prob2: product.cpp
	$(CPP) $(CPPFLAGS) -o prob2 product.cpp

prob3: euclidean_norm.cpp
	$(CPP) $(CPPFLAGS) -o prob3 euclidean_norm.cpp

.PHONY: clean

clean:
	rm -f prob1 prob2 prob3
