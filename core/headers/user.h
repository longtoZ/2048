#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include "keys.h"
#include "struct.h"
#include "utils.h"
using namespace std;

int userLogin(User &user);
void userRegister();
int userDelete(User &user);