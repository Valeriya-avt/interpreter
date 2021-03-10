all: bin/1_arithmetic bin/2_assign

bin:
	mkdir bin

bin/1_arithmetic: home/1_arithmetic.cpp
	g++ home/1_arithmetic.cpp -o bin/1_arithmetic -fsanitize=address,leak

bin/2_assign: home/2_assign.cpp
	g++ home/2_assign.cpp -o bin/2_assign -fsanitize=address,leak

clean:
	rm bin/1_arithmetic bin/2_assign
	rmdir bin

