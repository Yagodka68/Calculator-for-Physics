#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>  // Include windows.h library for Sleep() function

#define debug

#ifdef debug				// define "debug" while the programm is beeing testet so assert-functions get compiled 
#include <assert.h>

void testCase();						// testCases for functions

void testChooseOption();
void testRangeOfOption(int*);
void testMoveTheArrow(char*, int*);
#endif


void showTargetedOpt(int opt)
{
	if (opt == 0)
		printf("--> ");						
	else
		printf("    ");

	printf("Calculate velocity\n"); 

	if (opt == 1)
		printf("--> ");
	else
		printf("    ");

	printf("Calculate acceleration\n");
}

void rangeOfOption(int* opt)
{
	if (*opt < 0)			
		*opt = 0;			
	else if (*opt > 1)		
		*opt = 1;			
}

void moveTheArrow(char key, int* opt)
{
	if (key == 'i')
		(*opt)--;
	else if (key == 'k')
		(*opt)++;

	rangeOfOption(opt);		//	Limits the option code so it's not out of range
}

static char chooseOption()
{
	int opt = 0;
	char key;

	while (1)
	{
		printf("Choose the option\t\t\ti - Up\tk - Down\tEnter - Choose\n\n\n\n\n");

		
		showTargetedOpt(opt);		// Shows the targeted option by arrow


		key = _getch();				// reading the key 

		system("cls");

		if (key == 13)
			return opt;

		moveTheArrow(key, &opt);	// Moves the arrow depending on key by changing the option
	}
}



double calcV()
{
	double s = 0, v = 0, t = 0;

	printf("s - The lastet way in m\t v - The speed in m/s\t t - The time in s\n");
	printf("    s\n");
	printf("v = -\n");
	printf("    t\n\n\n\n");

	printf("Type s in m:\n");
	scanf("%lf", &s);
	printf("Type t in s:\n");
	scanf("%lf", &t);

	double res = s / t;
	printf("Result: v = %.7lf m/s\n\n", res);

	printf("Press any key to continue.\n");
	char any_key = _getch();
	system("cls");

}

double calcA()
{
	double v = 0, a = 0, t = 0;

	printf("a - The acceleration way in m/s^2\t v - The speed in m/s\t t - The time in s\n");
	printf("    v\n");
	printf("a = -\n");
	printf("    t\n\n\n\n");

	printf("Type v in m:\n");
	scanf("%lf", &v);
	printf("Type t in s:\n");
	scanf("%lf", &t);

	double res = v / t;
	printf("Result: v = %.7lf m/s^2\n\n", res);

	printf("Press any key to continue.\n");
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

	int option = 0;

	printf("Calculator for physics 2023\n");																				// 
	printf("Calculation of velocity and acceleration\nProgrammed on C\nPlease wait and don't press any button...");		//	 Welcome 
	Sleep(4000);																										//	 message
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

void testMoveTheArrow(char* key, int* opt) 
{
	*key = 'o';
	*opt = 1;
	moveTheArrow(*key, opt);		// Changes the option depending on key and so moves the arrow 
	assert(*opt == 1);

	*key = 'i';
	*opt = 1;
	moveTheArrow(*key, opt);
	assert(*opt == 0);

	*key = 'i';
	*opt = 0;
	moveTheArrow(*key, opt);		
	assert(*opt == 0);

	*key = 'k';
	*opt = 0;
	moveTheArrow(*key, opt);
	assert(*opt == 1);

	*key = 'k';
	*opt = 1;
	moveTheArrow(*key, opt);
	assert(*opt == 1);

	*key = 'd';
	*opt = 0;
	moveTheArrow(*key, opt);
	assert(*opt == 0);
}

void testChooseOption()
{
	int opt;
	char key;

	testRangeOfOption(&opt);
	testMoveTheArrow(&key, &opt);	
}

void testCase()
{
	testChooseOption(); // testing (sub)functions of  function "char chooseOption()"
}

#endif