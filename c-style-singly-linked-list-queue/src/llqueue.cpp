#include "../include/llqueue.h"
#include "../include/player.h"

Queue *newQueue()
{
    return new Queue{0, nullptr, nullptr};
}

LLNode *newLLNode(Player *p)
{
    if (p)
        return new LLNode{nullptr, p};
    return NULL;
}

void deleteLLNode(LLNode *lln)
{
    if (lln)
        delete lln;
}

void queuePushPlayerEntry(Queue *q, Player *entry)
{
    if (q && entry)
    {
        LLNode *secondToLast = q->tail;
        LLNode *last = newLLNode(entry);

        if (secondToLast)
        {
            secondToLast->next = last;
            q->tail = last;
        }
        else
        {
            q->head = last;
            q->tail = last;
        }
        q->size++;
    }
}

void queuePopPlayerEntry(Queue *q)
{
    if (q && q->head)
    {
        LLNode *nextNode = q->head->next;

        deletePlayer(q->head->entry);
        deleteLLNode(q->head);
        q->head = nextNode;
        q->size--;
        if (q->size == 0)
        {
            q->tail = nullptr;
        }
    }
}

Player *queueFront(Queue *q)
{
    if (q && q->size > 0)
        return q->head->entry;
    return NULL;
}

Player *queueBack(Queue *q)
{
    if (q && q->size > 0)
        return q->tail->entry;
    return NULL;
}

std::size_t queueSize(const Queue *q)
{
    return q->size;
}

void printQueue(const Queue *q)
{
    if (q && q->size > 0)
    {
        LLNode *currentNode = q->head;

        for (int indx = 0; indx < static_cast<int>(q->size); indx++)
        {
            printPlayer(currentNode->entry);
            currentNode = currentNode->next;
        }

        std::cout << std::endl;
    }
}

void deleteQueue(Queue *q)
{
    if (q)
    {
        if (q->size > 0)
        {
            LLNode *currentNode = q->head;
            LLNode *nextNode = q->head->next;

            for (int indx = 0; indx < static_cast<int>(q->size); indx++)
            {
                deletePlayer(currentNode->entry);
                deleteLLNode(currentNode);

                if (indx != static_cast<int>(q->size - 1))
                {
                    currentNode = nextNode;
                    nextNode = currentNode->next;
                }
            }
        }
        delete q;
    }
}