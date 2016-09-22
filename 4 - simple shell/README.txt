Author: Evan Heaton
 ______  _   _    ___    __    _
|  ___/ | | | |  /   \  |  \  | |
| |_    | | | | |  O  | |   \ | |
|  _|   |  \/ | |  _  | | |\ \| |
| |____  \   /  | | | | | | \   |
|_____/   \_/   |_| |_| |_|  \__|

Date Completed: Sunday, April 10th, 2016

Contents:
	- README.txt: this file!
	- parser.c: implementations of functions free_command and parse_command
	- shell.h: prototypes of functions free_command and parse_command, as well as the structure "command"
	- shell.cpp: implementation of the simple shell, mostly in the main() function
	- Makefile: a makefile used to compile the simple shell

Running:
	make to compile
	./shell to run
	the simple shell has a variety of basic commands including but not limited to ls, cd, mkdir, etc.

Implementation Notes:


Limitations:
	- I couldn't get test case 5 to work along with the other test cases. My shell does not properly report exit statuses of children
	- There is no line-length limitation, due to the use of c++ strings instead of c-strings

References:
	People:
	- Zack Arnett
        	o Helped with redirection, as well as the general outline for how to fork()
        	o Was endlessly helpful with general advice

	Sites:
	- http://www.cplusplus.com/forum/general/46540/ : for helping me get started
	- http://mirror.keystealth.org/gnu/bash/ : I downloaded bash to look at source code
	- http://stackoverflow.com/questions/9653072/return-a-struct-from-a-function-in-c : help on structs
	- http://www.linuxquestions.org/questions/programming-9/making-a-c-shell-775690/ : More on forking...
	- MAN PAGES
