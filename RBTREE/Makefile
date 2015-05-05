all: submission
CC = g++
CFLAGS =-std=c++11 -Wall -Wextra -g 
all: submission
submission: Driver.o rbtree.o
	$(CC) $(CFLAGS) rbtree.o Driver.o -o submission
Driver.o: Driver.cpp
	$(CC) $(CFLAGS) -c Driver.cpp -o Driver.o
rbtree.o: rbtree.cpp rbtree.h
	$(CC) $(CFLAGS) -c rbtree.cpp -o rbtree.o
clean:
	rm *.o core submission *~ 

