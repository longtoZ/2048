#include "list.h"

ListNode::ListNode(Data data)
{
    this->data = data;
    this->next = nullptr;
}

void List::init()
{
    head = nullptr;
    size = 0;
}

void List::insertHead(Data data)
{
    ListNode *node = new ListNode(data);

    if (head == nullptr)
    {
        head = node;
    }
    else
    {
        node->next = head;
        head = node;
    }

    size++;
}

void List::insertTail(Data data)
{
    ListNode *node = new ListNode(data);

    if (head == nullptr)
    {
        head = node;
    }
    else
    {
        ListNode *curr = head;

        while (curr->next != nullptr)
        {
            curr = curr->next;
        }

        curr->next = node;
    }

    size++;
}

void List::swap(ListNode*& head, ListNode* node1, ListNode* node2) {
    if ((node1->data).score == (node2->data).score) return;

    // Find previous nodes of node1 and node2
    ListNode *prev1 = nullptr, *prev2 = nullptr, *current = head;
    while (current && (prev1 == nullptr || prev2 == nullptr)) {
        if (current->next == node1) {
            prev1 = current;
        }
        if (current->next == node2) {
            prev2 = current;
        }
        current = current->next;
    }

    // If node1 or node2 are not present, do nothing
    if (node1 == nullptr || node2 == nullptr) return;

    // If node1 is head of linked list
    if (prev1 != nullptr) {
        prev1->next = node2;
    } else {
        head = node2;
    }

    // If node2 is head of linked list
    if (prev2 != nullptr) {
        prev2->next = node1;
    } else {
        head = node1;
    }

    // Swap next pointers
    ListNode* temp = node2->next;
    node2->next = node1->next;
    node1->next = temp;

}

void List::sort()
{
    ListNode *node = head;
    bool swapped;

    for (int i = 0; i < size - 1; i++)
    {
        node = head;
        swapped = false;

        for (int j = 0; j < size - i - 1; j++)
        {
            if (node->next != nullptr)
            {
                if ((node->data).score < (node->next->data).score)
                {
                    swap(head, node, node->next);
                    swapped = true;
                } else {
                    node = node->next;
                }
            }

        if (!swapped)
            break;
            
        }
    }
}