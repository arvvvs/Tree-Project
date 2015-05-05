COMPILER = g++
FLAGS = -g -std=c++0x
OUT = execute

all: btree.o Driver.o
	$(COMPILER) $(FLAGS) btree.o driver.o -o $(OUT)

btree.o: btree.cpp
	$(COMPILER) $(FLAGS) -c btree.cpp

Driver.o: driver.cpp
	$(COMPILER) $(FLAGS) -c driver.cpp

clean:
	rm *.o $(OUT)
