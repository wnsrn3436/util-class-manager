#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StringExt.h"
#include "InputExt.h"

void waitForInput()
{
	char input[InputStringLen];
	gets_s(input, InputStringLen);
}

int getOnlyInteger()
{
	char input[InputStringLen];

	gets_s(input, InputStringLen);
	while (!isOnlyInteger(input))
	{
		printf(IntegerError);
		gets_s(input, InputStringLen);
	}

	return atoi(input);
}

void getOnlyUpper(char str[])
{
	char input[InputStringLen];

	gets_s(input, InputStringLen);
	while (!isOnlyUpper(input))
	{
		printf(UpperError);
		gets_s(input, InputStringLen);
	}

	strcpy(str, input);
}

void getOnlyLower(char str[])
{
	char input[InputStringLen];

	gets_s(input, InputStringLen);
	while (!isOnlyLower(input))
	{
		printf(LowerError);
		gets_s(input, InputStringLen);
	}

	strcpy(str, input);
}