#ifndef QUEUE_H
#define QUEUE_H

#include "flight.h"

// Queue node for regular queue
typedef struct QueueNode {
    Flight* flight;
    struct QueueNode* next;
} QueueNode;

// Queue structure
typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
    int size;
} Queue;

// Priority Queue node (for min-heap implementation)
typedef struct {
    Flight* flights[100]; // Max 100 flights in priority queue
    int size;
} PriorityQueue;

// Regular Queue operations
Queue* createQueue();
int isQueueEmpty(Queue* q);
void enqueue(Queue* q, Flight* flight);
Flight* dequeue(Queue* q);
Flight* peek(Queue* q);
void displayQueue(Queue* q, const char* queueName);
void freeQueue(Queue* q);

// Priority Queue operations (Min-Heap)
PriorityQueue* createPriorityQueue();
int isPriorityQueueEmpty(PriorityQueue* pq);
void insertPriorityQueue(PriorityQueue* pq, Flight* flight);
Flight* extractMin(PriorityQueue* pq);
Flight* peekMin(PriorityQueue* pq);
void displayPriorityQueue(PriorityQueue* pq, const char* queueName);
void heapifyUp(PriorityQueue* pq, int index);
void heapifyDown(PriorityQueue* pq, int index);
int compareFlight(Flight* f1, Flight* f2);
void freePriorityQueue(PriorityQueue* pq);

#endif
