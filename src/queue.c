#include "queue.h"

// ==================== REGULAR QUEUE OPERATIONS ====================

// Create a new queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        printf("❌ Memory allocation failed for queue!\n");
        return NULL;
    }
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

// Check if queue is empty
int isQueueEmpty(Queue* q) {
    if (q == NULL) return 1;
    return q->front == NULL;
}

// Enqueue operation
void enqueue(Queue* q, Flight* flight) {
    if (q == NULL || flight == NULL) {
        return;
    }
    
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        printf("❌ Memory allocation failed for queue node!\n");
        return;
    }
    
    newNode->flight = flight;
    newNode->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

// Dequeue operation
Flight* dequeue(Queue* q) {
    if (q == NULL || isQueueEmpty(q)) {
        return NULL;
    }
    
    QueueNode* temp = q->front;
    Flight* flight = temp->flight;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    q->size--;
    return flight;
}

// Peek operation
Flight* peek(Queue* q) {
    if (q == NULL || isQueueEmpty(q)) {
        return NULL;
    }
    return q->front->flight;
}

// Display queue contents
void displayQueue(Queue* q, const char* queueName) {
    if (q == NULL || isQueueEmpty(q)) {
        printf("\n📭 %s is empty.\n", queueName);
        return;
    }
    
    printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║  %-58s  ║\n", queueName);
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    printf("Queue Size: %d\n", q->size);
    
    QueueNode* temp = q->front;
    int pos = 1;
    while (temp != NULL) {
        char timeStr[10];
        timeToString(temp->flight->scheduledTime, timeStr);
        printf("%d. %s | %s | %s | Priority: %s | Time: %s\n", 
               pos++,
               temp->flight->flightID,
               temp->flight->airline,
               operationToString(temp->flight->operation),
               priorityToString(temp->flight->priority),
               timeStr);
        temp = temp->next;
    }
}

// Free queue
void freeQueue(Queue* q) {
    if (q == NULL) return;
    
    while (!isQueueEmpty(q)) {
        dequeue(q);
    }
    free(q);
}

// ==================== PRIORITY QUEUE OPERATIONS (MIN-HEAP) ====================

// Create priority queue
PriorityQueue* createPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (pq == NULL) {
        printf("❌ Memory allocation failed for priority queue!\n");
        return NULL;
    }
    pq->size = 0;
    return pq;
}

// Check if priority queue is empty
int isPriorityQueueEmpty(PriorityQueue* pq) {
    if (pq == NULL) return 1;
    return pq->size == 0;
}

// Compare two flights (returns negative if f1 has higher priority than f2)
int compareFlight(Flight* f1, Flight* f2) {
    if (f1 == NULL || f2 == NULL) return 0;
    
    // First, compare emergency types (INFLIGHT_EMERGENCY=4 > AIRPLANE_DEFECT=3 > PILOT_UNAVAILABLE=2 > AIRPORT_DELAY=1)
    if (f1->emergencyType != f2->emergencyType) {
        return f2->emergencyType - f1->emergencyType; // Higher emergency type comes first
    }
    
    // Then, compare flight priority (EMERGENCY=3 > VIP=2 > SCHEDULED=1)
    if (f1->priority != f2->priority) {
        return f2->priority - f1->priority; // Higher priority comes first (min-heap for max priority)
    }
    
    // If same priority and emergency type, compare scheduled time (earlier time first)
    return f1->scheduledTime - f2->scheduledTime;
}

// Heapify up (for insertion)
void heapifyUp(PriorityQueue* pq, int index) {
    if (pq == NULL || index == 0) return;
    
    int parent = (index - 1) / 2;
    if (compareFlight(pq->flights[index], pq->flights[parent]) < 0) {
        // Swap
        Flight* temp = pq->flights[index];
        pq->flights[index] = pq->flights[parent];
        pq->flights[parent] = temp;
        heapifyUp(pq, parent);
    }
}

// Heapify down (for extraction)
void heapifyDown(PriorityQueue* pq, int index) {
    if (pq == NULL) return;
    
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if (left < pq->size && compareFlight(pq->flights[left], pq->flights[smallest]) < 0) {
        smallest = left;
    }
    
    if (right < pq->size && compareFlight(pq->flights[right], pq->flights[smallest]) < 0) {
        smallest = right;
    }
    
    if (smallest != index) {
        // Swap
        Flight* temp = pq->flights[index];
        pq->flights[index] = pq->flights[smallest];
        pq->flights[smallest] = temp;
        heapifyDown(pq, smallest);
    }
}

// Insert into priority queue
void insertPriorityQueue(PriorityQueue* pq, Flight* flight) {
    if (pq == NULL || flight == NULL) {
        return;
    }
    
    if (pq->size >= 100) {
        printf("❌ Priority queue is full!\n");
        return;
    }
    
    pq->flights[pq->size] = flight;
    heapifyUp(pq, pq->size);
    pq->size++;
}

// Extract minimum (highest priority) from priority queue
Flight* extractMin(PriorityQueue* pq) {
    if (pq == NULL || isPriorityQueueEmpty(pq)) {
        return NULL;
    }
    
    Flight* minFlight = pq->flights[0];
    pq->flights[0] = pq->flights[pq->size - 1];
    pq->size--;
    
    if (pq->size > 0) {
        heapifyDown(pq, 0);
    }
    
    return minFlight;
}

// Peek minimum
Flight* peekMin(PriorityQueue* pq) {
    if (pq == NULL || isPriorityQueueEmpty(pq)) {
        return NULL;
    }
    return pq->flights[0];
}

// Display priority queue
void displayPriorityQueue(PriorityQueue* pq, const char* queueName) {
    if (pq == NULL || isPriorityQueueEmpty(pq)) {
        printf("\n📭 %s is empty.\n", queueName);
        return;
    }
    
    printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║  %-58s  ║\n", queueName);
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    printf("Queue Size: %d\n", pq->size);
    
    for (int i = 0; i < pq->size; i++) {
        if (pq->flights[i] != NULL) {
            char timeStr[10];
            timeToString(pq->flights[i]->scheduledTime, timeStr);
            printf("%d. %s | %s | %s | Priority: %s | Time: %s\n", 
                   i+1,
                   pq->flights[i]->flightID,
                   pq->flights[i]->airline,
                   operationToString(pq->flights[i]->operation),
                   priorityToString(pq->flights[i]->priority),
                   timeStr);
        }
    }
}

// Free priority queue
void freePriorityQueue(PriorityQueue* pq) {
    if (pq != NULL) {
        free(pq);
    }
}