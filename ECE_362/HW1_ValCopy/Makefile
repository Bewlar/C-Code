## Makefile for ECE 362 HW1
C = gcc
CFLAGS = -Wall -std=c99 -g
OBJS = val.o
LIBS = -lm

help:
	@echo "Targets: all compile test clean"

all: compile test clean

compile: $(OBJS)
	@$(C) -o val $(OBJS) $(LIBS)
	

val.o: val.c
	@$(C) $(CFLAGS) -c val.c


test: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10

test1:
	@echo "Test1";
	./val 1 2 3 4 5
	
test2:
	@echo "Test2";
	./val -m 4 5 6
	
test3:
	@echo "Test3";
	./val -m 5 potato

test4:
	@echo "Test4";
	./val 1 2 3 4 5
	
test5:
	@echo "Test5";
	./val 4 5ff 6
	
test6:
	@echo "Test6";
	./val 5 potato
	
test7:
	@echo "Test7";
	./val -m 5 0 5f

test8:
	@echo "Test8";
	./val 1
	
test9:
	@echo "Test 9";
	./val -m f5 0 5

test10:
	@echo "Test 10";
	./val f5 0 5

clean:
	@rm -f $(OBJS) val