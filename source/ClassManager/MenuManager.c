#include <stdio.h>
#include <string.h>
#include "Null.h"
#include "Boolean.h"
#include "MenuManager.h"

int menuAdd(char menu[][MenuStringLen], char str[])
{
	int count = menuCount(menu);
	if (count < MenuBufferLen)
	{
		strcpy_s(menu[count], MenuStringLen, str);
		return true;
	}
	else return false;
}

void menuClear(char menu[][MenuStringLen])
{
	int count = menuCount(menu);
	for (int i = 0; i < count; i++)
	{
		menu[i][0] = null;
	}
}

int menuCount(const char menu[][MenuStringLen])
{
	int count;
	for (count = 0; count < MenuBufferLen; count++)
	{
		if (menu[count][0] == null) break;
	}
	return count;
}

void menuPrint(const char menu[][MenuStringLen])
{
	int count = menuCount(menu);
	for (int i = 0; i < count; i++)
	{
		printf("%s", MenuMarginText);
		puts(menu[i]);
	}
}

void menuGetCommand(char str[])
{
	printf("%s%s", MenuMarginText, MenuCommandText);
	gets_s(str, MenuStringLen);
}