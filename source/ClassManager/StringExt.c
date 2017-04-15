#include <string.h>
#include "Boolean.h"
#include "StringExt.h"

int isOnlyInteger(const char str[])
{
	int i = (str[0] == '+' || str[0] == '-') ? 1 : 0;
	int len = strlen(str);
	int result = true;
	for (; i < len; i++)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			result = false;
			break;
		}
	}
	return result;
}

int isOnlyUpper(const char str[])
{
	int len = strlen(str);
	int result = true;
	for (int i = 0; i < len; i++)
	{
		if (str[i] < 'A' || str[i] > 'Z')
		{
			result = false;
			break;
		}
	}
	return result;
}

int isOnlyLower(const char str[])
{
	int len = strlen(str);
	int result = true;
	for (int i = 0; i < len; i++)
	{
		if (str[i] < 'a' || str[i] > 'z')
		{
			result = false;
			break;
		}
	}
	return result;
}