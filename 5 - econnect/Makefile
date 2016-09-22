#Evan Heaton
#Program 5
#eclient / eserver

CC = gcc
CXX = g++
CFLAGS=-O2 -Wall
LDLIBS = -pthread

all: eclient eserver

eclient: eclient.o helpers.o csapp.o parser.o
	$(CXX) $(CFLAGS) $(LDLIBS) eclient.o parser.o helpers.o csapp.o -o eclient
eserver: eserver.o helpers.o csapp.o parser.o
	$(CXX) $(CFLAGS) $(LDLIBS) eserver.o parser.o helpers.o csapp.o -o eserver

#rules for compiling
csapp.o: csapp.c csapp.h
	$(CC) $(CFLAGS) $(LDLIBS) csapp.c -c -o csapp.o 
parser.o: parser.c parser.h
	$(CC) $(CFLAGS) $(LDLIBS) parser.c -c -o parser.o
helpers.o: helpers.cpp helpers.h csapp.h parser.h
	$(CXX) $(CFLAGS) $(LDLIBS) helpers.cpp -c -o helpers.o
eclient.o: eclient.cpp helpers.h csapp.h
	$(CXX) $(CFLAGS) $(LDLIBS) eclient.cpp -c -o eclient.o
eserver.o: eserver.cpp helpers.h csapp.h
	$(CXX) $(CFLAGS) $(LDLIBS) eserver.cpp -c -o eserver.o



clean:
	rm -rf *~ eclient eserver *.o

zip:
	zip ./Backups/econnect *.txt *.cpp *.c *.h Makefile
