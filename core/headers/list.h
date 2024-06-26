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
    // Source: https://www.geeksforgeeks.org/swap-nodes-in-a-linked-list-without-swapping-data/
    void swap(ListNode*& head, ListNode* node1, ListNode* node2);
    void sort();
};