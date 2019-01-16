# ------------------------------------------------------------
# Makefile: Makefile for Lab 1
#   author: Luke Slevinsky, 1453199
#
# Usage: make  // compiles the program
# 			 make debug 	 // compiles the program with a debug flag for gdb
#				 make sanitize // compiles the program with thread sanitization flags
#        make tar   	 // create a 'tar.gz' archive of 'allFiles'
#        make scp   	 // send '$(target).tar.gz' by scp to 'scpDir'
#        make clean 	 // remove unneeded files
# ------------------------------------------------------------

target :=		submit
allFiles := Makefile main.c lab1_IO.c lab1_IO.h matrixgen.c serialtester.c timer.h
objects :=
headers := lab1_IO.h timer.h
scpDir :=		lslevins@um23.cs.ualberta.ca:Documents/Cmput-379/Assignment-4/
CFLAGS :=  -Wall
threadSan := -fsanitize=thread -g
LDFLAGS= -pthread -lpthread
DEBUGFLAG := -g
CC := gcc
# ------------------------------------------------------------


default:  $(objects) $(headers)  main.o lab1_IO.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o matrixmultiplier lab1_IO.o main.o

matrixgen: matrixgen.o
	$(CC) $(CFLAGS) $(DEBUGFLAG) -o matrixgen matrixgen.o

serialtester: serialtester.o lab1_IO.o
	$(CC) $(CFLAGS) $(DEBUGFLAG) -o serialtester lab1_IO.o serialtester.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

serialtester.o: serialtester.c
	$(CC) $(CFLAGS) -c serialtester.c

matrixgen.o: matrixgen.c
	$(CC) $(CFLAGS) -c matrixgen.c

lab1_IO.o: lab1_IO.c
	$(CC) $(CFLAGS) lab1_IO.c -c

clean:
	rm *.o matrixmultiplier matrixgen serialtester
