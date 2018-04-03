all: mygrep

mygrep: main.o lexer.o parser.o checker.o
	g++ -std=c++11 main.o lexer.o parser.o checker.o -o mygrep

main.o: main.cpp checker.h
	g++ -std=c++11 -c main.cpp -o main.o

lexer.o: lexer.cpp lexer.h
	g++ -std=c++11 -c lexer.cpp -o lexer.o

parser.o: parser.cpp parser.h lexer.h
	g++ -std=c++11 -c parser.cpp -o parser.o

checker.o: checker.cpp checker.h parser.h
	g++ -std=c++11 -c checker.cpp -o checker.o

clean:
	rm -rf *.o mygrep
