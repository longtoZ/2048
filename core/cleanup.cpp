#include "cleanup.h"

void cleanChar(char* &s) {
    delete s;
}

void cleanBoard(Gameplay &gameplay) {
    int n = gameplay.size;
    int** &board = gameplay.board;

    for (int i=0; i<n; i++) {
        delete[] board[i];
    }

    board = nullptr;
    delete[] board;
}

void cleanEmptyPos(Gameplay &gameplay) {
    int** &emptyPos = gameplay.emptyPos;
    int &emptyLeft = gameplay.emptyLeft;

    for (int i=0; i<emptyLeft; i++) {
        delete[] emptyPos[i];
    }

    emptyPos = nullptr;
    delete[] emptyPos;
}

void cleanStack(Stack &stack) {
    StackNode* &head = stack.head;

    while (head != nullptr) {
        cleanBoard(head->gameplay);
        cleanEmptyPos(head->gameplay);

        StackNode* tmp = head;
        head = head->next;

        delete tmp;
    }

    stack.size = 0;
}

void cleanList(List &list) {
    ListNode* &head = list.head;

    while (head != nullptr) {
        ListNode* tmp = head;
        cleanChar((tmp->data).username);
        cleanChar((tmp->data).date);
        cleanChar((tmp->data).interval);
        head = head->next;
        delete tmp;
    }

    list.size = 0;
}

void cleanUser(User &user) {
    cleanChar(user.username);
    cleanChar(user.password);
}