Author: Evan Heaton
Date Completed: 04/26/2016
econnect: an rrsh server/client combo

Contents:
	Makefile - a file used to compile the executables
	README.txt - this file
	
	csapp.h - header file for the unix-system wrapper functions
	csapp.c - implementation for the unix-system wrapper functions

	parser.h - header file for the command struct and parse_command functions
	parser.c - implementation for the command struct and parse_command functions
	
	helpers.h - header file for helper functions, namely login() and commands()
	helpers.cpp - implementation for helper functions, namely login() and commands()

	eclient.cpp - implementation for the rrsh client
	eserver.cpp - implementation for the rrsh server

	rrshusers.txt - a list of approved users and passwords
	rrshcommands.txt - a list of approved commands that may be used on the server

Running:
	To compile the client and server executables, type 'make'
	To run the server executable, type ./eserver <port>
	To run the client executable, type ./eclient <IP> <port>

Implementation Notes:
	Many of the file scanning portions of code use a classic
	> while (instream >> string) {} formula. This is a great way to scan through entire files until there is nothing left.
	The command Kappa is implemented in addition to the conventional /bin/* commands as listed in the file rrshcommands.txt
	
	
Limitations:
	The server has trouble dealing with empty inputs. Never leave the Username or Password fields empty when sending them from the client. Also, never send only whitespace as a command to the server.
	Because of the way the username and password parsing was implemented, neither of the fields may contain whitespace.
	It is inherently dangerous to store usernames and passwords in plain text as done in this program. An encrypted connection is necessary to ensure the safety of both the machine running the server and also the machine running the client.

References:
	http://www.cplusplus.com/forum/general/71787/ : Include Guards
	https://www.cs.umd.edu/class/fall2002/cmsc214/Tutorial/makefile.html : Makefile

	I worked with Zack Arnett frequently on this programming assignment. Together we solved the problem I was having where the Username and Password were not sending correctly.

	Dr. Moore helped solve my buffered stdout problem

	
