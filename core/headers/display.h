#pragma once
#include <string>
#include <conio.h>
#include <iostream>
#include "struct.h"
#include "stack.h"
#include "utils.h"
#include "leaderboard.h"
#include "keys.h"
using namespace std;

int convertCellWidth(int n);
string convertNumberToColor(int n);
void emptyLine(int n, int length, string bg);
void centerBoardNumber(int n, int length, string txt, string bg, int type);
void emptyCell(int n, int length, string bg, int type);
void printBoard(Gameplay &gameplay);
void printGameplayMenu(Gameplay &gameplay, Stack &undoStack, Stack &redoStack, User &user);
void printFull(Gameplay &gameplay, Stack &undoStack, Stack &redoStack, User &user);
int printStartMenu(User &user);
int printUserMenu();
void printAchievement(User &user);
void printLeaderboard();