## Makefile for ECE 361 MLS app (Homework #3)
C = gcc
CFLAGS = -Wall -std=c99 -g
OBJS = MLStree.o MLSapp_Helpers.o test2_MLStree.o
HDRS = MLSapp_Helpers.h MLStree.h

hw3_mls_app : $(OBJS)
	$(C) -o hw3_mls_app $(OBJS)
	
MLStree.o : MLStree.c
	$(C) $(CFLAGS) -c MLStree.c

MLSapp_Helpers.o: MLSapp_Helpers.c
	$(C) $(CFLAGS) -c MLSapp_Helpers.c
	
test2_MLStree.o : test2_MLStree.c
	$(C) $(CFLAGS) -c test2_MLStree.c
	
$(OBJS) : $(HDRS)

clean:
	rm $(OBJS) hw3_mls_app.exe