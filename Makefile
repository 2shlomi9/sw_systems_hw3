CC = gcc
FLAGS= -g -Wall

all: StrList

StrList: StrList.o Main.o
	$(CC) $(FLAGS)  StrList.o Main.o -o StrList
StrList.o: StrList.c StrList.h
	$(CC) $(FLAGS) -fPIC -c StrList.c
Main.o: Main.c StrList.h
	$(CC) $(FLAGS) -c Main.c
StrList.a: StrList.o 
	ar -rcs StrList.a StrList.o 

.PHONY: clean all
clean:
	rm -f *.o *.a StrList
