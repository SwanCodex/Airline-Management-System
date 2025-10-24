#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "flight.h"
#include "queue.h"

// Scheduling algorithms (1-based for user input)
typedef enum {
    FCFS = 1,              // First Come First Serve
    PRIORITY_SCHED = 2,    // Priority Scheduling
    SJF = 3,               // Shortest Job First
    ROUND_ROBIN = 4        // Round Robin
} SchedulingAlgorithm;

// Runway structure
typedef struct Runway {
    char name[20];
    Flight* currentFlight;
    int availableAt;  // Time when runway becomes free
    int totalFlightsHandled;
} Runway;

// Scheduler structure
typedef struct Scheduler {
    Runway runways[2];  // Two runways (A and B)
    Queue* landingQueue;
    Queue* takeoffQueue;
    PriorityQueue* priorityLandingQueue;
    PriorityQueue* priorityTakeoffQueue;
    Flight* completedFlights;
    int currentTime;
    SchedulingAlgorithm algorithm;
    int totalWaitingTime;
    int totalFlightsProcessed;
} Scheduler;

// Scheduler functions
Scheduler* createScheduler(SchedulingAlgorithm algo);
void initializeRunways(Scheduler* scheduler);
void addFlightToScheduler(Scheduler* scheduler, Flight* flight);
void processScheduling(Scheduler* scheduler);
void displayDashboard(Scheduler* scheduler);
void runSimulation(Scheduler* scheduler, int duration);
void handleEmergency(Scheduler* scheduler);
void generateStatistics(Scheduler* scheduler);
void saveLogToFile(Scheduler* scheduler, const char* filename);
void freeScheduler(Scheduler* scheduler);

// Algorithm-specific functions
void scheduleFCFS(Scheduler* scheduler);
void schedulePriority(Scheduler* scheduler);
void scheduleSJF(Scheduler* scheduler);
void scheduleRoundRobin(Scheduler* scheduler);

// Helper functions
void assignFlightToRunway(Scheduler* scheduler, Flight* flight, int runwayIndex);
void completeFlightOperation(Scheduler* scheduler, int runwayIndex);
int findAvailableRunway(Scheduler* scheduler);
void displayRunwayStatus(Scheduler* scheduler);

#endif
