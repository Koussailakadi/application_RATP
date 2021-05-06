CXXFLAGS=-std=c++11 -Wall -Wextra -Werror -g

all: main 

main: main.cpp Grade.o ClassTP1.cpp 
	g++ $(CXXFLAGS) -o projet main.cpp ClassTP1.cpp Grade.o

clean:
	rm main 