									//**********************************************************************//		
									//						Calculator for Physics							//
									//																		//
									//		with Command Line Arguments support.							//
									//		Calculates velocity and acceleration.							//
									//		No other documents (such as txt files and etc) are required.	//
									//		Works only on Windows OS.										//
									//																		//
									//		Programmed by Deniel											//
									//**********************************************************************//										

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>	// Include windows.h library for Sleep() function

//#define debug

#ifdef debug							// define "debug" while the programm is beeing testet so assert-functions get compiled 
#include <assert.h>

void testCase();						// testCases for functions

void testChooseOption();
void testRangeOfOption(int*);
void testMoveTheArrow(char*, char*, int*);
#endif


void showTargetedOpt(unsigned opt)
{
	if (opt == 0)
		fputs("--> ", stdout);
	else
		fputs("    ", stdout);

	puts("Calculate velocity"); 

	if (opt == 1)
		fputs("--> ", stdout);
	else
		fputs("    ", stdout);

	puts("Calculate acceleration\n");

	if (opt == 2)
		fputs("--> ", stdout);
	else
		fputs("    ", stdout);

	puts("Exit");
}

void rangeOfOption(int* opt, int minOptVal, int maxOptVal)
{
	if (*opt < minOptVal)
		*opt = maxOptVal;
	else if (*opt > maxOptVal)
		*opt = minOptVal;
}

void moveTheArrow(char key1, char key2, int* opt)
{
	if (key1 == -32 && key2 == 72)
		(*opt)--;
	else if (key1 == -32 && key2 == 80)
		(*opt)++;
}

char chooseOption()
{
	int opt = 0;
	char key1 = 0, key2 = 0;

	while (1)
	{
		puts("Choose the option\t\t\tArrow up - Up\tArrow down - Down\tEnter - Choose\n\n\n\n");
		
		showTargetedOpt(opt);		// Shows the targeted option by arrow

		key1 = _getch();	// Reading 2 keys because arrows give 2 values - Here: The first key
		system("cls");		
		if (key1 == 13)		// If key is Enter (with ASCII code 13), the function returns the 
			return opt;
		else if (key1 != -32)
			continue;
		key2 = _getch();	// Here: the second key

		moveTheArrow(key1, key2, &opt);	// Moves the arrow depending on key by changing the option
		rangeOfOption(&opt, 0, 2);		//	Limits the option code so it's not out of range by the min and max value
	}
}

double div2Vals(double a, double b)
{
	long double zero = 0;

	if (a != 0 && b != 0)
		return a / b;
	return zero;
}

void calcV()
{
	double s = 0, t = 0, v = 0;

	puts("s - The lasted way in m\t v - The speed in m/s\t t - The time in s");
	puts("    s");
	puts("v = -");
	puts("    t\n\n\n");

	puts("Type s in m:");
	scanf("%lf", &s);
	puts("Type t in s:");
	scanf("%lf", &t);
	puts("");

	v = div2Vals(s, t);
	
	int opt = 0;

	while (1)																				// Offering the option to calculate the acceleration when needed
	{																						// Constructed similar to the function char chooseOption()
		printf("Result: v = %.7lf m/s\n\n", v);
		puts("Use Up/Down button to switch\t Use the Enter button to choose\n\n\n");

		if (opt == 0)
			fputs("--> ", stdout);
		else
			fputs("    ", stdout);
		puts("Calculate acceleration \"a\" with the known velocity \"v\" and return to menu");

		if (opt == 1)
			fputs("--> ", stdout);
		else
			fputs("    ", stdout);
		puts("Return to menu");

		char key1 = _getch();
		system("cls");
		if (key1 == 13)
		{
			if (opt == 0)
			{
				printf("Result: a = %lf m/s^2\n\n\n", v / t);

				puts("Press any Button to continue");
				char anyKey = _getch();
				break;				// Leaving the cicle to clear the screen and leave the function
			}
			else if (opt == 1)
				break;
		}
		else if (key1 != -32)
			continue;
		char key2 = _getch();

		moveTheArrow(key1, key2, &opt);
		rangeOfOption(&opt, 0, 1);		//	Limits the option code so it's not out of range by the min and max value

		puts("\n\n\n\n\n\n\n");
	}

	system("cls");
}

void calcA()
{
	double v = 0, t = 0, a = 0;

	puts("a - The acceleration in m/s^2\t v - The speed in m/s\t t - The time in s");
	puts("    v");
	puts("a = -");
	puts("    t\n\n\n");

	puts("Type v in m/s:");
	scanf("%lf", &v);
	puts("Type t in s:");
	scanf("%lf", &t);
	
	a = div2Vals(v, t);

	printf("Result: v = %.7lf m/s^2\n\n", a);

	puts("Press any key to continue.");
	char any_key = _getch();
	system("cls");
}

void redirectToChoice(unsigned opt)
{
	switch (opt)
	{
		case 0:
			calcV();		// Calc. veloctity and prints the result. Also offers to calculate the acceleratation by known v and t
			break; 
		case 1:
			calcA();		// Calc. acceleration and prints the result.
			break;
	}
}

