#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "Null.h"
#include "Boolean.h"
#include "MenuManager.h"
#include "InputExt.h"
#include "Main.h"

int main()
{
	system("mode con: lines=30 cols=91");

	int studentCount = 0;
	int studentID[MaxStudents];
	char studentName[MaxStudents][StudentStringLen];
	int studentKorean[MaxStudents];
	int studentEnglish[MaxStudents];

	int currentMenuIndex = RoomMain;
	char currentMenu[MenuBufferLen][MenuStringLen];
	char command[CommandStringLen];

	while (changeMenu(currentMenuIndex, currentMenu))
	{
		menuGetCommand(command);
		switch (currentMenuIndex)
		{
			case RoomMain:
				if (strcmp(command, "print") == 0) currentMenuIndex = RoomPrint;
				else if (strcmp(command, "new") == 0) currentMenuIndex = RoomNewStudent;
				else if (strcmp(command, "exit") == 0) currentMenuIndex = none;
				break;
			case RoomPrint:
				if (!strcmp(command, "id") || !strcmp(command, "name") || !strcmp(command, "korean") || !strcmp(command, "english"))
				{
					sortStudents(studentID, studentName, studentKorean, studentEnglish, studentCount, command);
					printStudents(studentID, studentName, studentKorean, studentEnglish, studentCount);
					waitForInput();
				}
				if (strcmp(command, "back") == 0) currentMenuIndex = RoomMain;
				break;
			case RoomNewStudent:
				if (strcmp(command, "new") == 0)
				{
					if (studentCount < MaxStudents)
					{
						printf("\n-------------------------------------------------------------------------------------------\n");

						printf("학번을 입력해주세요(100~999) : ");
						getStudentID(studentCount, studentID);

						printf("이름을 입력해주세요(소문자) : ");
						getStudentName(studentCount, studentName);

						printf("국어 성적을 입력해주세요 : ");
						getStudentScroe(studentCount, studentKorean);

						printf("영어 성적을 입력해주세요 : ");
						getStudentScroe(studentCount, studentEnglish);

						printf("-------------------------------------------------------------------------------------------\n");
						printf("정상적으로 등록되었습니다.");
						studentCount++;
						waitForInput();
					}
					else puts("더이상 학생을 추가할 수 없습니다.");
				}
				else if (strcmp(command, "back") == 0) currentMenuIndex = RoomMain;
				break;
		}
		system("cls");
	}
	return 0;
}

void getStudentID(int studentCount, int studentID[])
{
	studentID[studentCount] = getOnlyInteger();
	while (studentID[studentCount] < 100 || studentID[studentCount] > 999)
	{
		printf("> 학번은 100~999 범위여야 합니다. 다시 입력해주세요 : ");
		studentID[studentCount] = getOnlyInteger();
	}
	for (int i = 0; i < studentCount; i++)
	{
		if (studentID[i] == studentID[studentCount])
		{
			printf("> 이미 성적이 등록된 학생입니다. 다시 입력해주세요 : ");
			getStudentID(studentCount, studentID);
			break;
		}
	}
}

void getStudentName(int studentCount, char studentName[][StudentStringLen])
{
	getOnlyLower(studentName[studentCount]);
	int len = strlen(studentName[studentCount]);
	while (len < 1 || len > 5)
	{
		printf("> 이름은 다섯 글자 이내여야 합니다. 다시 입력해주세요 : ");
		getOnlyLower(studentName[studentCount]);
		len = strlen(studentName[studentCount]);
	}
	studentName[studentCount][0] = toupper(studentName[studentCount][0]);
}

void getStudentScroe(int studentCount, int studentScroe[])
{
	studentScroe[studentCount] = getOnlyInteger();
	while (studentScroe[studentCount] < 0 || studentScroe[studentCount] > 100)
	{
		printf("> 성적은 0 이상 100 이하여야 합니다. 다시 입력해주세요 : ");
		studentScroe[studentCount] = getOnlyInteger();
	}
}

void printStudents(int id[], char name[][StudentStringLen], int korean[], int english[], int count)
{
	system("cls");
	printf("-------------------------------------------------------------------------------------------\n");
	printf("     학번\t학생이름 \t국어성적\t영어성적\n");
	printf("-------------------------------------------------------------------------------------------\n");
	if (count > 0)
	{
		for (int i = 0; i < count; i++)
		{
			printf("     %-4d\t%-9s\t%8d\t%8d\n", id[i], name[i], korean[i], english[i]);
		}
		printf("\n");
		printf("         \t%-9s\t%8.2f\t%8.2f\n", "평균", getAverage(count, korean), getAverage(count, english));
		printf("         \t%-9s\t%8.2f\t%8.2f\n", "표준편차", getStdDeviation(count, korean), getStdDeviation(count, english));
	}
}

