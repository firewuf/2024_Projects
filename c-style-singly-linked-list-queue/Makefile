CXX = g++
CXXFLAGS = -Wall -Werror -std=c++20 -I include/ -fsanitize=address

all: hw03_main

hw03_main: lib/player.o lib/llqueue.o lib/futsal.o
	$(CXX) $(CXXFLAGS) src/hw03_main.cpp lib/player.o lib/llqueue.o lib/futsal.o -o lib/hw03_main

lib/player.o: src/player.cpp include/player.h
	$(CXX) $(CXXFLAGS) -c src/player.cpp -o lib/player.o

lib/llqueue.o: src/llqueue.cpp include/llqueue.h
	$(CXX) $(CXXFLAGS) -c src/llqueue.cpp -o lib/llqueue.o

lib/futsal.o: src/futsal.cpp include/futsal.h
	$(CXX) $(CXXFLAGS) -c src/futsal.cpp -o lib/futsal.o

clean:
	rm -f lib/*.o lib/hw03_main