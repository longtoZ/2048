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
int printStartMenu(User &user);
int printUserMenu();

string centerBoardNumber(int n, int length, string txt, string bg, int type);
string convertNumberToColor(int n);
string emptyLine(int n, int length, string bg);
string emptyCell(int n, int length, string bg, int type);

void printBoard(Gameplay &gameplay);
void printGameplayMenu(Gameplay &gameplay, Stack &undoStack, Stack &redoStack, User &user);
void printFull(Gameplay &gameplay, Stack &undoStack, Stack &redoStack, User &user);
void printAchievement(User &user);
void printLeaderboard(User &user, bool highlightUser = false);