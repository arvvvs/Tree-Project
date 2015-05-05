COMPILER = g++
FLAGS = -g -std=c++0x
OUT = execute

all: AVLTree.o Driver.o
	$(COMPILER) $(FLAGS) AVLTree.o Driver.o -o $(OUT)

AVLTree.o: AVLTree.cpp
	$(COMPILER) $(FLAGS) -c AVLTree.cpp

Driver.o: Driver.cpp
	$(COMPILER) $(FLAGS) -c Driver.cpp

clean:
	rm *.o $(OUT)
