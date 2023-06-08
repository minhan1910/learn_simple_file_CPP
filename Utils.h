#ifndef UTILS_H_
#define UTILS_H_


enum CharacterCaseType
{
	CC_UPPER_CASE= 0,
	CC_LOWER_CASE,
	CC_EITHER
};

char GetCharacter(const char * prompt, const char* error);

char GetCharacter(const char *prompt, const char* error, const char validInput[], int validInputLength, CharacterCaseType charCase);

int GetInteger(const char * prompt, const char* error, const int validInput[], int validInputLength);

int GetString(const char * prompt, const char * error, char string[], int maxLength);

void ClearScreen();

void WaitForKeyPress();

#endif /* UTILS_H_ */
