#pragma once
#include <string>

struct Gameplay {
    int** board;
    int size;
    int** emptyPos;
    int emptyLeft;
    int score;
    int step;
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
    std::string username;
    std::string date;
    int size;
    int score = 0;
    int step;
    std::string interval;
};

struct User {
    std::string username;
    std::string password;
};