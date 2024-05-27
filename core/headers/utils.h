#pragma once
#include <iomanip>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <bits/stdc++.h> 
#include <cctype>
#include "struct.h"
#include "keys.h"
using namespace std::chrono;
using namespace std;

int** createEmptyBoard(int n);
int** createEmptyPos(int n);
string getCurrentDateTime();
char* convertStringToChar(const string& str);
bool compareByScore(const Data &a, const Data &b);
string calculate_elapsed_time_string(const high_resolution_clock::time_point& start_time);
void createDirectory(string path);
void deleteDirectory(const string& path);
void deleteInfo(string username);
bool hasSpecialChar(const string& str);
char* formatDateChar(char* date);
string replaceAll(const string& original, const string& toReplace, const string& replacement);
void createEmptyFile(string path);
bool fileExist (const string& name);
void createUserFiles(const string& username);
int generateSelections(string options[], int n, string pre, string post);