CXXFLAGS = -Wall -pedantic -Wextra -pedantic-errors -DNDEBUG
CXXFLAGS_DEBUG = -Wall -pedantic -Wextra -pedantic-errors -g

BASIC_FLAGS = -DNDEBUG

main.exe: main.o
	g++ $(BASIC_FLAGS) main.o -o main.exe

main.o: main.cpp
	g++ $(BASIC_FLAGS) -c main.cpp -o main.o

.PHONY: clean release rebuild doc debug run_valgrind

clean:
	rm -f *.exe *.o

release:
	g++ $(CXXFLAGS) -c main.cpp -o main.o
	g++ $(CXXFLAGS) main.o -o main.exe

doc: 	
	doxygen Doxyfile

rebuild: clean release

debug: 
	g++ $(CXXFLAGS_DEBUG) -c main.cpp -o main.o
	g++ $(CXXFLAGS_DEBUG) main.o -o main.exe

run_valgrind: debug
	valgrind --leak-check=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -v ./main.exe