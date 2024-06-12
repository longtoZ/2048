#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include "keys.h"
#include "struct.h"
#include "utils.h"
#include "cleanup.h"
using namespace std;

int userLogin(User &user);
int userRegister(User &user);
int userDelete(User &user);