
repair: all
	g++ -o repair main.o solUno.o MaxHeap.o LinkedList.o iterator.o controller.o

all:
	g++ -c src/controller/*.cpp
	g++ -c src/LinkedList/*.cpp
	g++ -c src/solDos/*.cpp
	g++ -c src/solUno/*.cpp
	g++ -c src/main.cpp