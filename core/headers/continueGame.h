#pragma once
#include <iostream>
#include <fstream>
#include "utils.h"
#include "struct.h"
#include "keys.h"

void saveBoard(Gameplay &gameplay, User &user);
void getPrevBoard(Gameplay &gameplay, User &user);