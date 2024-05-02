#pragma once
#include <conio.h>
#include <iostream>
#include "struct.h"
#include "utils.h"
#include "display.h"
#include "handleRandom.h"
#include "processGame.h"
#include "continueGame.h"
#include "keys.h"

int userMenu();
int startMenu(User &user);
void startGame(Gameplay &gameplay, User &user);
void startPrevGame(Gameplay &gameplay, User &user);
