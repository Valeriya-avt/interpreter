CXX           = g++
DEL_FILE      = rm
MKDIR         = mkdir
DEL_DIR       = rmdir
FLAGS	      = -c -I./include -fpic -shared -fsanitize=address,leak

all: lib lib/libconst.so bin lib/libvariables.so lib/liblexem.so lib/liblexical.so lib/libsyntax.so lib/libsemantic.so lib/libprint.so bin/main 

lib:
	$(MKDIR) lib

bin:
	$(MKDIR) bin

lib/libconst.so: src/const.cpp
	$(CXX) $? -o $@ $(FLAGS)

lib/libvariables.so: src/variables.cpp
	$(CXX) $? -o $@ $(FLAGS)

lib/liblexem.so: src/lexem.cpp
	$(CXX) $? -o $@ $(FLAGS)

lib/liblexical.so: src/lexical.cpp
	$(CXX) $? -o $@ $(FLAGS)

lib/libsyntax.so: src/syntax.cpp
	$(CXX) $? -o $@ $(FLAGS)

lib/libsemantic.so: src/semantic.cpp
	$(CXX) $? -o $@ $(FLAGS)

lib/libprint.so: src/print.cpp
	$(CXX) $? -o $@ $(FLAGS)

bin/main: src/main.cpp
	$(CXX) $? -I./include -L lib/ -lconst -lvariables -llexem -llexical -lsyntax -lsemantic -lprint -o $@ -fsanitize=address,leak

clean:
	$(DEL_FILE) lib/libconst.so lib/libvariables.so lib/liblexem.so lib/liblexical.so lib/libsyntax.so lib/libsemantic.so lib/libprint.so bin/main
	$(DEL_DIR) lib
	$(DEL_DIR) bin