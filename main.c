// bfm interpreter //
// copyright (C) 2019 duri64 //
// under the GPLv3-License (SEE LICENSE.md) //

#include <stdio.h>
#define ARRSIZE 30000 // TODO: wrap underflows and overflows

//char input[] = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";
char* input;
char* array;
int shellmode = 0;
int counter = 0;
int pluscount = 0;
int minuscount = 0;
int debug = 0; // debug mode variable, 0 = off, 1 = on. if corrupted the 'd' command will temporarily restore it.
int loopmode = 0;
int beginloop = 0;
int isdebugfile = 0;
char* vernum = "1.2-rc1\n"; // current release variable, only displayed when 'v' is run in debug mode.

char* debugout = 0;

int debugprintarray() {
	printf("\nDEBUG: [");
	for (int i = 0; i < ARRSIZE; ++i) {
		if (i == ARRSIZE-1)
			printf("\"%c\" = %d", array[i], array[i]);
		else
			printf("\"%c\" = %d, ", array[i], array[i]);
	}
	printf("]\n");
 
	return 0;
}

int compile(char x, int i) { // WIP for a -c switch. translates everything in to C and then runs GCC to compiles it
	if (debug == 1) {
		printf("Compiling '%c' at pos %d\n", x, i);
	}
}

int interpret(char x, int i) {
	if (debug == 1)
		printf("Interpreting '%c' at pos %d\n", x, i);

	switch (x) {
		case '>': // move cell pointer (the counter int) left
			++counter;
			break;
		case '<': // move cell pointer (the counter int) left
			--counter;
			break;
		case '+': // add 1 to current cell
			++(array[counter]);
			if (debug == 1)
				printf("Char at pos %d is now %d\n", counter, array[counter]);
			break;
		case '-': // subtract 1 from current cell
			--(array[counter]);
			if (debug == 1)
				printf("Char at pos %d is now %d\n", counter, array[counter]);
			break;
		case '.': // print contents of current cell in ASCII
			if (debug == 1)
				//sprintf(debugout, "%c", array[counter]);
				strncat(debugout, array+counter, 1);
			else
				printf("%c", array[counter]);
			break;
		case ',': // ask for one char of input
			array[counter] = getchar();
			break;
		case '[': // begin while (array[counter] == 0) loop
			loopmode = 1;
			beginloop = i;
			break;
		case '!': // exit command (shell has a non silent version)
			if (shellmode == 1) {
				printf("exiting...\n");
			}
			free(array);
			exit(0);
			break;
		case '#': // debugging command, prints out the tape
			if (debug == 1)
				debugprintarray();
			else {
				printf("hey! that's a debug (-d) mode-only command!");
				break;
			}
		case '@': // debugging command, frees array
			if (debug == 1) {
				//free(array);
				memset(array, 0, ARRSIZE);
				printf("tape cleared.\n");
			}
			else {
				printf("hey! that's a debug (-d) mode-only command!");
				break;
			}
		//case '*': // set ARRSIZE to current cells value
			//#define ARRSIZE array[counter]
			//printf("ARRSIZE set to %c", array[counter]);
			//break;
		case '^': // print current cells numerical value
			printf("%d\n", array[counter]);
			break;
		case '_': // subtract 10 from current cell
			while (minuscount < 10) {
				--array[counter];
				++minuscount;
			}
			if (debug == 1) {
				printf("char at pos %d is now %d\n", counter, array[counter]);
			}
			minuscount = 0;
			break;
		case '=': // add 10 to current cell
			while (pluscount < 10) {
				++array[counter];
				++pluscount;
			}
			if (debug == 1) {
				printf("char at pos %d is now %d\n", counter, array[counter]);
			}
			pluscount = 0;
			break;
		case '/': // clear screen, works on Windows/*Nix/*BSD/whatever
			#ifdef _WIN32
			system("cls");
			#else
			system("clear");
			#endif
			if (debug == 1) {
				printf("bfm interactive shell (debug mode).\n");
				break;
			}
			else if (debug == 0) {
				printf("bfm interactive shell.\n");
				break;
			}
		case 'v': // version command
			if (debug == 1) {
				printf("bfm v1");
				printf("\nthe exact version number is: ");
				printf(vernum);
				break;
			}
			else {
				printf("bfm v1");
				break;
			}
		case 'c': // credits command
			printf("bfm - built by @isy#0669 and @YPwn#9731");
			break;
		case 'd': // debug mode toggle
			if (debug == 0) {
				debug = 1;
				printf("debug mode is now toggled ON. use 'd' again to turn it off.\n");
				break;
			}
			else if (debug == 1) {
				debug = 0;
				printf("debug mode is now toggled OFF. use 'd' again to turn it on.\n");
				break;
			}
			else {
				debug = 0;
				printf("the debug variable was corrupted and is now set to 0. use 'd' again to toggle debug mode on.\n");
				break;
			}
		case '?': // help command
			printf("\nbfm - an expanded brainf*ck interpreter.\n\n> - move pointer right.\n< - move pointer left.\n+ - add 1 to current cell.\n- - subtract 1 from current cell.\n= - add 10 to current cell.\n_ - subtract 10 from current cell.\n. - print contents of current cell in ASCII.\n, - ask for one char of user input.\n[ - start loop.\n] - end loop.\n! - end program.\n# - print contents of tape (debug mode only).\n@ - clear tape (debug mode only).\n^ - print numerical value of current cell.\n/ - clear screen.\nv - show version.\nc - show credits.\nd - enable/disable debug mode.\n? - show this help dialogue.\n");
			break;
		default: // else
			break;
	}
 
	return 0;
}

