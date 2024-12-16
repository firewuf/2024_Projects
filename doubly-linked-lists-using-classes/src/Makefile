CXX = g++
CXXFLAGS = -Wall -Werror -std=c++20 -I include/ -fsanitize=address

all: main

main: ../lib/artist.o ../lib/artistList.o ../lib/parse_csv.o
	$(CXX) $(CXXFLAGS) main.cpp ../lib/artist.o ../lib/artistList.o ../lib/parse_csv.o -o ../lib/main

../lib/artist.o: 
	$(CXX) $(CXXFLAGS) -c artist.cpp -o ../lib/artist.o

../lib/artistList.o: 
	$(CXX) $(CXXFLAGS) -c artistList.cpp -o ../lib/artistList.o

../lib/parse_csv.o:
	$(CXX) $(CXXFLAGS) -c parse_csv.cpp -o ../lib/parse_csv.o

clean:
	rm -f lib/*.o lib/hw03_main