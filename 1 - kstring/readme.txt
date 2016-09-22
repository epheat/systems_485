Evan Heaton - ephe223@g.uky.edu
2/9/2016
CS485G:006 - Systems Programming
Programming Assignment 1: http://cs.uky.edu/~neil/485/pa/1/

CONTENTS:
	- kstring.h
		kstring header file: prototypes all functions to be implemented by kstring.c
	- kstring.c
		implements all functions prototyped in kstring.h
	- Makefile
		a makefile for compiling the program into ./test-abbrev and ./test-full : use make memcheck to check for memory leaks and such
	- readme.txt
		this file
	- test-abbrev.c
		for the abbreviated test
	- test-full.o
		the full test file
	- script.txt
		a text document showing the use of the program : namely, running the memcheck operation 

RUNNING:
	To run the test programs, use ./test-abbrev or ./test-full. To run with memory checking active use make memcheck, which will run the test automatically while also checking for memory leaks.

IMPLEMENTATION NOTES:
	Most of the decisions I made are outlined in the comments of kstring.c
	I used no extra helper functions

LIMITATIONS:
	My kstring class has no limitations because it is baller. It leaves no room for memory leaks, and it is as optimal as I could think of.

REFERENCES:
	http://en.cppreference.com/w/c/memory/malloc
	http://en.cppreference.com/w/c/memory/free
	http://en.cppreference.com/w/c/memory/realloc
	for obvious reasons


