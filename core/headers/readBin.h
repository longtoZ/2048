#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include "list.h"
using namespace std;

void writeUsersToFile(string& filename, List& users);
void readUsersFromFile(string& filename, Data users[], int& maxUsers);