void sortStudents(int id[], char name[][StudentStringLen], int korean[], int english[], int count, char sortCommand[])
{
	printf("\n-------------------------------------------------------------------------------------------\n");
	printf("정렬 방법을 선택해주세요(오름차순, 내림차순) : ");
	char tempStr[9];
	int sortBy = none;
	while (sortBy == none)
	{
		gets_s(tempStr, sizeof(tempStr));
		if (strcmp(tempStr, "오름차순") == 0) sortBy = Ascending;
		else if (strcmp(tempStr, "내림차순") == 0) sortBy = Descending;
		else printf("> 오름차순 혹은 내림차순으로 다시 입력해주세요 : ");
	}
	printf("\n-------------------------------------------------------------------------------------------\n");

	int *sortTarget = null;
	if (strcmp(sortCommand, "id") == 0) sortTarget = id;
	else if (strcmp(sortCommand, "korean") == 0) sortTarget = korean;
	else if (strcmp(sortCommand, "english") == 0) sortTarget = english;

	for (int i = 0; i < count - 1; i++)
	{
		for (int j = i + 1; j < count; j++)
		{
			int cmpResult = (sortTarget != null) ? sortTarget[j] > sortTarget[i] : strcmp(name[j], name[i]);
			if ((sortBy == Ascending && cmpResult != 1) || (sortBy == Descending && cmpResult == 1))
			{
				swapInt(&id[i], &id[j]);
				swapInt(&korean[i], &korean[j]);
				swapInt(&english[i], &english[j]);
				swapString(name[i], name[j]);
			}
		}
	}
}

void swapInt(int *x, int *y)
{
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;
}

void swapString(char str1[], char str2[])
{
	char tempStr[StudentStringLen];
	strcpy(tempStr, str1);
	strcpy(str1, str2);
	strcpy(str2, tempStr);
}

float getAverage(int studentCount, int studentScroe[])
{
	int sum = 0;
	for (int i = 0; i < studentCount; i++) sum += studentScroe[i];
	return (sum / studentCount);
}

float getStdDeviation(int studentCount, int studentScroe[])
{
	float deviation = 0.0f;
	float average = getAverage(studentCount, studentScroe);
	for (int i = 0; i < studentCount; i++)
	{
		deviation += power(studentScroe[i] - average, 2);
	}
	deviation = sqrt(deviation / studentCount);
	return deviation;
}

float power(int x, int exp)
{
	if (exp > 0)
		return (x * power(x, exp - 1));
	else if (exp < 0)
		return (1 / x * power(x, exp + 1));
	else
		return 1;
}

int changeMenu(int menuIndex, char menu[][MenuStringLen])
{
	menuClear(menu);
	switch (menuIndex)
	{
		case RoomMain: changeToMain(menu); break;
		case RoomPrint: changeToPrint(menu); break;
		case RoomNewStudent: changeToNewStudent(menu); break;
		default: return false;
	}
	menuPrint(menu);
	return true;
}

void changeToMain(char menu[][MenuStringLen])
{
	menuAdd(menu, "--------------------------------------------------------------------------------");
	menuAdd(menu, "                             성적관리 프로그램 v1.0                             ");
	menuAdd(menu, "--------------------------------------------------------------------------------");
	menuAdd(menu, " ");
	menuAdd(menu, "  print  : 종합 출력\n");
	menuAdd(menu, "  new    : 성적 등록\n");
	menuAdd(menu, "  exit   : 종료");
	menuAdd(menu, " ");
	menuAdd(menu, "--------------------------------------------------------------------------------");
	menuAdd(menu, "                                 by. wnsrn3436                                  ");
	menuAdd(menu, "--------------------------------------------------------------------------------");
}

void changeToPrint(char menu[][MenuStringLen])
{
	menuAdd(menu, "--------------------------------------------------------------------------------");
	menuAdd(menu, "                                   종합 출력                                    ");
	menuAdd(menu, "--------------------------------------------------------------------------------");
	menuAdd(menu, " ");
	menuAdd(menu, "  id      : 학번순으로 출력\n");
	menuAdd(menu, "  name    : 이름순으로 출력\n");
	menuAdd(menu, "  korean  : 국어 성적순으로 출력\n");
	menuAdd(menu, "  english : 영어 성적순으로 출력\n");
	menuAdd(menu, "  back    : 뒤로");
	menuAdd(menu, " ");
	menuAdd(menu, "--------------------------------------------------------------------------------");
}

void changeToNewStudent(char menu[][MenuStringLen])
{
	menuAdd(menu, "--------------------------------------------------------------------------------");
	menuAdd(menu, "                                   성적 등록                                    ");
	menuAdd(menu, "--------------------------------------------------------------------------------");
	menuAdd(menu, " ");
	menuAdd(menu, "  new  : 성적 등록\n");
	menuAdd(menu, "  back : 뒤로");
	menuAdd(menu, " ");
	menuAdd(menu, "--------------------------------------------------------------------------------");
}