#pragma once

#include "MenuManager.h"

#define RoomMain 0
#define RoomPrint 1
#define RoomNewStudent 2

#define MaxStudents 256
#define StudentStringLen 128

#define Ascending 0
#define Descending 1

void getStudentID(int studentCount, int studentID[]);
void getStudentName(int studentCount, char studentName[][StudentStringLen]);
void getStudentScroe(int studentCount, int studentScroe[]);
void printStudents(int id[], char name[][StudentStringLen], int korean[], int english[], int count);
void sortStudents(int id[], char name[][StudentStringLen], int korean[], int english[], int count, char sortCommand[]);
void swapInt(int *x, int *y);
void swapString(char str1[], char str2[]);
float getAverage(int studentCount, int studentScroe[]);
float getStdDeviation(int studentCount, int studentScroe[]);
float power(int x, int exp);
int changeMenu(int menuIndex, char menu[][MenuStringLen]);
void changeToMain(char menu[][MenuStringLen]);
void changeToPrint(char menu[][MenuStringLen]);
void changeToNewStudent(char menu[][MenuStringLen]);