void printCLAInstructions()
{
	puts("After the name of the programm use folowing flags with their values:\n-s *way in m* and -t *time in s*\nExample: calcForPhysic -t 8 -s 90");
}

void argumentsInProcess(int argc, char* argv[])
{
	double s = 0, t = 0, v = 0, a = 0;
	char* end = NULL;
	int CLANum = argc - 1;

	if (CLANum % 2 != 0)					// Checking if the amount of arguments is even 
	{
		puts("Not enough arguments printed");
		printCLAInstructions();
		return 0;
	}

	if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h"))
	{
		printCLAInstructions();
		return 0;
	}

	for (unsigned i = 1; i < argc; i += 2)
	{
		if (!strcmp(argv[i], "-s"))
			s = strtod(argv[i + 1], &end, 10);
		else if (!strcmp(argv[i], "-t"))
			t = strtod(argv[i + 1], &end, 10);
		else
		{
			puts("Wrong arguments printed");
			printCLAInstructions();
			return 0;
		}
	}

	v = div2Vals(s, t);
	a = div2Vals(v, t);

	printf("v in m/s = %.7lf\n", v);
	printf("a in m/s^2 = %.7lf\n", a);
}

#ifndef debug
void printWelcomeMessage()
{		// The loading screen for 4 seconds
	unsigned greetingTimeInS = 4;

	puts("Calculator for physics 2023\n");																					// Welcome  
	puts("Calculation of velocity and acceleration\nProgrammed on C\nPlease wait and don't press any button...  ");			// message
																															
	// Animation for a loading symbol
	for (unsigned i = 0, phase = 0; i < greetingTimeInS; i++, phase = i % 4)			
	{
		if (phase == 0)				
			fputs("|", stdout);
		else if (phase == 1)
			fputs("/", stdout);
		else if (phase == 2)
			fputs("-", stdout);
		else if (phase == 3)
			fputs("\\", stdout);

		printf(" ");
		Sleep(1000); 

		printf("\b\b");
	}

	system("cls");																										
}
#endif

int main(int argc, char* argv[])
{
	#ifdef debug
	testCase();			// starts the test operation
	#endif

	if (argc > 1)
	{
		argumentsInProcess(argc, argv);
		return 0;
	}

	#ifndef debug
	printWelcomeMessage();		// PrintsTheWelcome Message
	#endif 

	int option = 0;

	while (1)					// The main part
	{
		option = chooseOption(); // returns the option 0, 1 or 2

		if (option == 2)
			return 0;

		redirectToChoice(option); // Option 0 stands for calc. of velocity // Option 1 for calc. of acceleration
	}
}

#ifdef debug

void testRangeOfOption(int* opt)
{
	*opt = 0;
	rangeOfOption(opt, 0, 1);
	assert(*opt == 0);

	*opt = 1;
	rangeOfOption(opt, 0, 1);
	assert(*opt == 1);

	*opt = 2;
	rangeOfOption(opt, 0, 1);
	assert(*opt == 0);

	*opt = 3;
	rangeOfOption(opt, 0, 1);
	assert(*opt == 0);

	*opt = 6;
	rangeOfOption(opt, 2, 4);
	assert(*opt == 2);

	*opt = 16;
	rangeOfOption(opt, 1, 19);
	assert(*opt == 16);

	*opt = 5;
	rangeOfOption(opt, 8, 19);
	assert(*opt == 19);

	*opt = -5;
	rangeOfOption(opt, 8, 19);
	assert(*opt == 19);

	*opt = -6;
	rangeOfOption(opt, 2, 5);
	assert(*opt == 5);
}

void testMoveTheArrow(char* key1, char* key2, int* opt) 
{
	*key1 = -32;				
	*key2 = 80;				// key2 - Up returns 72, Down returns 80
	*opt = 0;
	moveTheArrow(*key1, *key2, opt);		// Changes the option depending on key and so moves the arrow 
	assert(*opt == 1);

	*key1 = -32;
	*key2 = 72;
	*opt = 1;
	moveTheArrow(*key1, *key2, opt);
	assert(*opt == 0);

	*key1 = 'k';
	*key2 = NULL;
	*opt = 0;
	moveTheArrow(*key1, *key2, opt);
	assert(*opt == 0);

	*key1 = -32;
	*key2 = 80;
	*opt = 0;
	moveTheArrow(*key1, *key2, opt);
	assert(*opt == 1);

	*key1 = -32;
	*key2 = 80;
	*opt = 1;
	moveTheArrow(*key1, *key2, opt);
	assert(*opt == 2);

	*key1 = -32;
	*key2 = 72;
	*opt = 0;
	moveTheArrow(*key1, *key2, opt);
	assert(*opt == -1);
}

void testChooseOption()
{
	int opt = 0;
	char key1 = 0, key2 = 0;

	testRangeOfOption(&opt);
	testMoveTheArrow(&key1, &key2, &opt);	
}

void testCase()
{
	testChooseOption(); // testing (sub)functions of  function "char chooseOption()"
}

#endif