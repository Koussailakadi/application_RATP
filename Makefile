CXXFLAGS=-std=c++11 -Wall -Wextra -Werror -g

all: main 

main: main.cpp Grade.o RATP.cpp 
	g++ $(CXXFLAGS) -o projet main.cpp RATP.cpp Grade.o

clean:
	rm main 