#pragma once
#include "struct.h"
#include "stack.h"
#include "list.h"

void cleanChar(char* &s);
void cleanBoard(Gameplay &gameplay);
void cleanEmptyPos(Gameplay &gameplay);
void cleanStack(Stack &stack);
void cleanList(List &list);
void cleanUser(User &user);