void compilebrain(char* code, int size) {
	printf("wee it works!\n");
}

void runbrain(char* code, int size) {
	if (debug == 1) {
		printf("Code: %s, size: %d\n", code, size);
		debugout = (char*)calloc(1, 2048); // temp size
	}

	for (int i = 0; i < size; ++i) {
		if (debug == 1)
			printf("I: %d, char: %c\n", i, code[i]);
		interpret(code[i], i);
		if (loopmode) {
			if (code[i] == ']') {
				if (array[counter]) {
					i = beginloop;
					if (debug == 1)
						printf("array counter: %d %d\n", array[counter], counter);
				} else
					loopmode = 0;
			}
		}
	}

	if (debug == 1) {
		printf("\nProgram output: %s\n", debugout);
		free(debugout);
	} else
		puts("");
}

void runshell(int isdebug) {
	shellmode = 1;
	if (!isdebug)
		printf("bfm interactive shell.\n");
	else {
		printf("bfm interactive shell (debug mode).\n");
		debug = 1;
	}

	char* str;
	if (isdebug)
		str = (char*)calloc(1, ARRSIZE);

	while (1) {
		if (!isdebug)
			str = (char*)calloc(1, ARRSIZE);
		//memset(str, 0, ARRSIZE);
		printf("bfm> ");
		fgets(str, ARRSIZE, stdin);
		if (str[0] == '\0')
			return;
		array = (char*)calloc(1, ARRSIZE);
		if (!(str[0] == 0x0A))
			runbrain(str, strlen(str));
		free(array);
		if (!isdebug)
			free(str);
	}
}

void runfile(char* filename) {
	if (isdebugfile == 1) {
		printf("interpreting file in debug mode (-dF switch used).");
		debug == 1;
	}
	// let's read the file in argument 1
	FILE* myfile = fopen(filename, "rb");

	// obtain file size
	fseek(myfile, 0, SEEK_END);
	int filesize = ftell(myfile);
	rewind(myfile);

	// load the file into "input"
	input = (char*)malloc(filesize+1);
	fread(input, 1, filesize, myfile);
	input[filesize] = '\0';
	fclose(myfile);
	//printf("Now input contains: %s\n", input);

	array = (char*)calloc(1, ARRSIZE);
	//int size = sizeof(input)-1;
	int size = filesize;

	runbrain(input, filesize);
}
 
int main(int argc, char** argv) {
	for (int i = 0; i < argc; ++i) {
		if (!strcmp(argv[i], "-d")) {
			compilebrain;
			goto end;
		}
	}

	if (argc == 2)
		runfile(argv[1]);
	else
		runshell(0);

p2:
	if (argc == 2)
		runfile(argv[1]);
	else
		runshell(0);

end:
	free(array);
	return 0;
}
