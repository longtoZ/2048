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

void List::swap(ListNode *&head, ListNode *node1, ListNode *node2)
{
    if ((node1->data).score == (node2->data).score)
        return;

    // Find previous nodes of node1 and node2
    ListNode *prev1 = nullptr, *prev2 = nullptr, *current = head;
    while (current && (prev1 == nullptr || prev2 == nullptr))
    {
        if (current->next == node1)
        {
            prev1 = current;
        }
        if (current->next == node2)
        {
            prev2 = current;
        }
        current = current->next;
    }

    // If node1 or node2 are not present, do nothing
    if (node1 == nullptr || node2 == nullptr)
        return;

    // If node1 is head of linked list
    if (prev1 != nullptr)
    {
        prev1->next = node2;
    }
    else
    {
        head = node2;
    }

    // If node2 is head of linked list
    if (prev2 != nullptr)
    {
        prev2->next = node1;
    }
    else
    {
        head = node1;
    }

    // Swap next pointers
    ListNode *temp = node2->next;
    node2->next = node1->next;
    node1->next = temp;
}

ListNode *getTail(ListNode *head)
{
    ListNode *curr = head;
    while (curr != nullptr && curr->next != nullptr)
    {
        curr = curr->next;
    }
    return curr;
}

void quickSort(ListNode *&head, ListNode *&tail)
{
    if (head == tail || head == nullptr || tail == nullptr)
    {
        return;
    }

    ListNode *SH = nullptr, *ST = nullptr, *LH = nullptr, *LT = nullptr;
    ListNode *curr = head, *pivot = tail;

    while (curr != pivot)
    {
        if ((curr->data).score > (pivot->data).score)
        {
            if (ST == nullptr)
            {
                SH = ST = curr;
            }
            else
            {
                ST->next = curr;
                ST = curr;
            }
        }
        else
        {
            if (LT == nullptr)
            {
                LH = LT = curr;
            }
            else
            {
                LT->next = curr;
                LT = curr;
            }
        }

        curr = curr->next;
    }

    pivot->next = nullptr;

    if (ST != nullptr)
    {
        ST->next = nullptr;
    }

    if (LT != nullptr)
    {
        LT->next = nullptr;
    }

    quickSort(SH, ST);
    quickSort(LH, LT);

    if (ST != nullptr)
    {
        ST->next = pivot;
        head = SH;
    }
    else
    {
        head = pivot;
    }

    if (LT != nullptr)
    {
        pivot->next = LH;
        tail = LT;
    }
    else
    {
        tail = pivot;
    }
}

void List::sort()
{
    if (head == nullptr)
        return;

    ListNode *tail = getTail(head);
    quickSort(head, tail);
}