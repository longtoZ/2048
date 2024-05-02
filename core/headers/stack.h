#pragma once
#include <iostream>
#include "struct.h"
#include "utils.h"

struct StackNode {
    Gameplay gameplay;
    StackNode* next;

    StackNode(Gameplay gameplay);
};

struct Stack {
    StackNode* head;
    int size;
    
    void init();

    void push(Gameplay gameplay);

    void pop();

    Gameplay top();

    bool empty();
};