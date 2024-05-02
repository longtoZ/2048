#pragma once
#include <iomanip>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <bits/stdc++.h> 
#include <cctype>
#include "struct.h"
using namespace std::chrono;
using namespace std;

int** createEmptyBoard(int n);
int** createEmptyPos(int n);
std::string getCurrentDateTime();
char* convertStringToChar(const string& str);
bool compareByScore(const Data &a, const Data &b);
void storeBestScore(User &user);
Data getBestScore(User &user);
std::string calculate_elapsed_time_string(const high_resolution_clock::time_point& start_time);
void createDirectory(const std::string& path);
void deleteDirectory(const std::string& path);
void deleteInfo(string username);
bool hasSpecialChar(const std::string& str);