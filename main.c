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

	puts("Calculate acceleration");
}

void rangeOfOption(int* opt)
{
	if (*opt < 0)			
		*opt = 0;			
	else if (*opt > 1)		
		*opt = 1;			
}

void moveTheArrow(char key1, char key2, int* opt)
{
	if (key1 == -32 && key2 == 72)
		(*opt)--;
	else if (key1 == -32 && key2 == 80)
		(*opt)++;

	rangeOfOption(opt);		//	Limits the option code so it's not out of range
}

char chooseOption()
{
	int opt = 0;
	char key1 = 0, key2 = 0;

	while (1)
	{
		puts("Choose the option\t\t\tArrow up - Up\tArrow down - Down\tEnter - Choose\n\n\n\n");

		
		showTargetedOpt(opt);		// Shows the targeted option by arrow


		key1 = _getch();	// reading the 2 keys because  arrows give 2 values - Here: The first key
		system("cls");		
		if (key1 == 13)		// If key is Enter (with ASCII code 13), the function returns the 
			return opt;
		key2 = _getch();	// Here: the second key

		

		moveTheArrow(key1, key2, &opt);	// Moves the arrow depending on key by changing the option
	}
}



double calcV()
{
	double s = 0, v = 0, t = 0;

	puts("s - The lastet way in m\t v - The speed in m/s\t t - The time in s");
	puts("    s");
	puts("v = -");
	puts("    t\n\n\n");

	puts("Type s in m:");
	scanf("%lf", &s);
	puts("Type t in s:");
	scanf("%lf", &t);

	double res = s / t;
	printf("Result: v = %.7lf m/s\n\n", res);

	puts("Press any key to continue.");
	char any_key = _getch();
	system("cls");

}

double calcA()
{
	double v = 0, a = 0, t = 0;

	puts("a - The acceleration way in m/s^2\t v - The speed in m/s\t t - The time in s");
	puts("    v");
	puts("a = -");
	puts("    t\n\n\n");

	puts("Type v in m:");
	scanf("%lf", &v);
	puts("Type t in s:");
	scanf("%lf", &t);

	double res = v / t;
	printf("Result: v = %.7lf m/s^2\n\n", res);

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
			calcA();		// Calc. acceleration and prints the result.
			break;
	}
}



int main()
{
	#ifdef debug
	testCase();			// starts the test operation
	#endif

	int option = 0, greetingTimeout = 4000;		// The period of time in miliseconds where the welcome message is shown

	puts("Calculator for physics 2023\n");																				// 
	puts("Calculation of velocity and acceleration\nProgrammed on C\nPlease wait and don't press any button...");		//	 Welcome 
	Sleep(greetingTimeout);																								//	 message
	system("cls");																										//
	 

	while (1)
	{
		option = chooseOption(); // returns the option 0 or 1
		redirectToChoice(option); // Option 0 stands for calc. of velocity // Option 1 for calc. of acceleration
	}
}

#ifdef debug

void testRangeOfOption(int* opt)
{
	*opt = 0;
	rangeOfOption(opt);
	assert(*opt == 0);

	*opt = 1;
	rangeOfOption(opt);
	assert(*opt == 1);

	*opt = 2;
	rangeOfOption(opt);
	assert(*opt == 1);

	*opt = 3;
	rangeOfOption(opt);
	assert(*opt == 1);

	*opt = -1;
	rangeOfOption(opt);
	assert(*opt == 0);

	*opt = -2;
	rangeOfOption(opt);
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