#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "struct.h"
#include "list.h"
#include "utils.h"
#include "cleanup.h"

bool compareByScore(const Data &a, const Data &b);
std::string getCurrentDateTime();
std::string leftCellNumber(int n, int length);
void storeAchievement(int size, int score, int step, std::string elapsed_time, User &user);
void deleteAchievement(User &user);
void getAchievement(User &user);
void getLeaderboard();