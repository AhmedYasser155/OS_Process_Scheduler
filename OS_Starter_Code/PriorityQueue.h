#include"PCB.h"

struct PCBNode{
    struct PCB pcb;
    struct PCBNode* next;
};

struct PriorityQueue{
    struct PCBNode* head;
};

struct PCBNode GenerateNode(struct PCB pcb)
{
    struct PCBNode New;
    New.pcb = pcb;
    New.next = NULL;
    return New;
}

void initializeQueue(struct PriorityQueue* que)
{
    que->head = NULL;
}

void enQueue(struct PriorityQueue* que, struct PCBNode* newNode)
{
    if(que->head == NULL)
    {
        que->head = newNode;
    }
    else
    {
        struct PCBNode* next = que->head;
        while(next->next != NULL)
        {
            next = next->next;
        }
        next->next = newNode;
    }
}

void InsertAccordingToPriority(struct PriorityQueue* que, struct PCBNode* newNode)
{
    if(que->head == NULL)
    {
        que->head = newNode;
    }
    else
    {
        if(que->head->pcb.Priority > newNode->pcb.Priority)
        {
            newNode->next = que->head;
            que->head = newNode;
        }
        else
        {
            struct PCBNode* next = que->head;
            while(next->next != NULL && next->next->pcb.Priority < newNode->pcb.Priority)
            {
                next = next->next;
            }
            if(next->next != NULL)
            {
                newNode->next = next->next;
                next->next = newNode;
            }
            else
            {
                next->next = newNode;
            }
        }
    }
}

void InsertAccordingToArrivalTime(struct PriorityQueue* que, struct PCBNode* newNode)
{
    if(que->head == NULL)
    {
        que->head = newNode;
    }
    else
    {
        if(que->head->pcb.ArrTime > newNode->pcb.ArrTime)
        {
            newNode->next = que->head;
            que->head = newNode;
        }
        else
        {
            struct PCBNode* next = que->head;
            while(next->next != NULL && next->next->pcb.ArrTime < newNode->pcb.ArrTime)
            {
                next = next->next;
            }
            if(next->next != NULL)
            {
                newNode->next = next->next;
                next->next = newNode;
            }
            else
            {
                next->next = newNode;
            }
        }
    }
}

void InsertAccordingToReaminingTime(struct PriorityQueue* que, struct PCBNode* newNode)
{
    if(que->head == NULL)
    {
        que->head = newNode;
    }
    else
    {
        if(que->head->pcb.RunTime > newNode->pcb.RunTime)
        {
            newNode->next = que->head;
            que->head = newNode;
        }
        else
        {
            struct PCBNode* next = que->head;
            while(next->next != NULL && next->next->pcb.RunTime < newNode->pcb.RunTime)
            {
                next = next->next;
            }
            if(next->next != NULL)
            {
                newNode->next = next->next;
                next->next = newNode;
            }
            else
            {
                next->next = newNode;
            }
        }
    }
}

void DeQueue(struct PriorityQueue* que, struct PCB* tosetPCB)
{
    if(que->head != NULL)
    {
        struct PCBNode* node = que->head;
        que->head = que->head->next;
        CopyPCB(tosetPCB, node->pcb);
        node = NULL;
    }
    else
    {
        printf("null state\n");
        tosetPCB = NULL;
    }
}

int countNodes(struct PriorityQueue* a)
{
    int iter = 0;
    struct PCBNode* n;
    n = a->head;
    while(n!= NULL)
    {
        iter = iter + 1;
        n = n->next;
    }
    return iter;
}
