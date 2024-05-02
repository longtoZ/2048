#include "list.h"

ListNode::ListNode(Data data) {
    this->data = data;
    this->next = nullptr;
}

void List::init() {
    head = nullptr;
    size = 0;
}

void List::insertHead(Data data) {
    ListNode* node = new ListNode(data);

    if (head == nullptr) {
        head = node;
    } else {
        node->next = head;
        head = node;
    }

    size++;
}

void List::insertTail(Data data) {
    ListNode* node = new ListNode(data);

    if (head == nullptr) {
        head = node;
    } else {
        ListNode* curr = head;

        while (curr->next != nullptr) {
            curr = curr->next;
        }

        curr->next = node;
    }

    size++;
}

void List::swap(ListNode* &p1, ListNode* &p2) {
    std::string username = (p1->data).username;
    std::string date = (p1->data).date;
    int size = (p1->data).size;
    int score = (p1->data).score;
    int step = (p1->data).step;
    std::string interval = (p1->data).interval;

    (p1->data).username = (p2->data).username;
    (p1->data).date = (p2->data).date;
    (p1->data).size = (p2->data).size;
    (p1->data).score = (p2->data).score;
    (p1->data).step = (p2->data).step;
    (p1->data).interval = (p2->data).interval;

    (p2->data).username = username;
    (p2->data).date = date;
    (p2->data).size = size;
    (p2->data).score = score;
    (p2->data).step = step;
    (p2->data).interval = interval;
}

void List::sort() {
    ListNode* p1 = head;

    for (int i=0; i<size-1; i++) {
        p1 = head;

        for (int j=0; j<size-i-1; j++) {
            if (p1->next != nullptr) {
                if ((p1->data).score < (p1->next->data).score) {
                    swap(p1, p1->next);
                } else if ((p1->data).score == (p1->next->data).score) {
                    if ((p1->data).step < (p1->next->data).step) {
                        swap(p1, p1->next);
                    }
                }
            } 

            p1 = p1->next;

        }

    }
}