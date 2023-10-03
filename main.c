#include <stdio.h> // Test git commit 2
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

char chooseOption()
{
	int opt = 0;
	char key;

	while (1)
	{
		printf("Chose the option\t\t\ti - Up\tk - Down\tEnter - Chose\n\n\n\n\n");

		
		showTargetedOpt(opt);		// Shows the targeted option by arrow


		key = _getch();				// reading the key 

		system("cls");

		if (key == 13)
			return opt;

		moveTheArrow(key, &opt);	// Moves the arrow depending on key by changing the option
	}
}

int main()
{
	#ifdef debug
	testCase();
	#endif

	//printf("Calculator for physic 2023\n");										// 
	//printf("Calculation of velocity and acceleration\nprogrammed on c\n");		//	 Welcome 
	//Sleep(4000);																	//	 message
	//system("cls");																// 

	while (1)
	{
		int option = chooseOption(); // returns the option 0 or 1
		
		
	}

	return 0;
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