CXXFLAGS=-std=c++11 -Wall -Wextra -Werror -g

all: main 

main: main.cpp Grade.o RATP.cpp  RATP.hpp
	g++ -c RATP.cpp -o RATP.o 
	g++ -c main.cpp -o main.o 
	g++ -o projet RATP.o main.o Grade.o

clean:
	rm main 