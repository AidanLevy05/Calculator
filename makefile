PROG = prog 
CC = g++
CPPFLAGS = -g -Wall -std=c++11
OBJS = main.o ExpressionTree.o

$(PROG) : $(OBJS) 
	$(CC) -o $(PROG) $(OBJS)

main.o : main.cpp 
	$(CC) $(CPPFLAGS) -c main.cpp 

ExpressionTree.o : ExpressionTree.h ExpressionTree.cpp 
	$(CC) $(CPPFLAGS) -c ExpressionTree.cpp

clean:
	rm -f core $(PROG) $(OBJS) 

rebuild:
	make clean
	make
