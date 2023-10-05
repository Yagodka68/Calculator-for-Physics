#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>	// Include windows.h library for Sleep() function

//#define debug

#ifdef debug							// define "debug" while the programm is beeing testet so assert-functions get compiled 
#include <assert.h>

void testCase();						// testCases for functions

void testChooseOption();
void testRangeOfOption(int*);
void testMoveTheArrow(char*, char*, int*);
#endif


void showTargetedOpt(int opt)
{
	if (opt == 0)
		printf("--> ");						
	else
		printf("    ");

	puts("Calculate velocity"); 

	if (opt == 1)
		printf("--> ");
	else
		printf("    ");

	puts("Calculate acceleration\n");

	if (opt == 2)
		printf("--> ");
	else
		printf("    ");

	puts("Exit");
}

void rangeOfOption(int* opt, int range1, int range2)
{
	if (*opt < range1)			
		*opt = range2;			
	else if (*opt > range2)		
		*opt = range1;			
}

void moveTheArrow(char key1, char key2, int* opt)
{
	if (key1 == -32 && key2 == 72)
		(*opt)--;
	else if (key1 == -32 && key2 == 80)
		(*opt)++;

	rangeOfOption(opt, 0, 2);		//	Limits the option code so it's not out of range by the min and max value
}

char chooseOption()
{
	int opt = 0;
	char key1 = 0, key2 = 0;

	while (1)
	{
		puts("Choose the option\t\t\tArrow up - Up\tArrow down - Down\tEnter - Choose\n\n\n\n");
		
		showTargetedOpt(opt);		// Shows the targeted option by arrow

		key1 = _getch();	// reading 2 keys because arrows give 2 values - Here: The first key
		system("cls");		
		if (key1 == 13)		// If key is Enter (with ASCII code 13), the function returns the 
			return opt;
		else if (key1 != -32)
			continue;
		key2 = _getch();	// Here: the second key

		moveTheArrow(key1, key2, &opt);	// Moves the arrow depending on key by changing the option
	}
}



double calcV()
{
	double s = 0, t = 0;

	puts("s - The lastet way in m\t v - The speed in m/s\t t - The time in s");
	puts("    s");
	puts("v = -");
	puts("    t\n\n\n");

	puts("Type s in m:");
	scanf("%lf", &s);
	puts("Type t in s:");
	scanf("%lf", &t);
	puts("");

	double v = s / t;
	
	int opt = 0;

	while (1)																				// Offering the option to calculate the acceleration when needed
	{																						// Constructed similar to the function char chooseOption()
		printf("Result: v = %.7lf m/s\n\n", v);
		puts("Use Up/Down button to switch\t Use the Enter button to choose\n\n\n");

		if (opt == 0)
			printf("--> ");
		else
			printf("    ");
		puts("Calculate acceleration \"a\" with the known velocity \"v\" and return to menu");

		if (opt == 1)
			printf("--> ");
		else
			printf("    ");
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

		puts("\n\n\n\n\n\n\n");
	}

	system("cls");
}

double calcA()
{
	double v = 0, t = 0;

	puts("a - The acceleration way in m/s^2\t v - The speed in m/s\t t - The time in s");
	puts("    v");
	puts("a = -");
	puts("    t\n\n\n");

	puts("Type v in m:");
	scanf("%lf", &v);
	puts("Type t in s:");
	scanf("%lf", &t);
	
	double a = v / t;
	printf("Result: v = %.7lf m/s^2\n\n", a);

	puts("Press any key to continue.");
	char any_key = _getch();
	system("cls");
}

double redirectToChoice(int opt)
{
	switch (opt)
	{
		case 0:
			calcV();		// Calc. veloctity and prints the result.
			break; 
		case 1:
			calcA(0, 0);		// Calc. acceleration and prints the result.
			break;
	}
}

#ifndef debug
void printWelcomeMessage()
{
	int greetingTimeout = 4000;		// The period of time in miliseconds where the welcome message is shown

	puts("Calculator for physics 2023\n");																					// Welcome  
	printf("Calculation of velocity and acceleration\nProgrammed on C\nPlease wait and don't press any button...  ");		// message
																															
	
	for (unsigned i = 0, phase = 0; i < 4; i++, phase = i % 4)			// Animation for a loading symbol
	{

		if (phase == 0)
			printf("|");
		else if (phase == 1)
			printf("/");
		else if (phase == 2)
			printf("-");
		else if (phase == 3)
			printf("\\");

		printf(" ");
		Sleep(1000);

		printf("\b\b");
	}

	system("cls");																										//
}
#endif

int main()
{
	#ifdef debug
	testCase();			// starts the test operation
	#endif

	int option = 0;		

	#ifndef debug
	printWelcomeMessage();																							// PrintsTheWelcome Message
	#endif 

	while (1)
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
	assert(*opt == 1);

	*opt = 3;
	rangeOfOption(opt, 0, 1);
	assert(*opt == 1);

	*opt = -1;
	rangeOfOption(opt, 0, 1);
	assert(*opt == 0);

	*opt = -2;
	rangeOfOption(opt, 0, 1);
	assert(*opt == 0);
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

	*key1 = 'b';
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
	assert(*opt == 1);

	*key1 = -32;
	*key2 = 72;
	*opt = 0;
	moveTheArrow(*key1, *key2, opt);
	assert(*opt == 0);
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