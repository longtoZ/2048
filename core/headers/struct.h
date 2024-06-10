#pragma once
#include <string>

struct Gameplay {
    int** board;
    int size;
    int** emptyPos;
    int emptyLeft;
    int score;
    int step;
    bool canUndoRedo = true;
    long long startTime;
    long long duration = 0;
};

struct Position {
    int pos1_x;
    int pos1_y;
    int pos2_x;
    int pos2_y;
};

struct InitNumber {
    int num1;
    int num2;
};

struct Data {
    char* username;
    char* date;
    int size;
    int score = 0;
    int step;
    char* interval;
};

struct User {
    char* username;
    char* password;
};

struct ScreenSize {
    int width;
    int height;
};