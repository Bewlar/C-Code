## Makefile for ECE 362 HW2
C = gcc
CFLAGS = -Wall -std=c99 -g
OBJS = Select.o
OBJS2 = Capture.o
LIBS = -lm

help:
	@echo "Targets: all compile compile2 clean"

all: compile compile2 clean

compile: $(OBJS)
	@$(C) -o Select $(OBJS) $(LIBS)

Select.o: Select.c
	@$(C) $(CFLAGS) -c Select.c

compile2: $(OBJS2)
	@$(C) -o Capture $(OBJS2) $(LIBS)
	
Capture.o: Capture.c
	@$(C) $(CFLAGS) -c Capture.c

clean:
	@rm -f $(OBJS) $(OBJS2) Select Capture