
#include "Utils.h"
#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;


char GetCharacter(const char * prompt, const char* error)
{

	const int IGNORE_CHARS = 256;

	char input;
	bool failure;

	do
	{
		failure = false;

		cout << prompt;
		cin >> input;

		if(cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << error << endl;
			failure = true;
		}
		else
		{
			cin.ignore(IGNORE_CHARS, '\n');

			if(isalpha(input))
			{
				input = tolower(input);
			}
			else
			{
				cout << error << endl;
				failure = true;
			}
		}

	}while(failure);

	return input;
}

char GetCharacter(const char *prompt, const char* error, const char validInput[], int validInputLength, CharacterCaseType charCase)
{

	const int IGNORE_CHARS = 256;

	char input;
	bool failure;

	do
	{
		failure = false;

		cout << prompt;
		cin >> input;

		if(cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << error << endl;
			failure = true;
		}
		else
		{
			cin.ignore(IGNORE_CHARS, '\n');

			if(isalpha(input))
			{
				if(charCase == CC_UPPER_CASE)
				{
					input = toupper(input);
				}
				else if(charCase == CC_LOWER_CASE)
				{
					input = tolower(input);
				}

				for(int i = 0; i < validInputLength; i++)
				{
					if(input == validInput[i])
					{
						return input;
					}
				}
			}

			cout << error << endl;
			failure = true;

		}

	}while(failure);

	return input;
}


int GetInteger(const char * prompt, const char* error, const int validInput[], int validInputLength)
{
	int input;
	bool inputFailure;

	const int IGNORE_CHARS = 256;
	do
	{

		inputFailure = false;

		cout << prompt;
		cin >> input;

		if(cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << error << endl;
			inputFailure = true;
		}
		else
		{
			for(int i = 0; i < validInputLength; i++)
			{
				if(input == validInput[i])
				{
					return input;
				}
			}


			cout << error << endl;
			inputFailure = true;
		}


	}while(inputFailure);

	return -1;

}

int GetString(const char * prompt, const char * error, char string[], int maxLength) {	
	bool inputFailure;

	const int IGNORE_CHARS = 256;
	
	int length = 0;
	
	do
	{

		inputFailure = false;

		cout << prompt;
		cin >> ws; // read a new line
		cin.get(string, maxLength, '\n');

		if(cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << error << endl;
			inputFailure = true;
		}
		else
		{
			cin.ignore(IGNORE_CHARS, '\n');
			length = strlen(string);	
			
			if (length == 0) {
				cout << "You must enter a word that's longer than 0 characters! Please Try again'" << endl;
				inputFailure = true;
			} 
			
		}
	}while(inputFailure);

	return length;
}

void ClearScreen()
{
	system("clear");
}

void WaitForKeyPress()
{
	system("pause");//for windows only!

//	system("read -n 1 -s -p \"Press any key to continue...\";echo");
}
