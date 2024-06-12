#pragma once
#include "struct.h"
#include "stack.h"
#include "cleanup.h"
#include "display.h"
#include "init.h"
#include "leaderboard.h"
#include "handleRandom.h"
#include "utils.h"
using namespace std::chrono;

bool gameOver(Gameplay &gameplay);
bool gameWon(Gameplay &gameplay);

int undo(Gameplay &gameplay, Stack &undoStack, Stack &redoStack);
int redo(Gameplay &gameplay, Stack &undoStack, Stack &redoStack);

void createBoard(Gameplay &gameplay);
void moveLeft(Gameplay &gameplay, int &moved);
void moveRight(Gameplay &gameplay, int &moved);
void moveUp(Gameplay &gameplay, int &moved);
void moveDown(Gameplay &gameplay, int &moved);
void endGame(Gameplay &gameplay, Stack &undoStack, Stack &redoStack, User &user);
