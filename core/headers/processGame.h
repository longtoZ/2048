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

void createBoard(Gameplay &gameplay);
void moveLeft(Gameplay &gameplay, int &moved);
void moveRight(Gameplay &gameplay, int &moved);
void moveUp(Gameplay &gameplay, int &moved);
void moveDown(Gameplay &gameplay, int &moved);
bool gameOver(Gameplay &gameplay, Stack &undoStack, Stack &redoStack, const high_resolution_clock::time_point& start_time, User &user);
void endGame(Gameplay &gameplay, Stack &undoStack, Stack &redoStack,const high_resolution_clock::time_point& start_time, User &user);
void undo(Gameplay &gameplay, Stack &undoStack, Stack &redoStack);
void redo(Gameplay &gameplay, Stack &undoStack, Stack &redoStack);
