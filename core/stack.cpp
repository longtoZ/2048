#include "stack.h"

StackNode::StackNode(Gameplay gameplay) {
    (this->gameplay).board = createEmptyBoard(gameplay.size);
    (this->gameplay).emptyPos = createEmptyPos(gameplay.emptyLeft);

    for (int i=0; i<gameplay.size; i++) {
        for (int j=0; j<gameplay.size; j++) {
            (this->gameplay).board[i][j] = gameplay.board[i][j];
        }
    }

    for (int i=0; i<gameplay.emptyLeft; i++) {
        (this->gameplay).emptyPos[i][0] = gameplay.emptyPos[i][0];
        (this->gameplay).emptyPos[i][1] = gameplay.emptyPos[i][1];
    }

    (this->gameplay).size = gameplay.size;
    (this->gameplay).emptyLeft = gameplay.emptyLeft;
    (this->gameplay).score = gameplay.score;
    (this->gameplay).step = gameplay.step;

    this->next = nullptr;
}

void Stack::init() {
    head = nullptr;
    size = 0;
}

void Stack::push(Gameplay gameplay) {
    StackNode* node = new StackNode(gameplay);

    if (head == nullptr) {
        head = node;
    } else {
        node->next = head;
        head = node;
    }

    size++;
}

void Stack::pop() {

    StackNode* tmp = head;

    head = head->next;
    delete tmp;
    
    size--;
}

Gameplay Stack::top() {
    return head->gameplay;
}

bool Stack::empty() {
    return head==nullptr;
}