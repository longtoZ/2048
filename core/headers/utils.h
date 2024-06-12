#pragma once
#include <conio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <windows.h>
#include <regex>
#include "struct.h"
#include "keys.h"
#include "effect.h"
using namespace std::chrono;
using namespace std;

bool hasSpecialChar(string& str);
bool fileExist (string name);
bool isStrongPassword(string password);

char* convertStringToChar(string str);

// Source: https://stackoverflow.com/questions/31255486/how-do-i-convert-a-stdchronotime-point-to-long-and-back
high_resolution_clock::time_point convertLongToTime(long long milliseconds);

int generateSelections(string options[], int n, string pre, string post, string align = "left");
int** createEmptyBoard(int n);
int** createEmptyPos(int n);

// Source: https://stackoverflow.com/questions/31255486/how-do-i-convert-a-stdchronotime-point-to-long-and-back
long long convertTimeToLong(const high_resolution_clock::time_point& current_time);
// Source: https://stackoverflow.com/questions/31657511/how-to-get-the-difference-between-two-points-in-time-in-milliseconds
long long calculateDurationInMilliseconds(long long start_time);

// Source: https://www.geeksforgeeks.org/c-program-delete-file/
//         https://www.geeksforgeeks.org/rename-function-in-ccpp/
void deleteInfo(string username);
void createEmptyFile(string path);
void createUserFiles(string username);
void deleteUserFiles(string username);
// Source: https://www.geeksforgeeks.org/how-to-use-gotoxy-in-codeblocks/
void gotoxy(int x, int y);
// Source: https://stackoverflow.com/questions/34522617/ignore-keyboard-input-during-sleep-in-c
void sleepIgnoreInput(int miliseconds);

// Source: https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
ScreenSize getScreenSize();
// Source: https://stackoverflow.com/questions/70696610/is-there-an-easier-way-to-get-the-current-time-in-hhmmss-format
string getCurrentDateTime();
string convertCharToString(char* charArray);
string calculateElapsedTimeString(const high_resolution_clock::time_point& start_time, const milliseconds& extraTime = milliseconds(0));
string formatDateStr(char* date);
string replaceAll(string& original, string& toReplace, string& replacement);
string setLeftAlignSize();
string setCenterAlignSize(int length);
// Source: https://www.w3schools.com/python/python_regex.asp
//         https://www.geeksforgeeks.org/regex_replace-in-cpp-replace-the-match-of-a-string-using-regex_replace/
string replaceAllRegex(string input);