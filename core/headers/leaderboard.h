#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "struct.h"
#include "list.h"
#include "utils.h"
#include "cleanup.h"
#include "keys.h"

string leftCellNumber(int n, int length);
string getAchievement(User &user);
string getLeaderboard(User &user, int& rankOfUser, int scoreToHighlight = -1);

void storeBestScore(User &user);
void storeAchievement(int size, int score, int step, string elapsed_time, User &user);
void deleteAchievement(User &user);

Data getBestScore(User &user);