CXXFLAGS=-Wall -Wextra -Werror -g

all: main 

main: main.cpp 
	g++ $(CXXFLAGS) -o projet main.cpp ClassTP1.cpp ClassTP1.hpp Grade2019_ 820.o

clean:
	rm main