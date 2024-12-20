PROG = prog 
CC = g++
CPPFLAGS = -fopenmp -Wall -std=c++11
OBJS = main.o ExpressionTree.o sine.o cosine.o tan.o

$(PROG) : $(OBJS) 
	$(CC) $(CPPFLAGS) -o $(PROG) $(OBJS)

main.o : main.cpp Headers.h
	$(CC) $(CPPFLAGS) -c main.cpp 

ExpressionTree.o : ExpressionTree.h ExpressionTree.cpp Headers.h
	$(CC) $(CPPFLAGS) -c ExpressionTree.cpp

sine.o : sine.h sine.cpp Headers.h
	$(CC) $(CPPFLAGS) -c sine.cpp

cosine.o : cosine.h cosine.cpp Headers.h 
	$(CC) $(CPPFLAGS) -c cosine.cpp

tan.o : tan.h tan.cpp Headers.h 
	$(CC) $(CPPFLAGS) -c tan.cpp

clean:
	rm -f core $(PROG) $(OBJS) 

rebuild:
	make clean
	make