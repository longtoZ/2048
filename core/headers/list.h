#pragma once
#include <iostream>
#include "struct.h"

struct ListNode {
    Data data;
    ListNode* next;

    ListNode(Data data);
};

struct List {
    ListNode* head;
    int size;

    void init();
    void insertHead(Data data);
    void insertTail(Data data);
    void swap(ListNode* &p1, ListNode* &p2);
    void sort();
};