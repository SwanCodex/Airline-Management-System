#ifndef FLIGHT_H
#define FLIGHT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Flight priority levels (1-based for user input)
typedef enum {
    SCHEDULED = 1,
    VIP = 2,
    EMERGENCY = 3
} Priority;

// Flight status
typedef enum {
    WAITING = 0,
    IN_PROGRESS = 1,
    COMPLETED = 2
} Status;

// Flight operation type
typedef enum {
    LANDING = 0,
    TAKEOFF = 1
} Operation;

// Flight structure
typedef struct Flight {
    char flightID[50];
    char airline[50];
    char source[50];
    char destination[50];
    int scheduledTime; // in minutes from midnight
    Priority priority;
    Status status;
    Operation operation;
    int processingTime; // time needed for landing/takeoff (in minutes)
    struct Flight* next;
} Flight;

// Flight linked list functions
Flight* createFlight(const char* id, const char* airline, const char* src, 
                     const char* dest, int time, Priority pri, Operation op, int procTime);
void addFlight(Flight** head, Flight* newFlight);
void displayFlight(Flight* flight);
void displayAllFlights(Flight* head);
Flight* findFlight(Flight* head, const char* id);
void deleteFlight(Flight** head, const char* id);
void freeFlightList(Flight** head);
int countFlights(Flight* head);

// Utility functions
const char* priorityToString(Priority p);
const char* statusToString(Status s);
const char* operationToString(Operation o);
void timeToString(int minutes, char* buffer);

#endif
