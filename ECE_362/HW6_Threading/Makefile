## Makefile for ECE 362 HW6
C = gcc
CFLAGS = -Wall -std=c99 -g
OBJS = Threaddit.o
OBJS2 = thread1.o
LIBS = -lm 

help:
	@echo "Targets: all compile compile2 Tests clean"
	
all: compile compile2  test clean

compile: $(OBJS)
	@$(C) -o Threaddit $(OBJS) $(LIBS) -pthread
	
compile2: $(OBJS2)
	@$(C) -o thread1 $(OBJS2) $(LIBS) -pthread
	
Threaddit.o: Threaddit.c
	@$(C) $(CFLAGS) -c Threaddit.c 
	
thread1.o: thread1.c
	@$(C) $(CFLAGS) -c thread1.c 

test: test1 test2 test3 test4

test1:
	time ./Threaddit -t 8 -s 1
	
test2:
	time ./Threaddit -t 4 -s 1
	
test3:
	time ./Threaddit -t 1 -s 1

test4:
	./thread1 -t 4
	
clean:
	@rm -f $(OBJS) $(OBJS2) Threaddit thread1