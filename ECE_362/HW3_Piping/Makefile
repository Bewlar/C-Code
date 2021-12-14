## Makefile for ECE 362 HW1
C = gcc
CFLAGS = -Wall -std=c99 -g
OBJS = flip.o
OBJS2 = piper.o
LIBS = -lm

help:
	@echo "Targets: all compile clean"

all: compile compile2 clean

compile: $(OBJS)
	@$(C) -o flip $(OBJS) $(LIBS)
	
flip.o: flip.c
	@$(C) $(CFLAGS) -c flip.c
	
compile2: $(OBJS2)
	@$(C) -o piper $(OBJS2) $(LIBS)

clean:
	@rm -f $(OBJS) $(OBJS2) upper.txt lower.txt