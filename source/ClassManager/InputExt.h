#pragma once

#define InputStringLen 128
#define IntegerError "> 입력된 값이 숫자로 구성되지 않았습니다. 다시 입력해주세요 : "
#define UpperError "> 입력된 값이 대문자로 구성되지 않았습니다. 다시 입력해주세요 : "
#define LowerError "> 입력된 값이 소문자로 구성되지 않았습니다. 다시 입력해주세요 : "

void waitForInput();
int getOnlyInteger();
void getOnlyUpper(char str[]);
void getOnlyLower(char str[]);