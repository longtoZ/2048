#pragma once
#include <iostream>
#include <windows.h>
#include "struct.h"
#include "keys.h"
#include "utils.h"

void gameOverPopup(int duration);
void gameWonPopup(int duration);
void gameStartPopup(int duration);
void loginPopup(int duration);
void logoutPopup(int duration);
void programStartPopup(int duration);
void programExitPopup(int duration);
void preventPlaying();