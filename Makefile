all: bin/const.o bin/lexem.o bin/lexical.o bin/syntax.o bin/semantic.o bin/main 

bin:
	mkdir bin

bin/const.o: src/const.cpp
	g++ -I./include -c src/const.cpp -o bin/const.o -fsanitize=address,leak

bin/lexem.o: src/lexem.cpp
	g++ -I./include -c src/lexem.cpp -o bin/lexem.o -fsanitize=address,leak

bin/lexical.o: src/lexical.cpp
	g++ -I./include -c src/lexical.cpp -o bin/lexical.o -fsanitize=address,leak

bin/syntax.o: src/syntax.cpp
	g++ -I./include -c src/syntax.cpp -o bin/syntax.o -fsanitize=address,leak

bin/semantic.o: src/semantic.cpp
	g++ -I./include -c src/semantic.cpp -o bin/semantic.o -fsanitize=address,leak

bin/main: src/main.cpp
	g++ -I./include src/main.cpp bin/const.o bin/lexem.o bin/lexical.o bin/syntax.o bin/semantic.o -o bin/main -fsanitize=address,leak

clean:
	rm bin/const.o bin/lexem.o bin/lexical.o bin/syntax.o bin/semantic.o bin/main
	rmdir bin

