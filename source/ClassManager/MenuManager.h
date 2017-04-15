#pragma once

#define MenuBufferLen 128
#define MenuStringLen 128
#define MenuMarginText "     "
#define MenuCommandText "¸í·É¾î : "
#define CommandStringLen 128

int menuAdd(char menu[][MenuStringLen], char str[]);
void menuClear(char menu[][MenuStringLen]);
int menuCount(const char menu[][MenuStringLen]);
void menuPrint(const char menu[][MenuStringLen]);
void menuGetCommand(char str[]);