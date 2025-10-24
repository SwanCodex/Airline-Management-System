#include "scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
    #include <windows.h>
    #define sleep(x) Sleep((x) * 1000)
#else
    #include <unistd.h>
#endif

// Create scheduler
Scheduler* createScheduler(SchedulingAlgorithm algo) {
    Scheduler* scheduler = (Scheduler*)malloc(sizeof(Scheduler));
    if (scheduler == NULL) {
        printf("❌ Memory allocation failed for scheduler!\n");
        return NULL;
    }
    
    scheduler->landingQueue = createQueue();
    scheduler->takeoffQueue = createQueue();
    scheduler->priorityLandingQueue = createPriorityQueue();
    scheduler->priorityTakeoffQueue = createPriorityQueue();
    scheduler->completedFlights = NULL;
    scheduler->currentTime = 600; // Start at 10:00 AM
    scheduler->algorithm = algo;
    scheduler->totalWaitingTime = 0;
    scheduler->totalFlightsProcessed = 0;
    
    initializeRunways(scheduler);
    return scheduler;
}

// Initialize runways
void initializeRunways(Scheduler* scheduler) {
    if (scheduler == NULL) return;
    
    strcpy(scheduler->runways[0].name, "Runway A");
    scheduler->runways[0].currentFlight = NULL;
    scheduler->runways[0].availableAt = 600;
    scheduler->runways[0].totalFlightsHandled = 0;
    
    strcpy(scheduler->runways[1].name, "Runway B");
    scheduler->runways[1].currentFlight = NULL;
    scheduler->runways[1].availableAt = 600;
    scheduler->runways[1].totalFlightsHandled = 0;
}

// Add flight to appropriate queue
void addFlightToScheduler(Scheduler* scheduler, Flight* flight) {
    if (scheduler == NULL || flight == NULL) return;
    
    if (scheduler->algorithm == PRIORITY_SCHED) {
        if (flight->operation == LANDING) {
            insertPriorityQueue(scheduler->priorityLandingQueue, flight);
        } else {
            insertPriorityQueue(scheduler->priorityTakeoffQueue, flight);
        }
    } else {
        if (flight->operation == LANDING) {
            enqueue(scheduler->landingQueue, flight);
        } else {
            enqueue(scheduler->takeoffQueue, flight);
        }
    }
    printf("✈️  Flight %s added to %s queue\n", 
           flight->flightID, 
           operationToString(flight->operation));
}

// Find available runway
int findAvailableRunway(Scheduler* scheduler) {
    if (scheduler == NULL) return -1;
    
    for (int i = 0; i < 2; i++) {
        if (scheduler->runways[i].currentFlight == NULL && 
            scheduler->runways[i].availableAt <= scheduler->currentTime) {
            return i;
        }
    }
    return -1; // No runway available
}

// Assign flight to runway
void assignFlightToRunway(Scheduler* scheduler, Flight* flight, int runwayIndex) {
    if (scheduler == NULL || flight == NULL || runwayIndex < 0 || runwayIndex > 1) return;
    
    char timeStr[10];
    timeToString(scheduler->currentTime, timeStr);
    
    scheduler->runways[runwayIndex].currentFlight = flight;
    scheduler->runways[runwayIndex].availableAt = scheduler->currentTime + flight->processingTime;
    flight->status = IN_PROGRESS;
    
    printf("\n[Time %s] ✈️  Flight %s (%s) %s on %s... (Duration: %d min)\n",
           timeStr,
           flight->flightID,
           flight->airline,
           flight->operation == LANDING ? "landing" : "taking off",
           scheduler->runways[runwayIndex].name,
           flight->processingTime);
}

// Complete flight operation
void completeFlightOperation(Scheduler* scheduler, int runwayIndex) {
    if (scheduler == NULL || runwayIndex < 0 || runwayIndex > 1) return;
    
    Flight* flight = scheduler->runways[runwayIndex].currentFlight;
    if (flight == NULL) return;
    
    char timeStr[10];
    timeToString(scheduler->currentTime, timeStr);
    
    flight->status = COMPLETED;
    printf("[Time %s] ✅ Flight %s completed %s on %s\n",
           timeStr,
           flight->flightID,
           operationToString(flight->operation),
           scheduler->runways[runwayIndex].name);
    
    // Add to completed flights
    addFlight(&scheduler->completedFlights, flight);
    
    // Update statistics
    scheduler->runways[runwayIndex].totalFlightsHandled++;
    scheduler->totalFlightsProcessed++;
    int waitTime = scheduler->currentTime - flight->scheduledTime;
    if (waitTime > 0) {
        scheduler->totalWaitingTime += waitTime;
    }
    
    // Free runway
    scheduler->runways[runwayIndex].currentFlight = NULL;
}

// FCFS Scheduling
void scheduleFCFS(Scheduler* scheduler) {
    if (scheduler == NULL) return;
    
    // Check if any runway operations are complete
    for (int i = 0; i < 2; i++) {
        if (scheduler->runways[i].currentFlight != NULL &&
            scheduler->runways[i].availableAt <= scheduler->currentTime) {
            completeFlightOperation(scheduler, i);
        }
    }
    
    // Try to assign flights to available runways
    int runwayIndex = findAvailableRunway(scheduler);
    if (runwayIndex != -1) {
        // Priority: Landing over Takeoff
        Flight* flight = NULL;
        if (!isQueueEmpty(scheduler->landingQueue)) {
            flight = dequeue(scheduler->landingQueue);
        } else if (!isQueueEmpty(scheduler->takeoffQueue)) {
            flight = dequeue(scheduler->takeoffQueue);
        }
        
        if (flight != NULL) {
            assignFlightToRunway(scheduler, flight, runwayIndex);
        }
    }
}

// Priority Scheduling
void schedulePriority(Scheduler* scheduler) {
    if (scheduler == NULL) return;
    
    // Check if any runway operations are complete
    for (int i = 0; i < 2; i++) {
        if (scheduler->runways[i].currentFlight != NULL &&
            scheduler->runways[i].availableAt <= scheduler->currentTime) {
            completeFlightOperation(scheduler, i);
        }
    }
    
    // Try to assign flights to available runways
    int runwayIndex = findAvailableRunway(scheduler);
    if (runwayIndex != -1) {
        Flight* flight = NULL;
        // Priority: Landing over Takeoff, then by priority level
        if (!isPriorityQueueEmpty(scheduler->priorityLandingQueue)) {
            flight = extractMin(scheduler->priorityLandingQueue);
        } else if (!isPriorityQueueEmpty(scheduler->priorityTakeoffQueue)) {
            flight = extractMin(scheduler->priorityTakeoffQueue);
        }
        
        if (flight != NULL) {
            assignFlightToRunway(scheduler, flight, runwayIndex);
        }
    }
}

// SJF Scheduling (Shortest processing time first)
void scheduleSJF(Scheduler* scheduler) {
    if (scheduler == NULL) return;
    
    // Check if any runway operations are complete
    for (int i = 0; i < 2; i++) {
        if (scheduler->runways[i].currentFlight != NULL &&
            scheduler->runways[i].availableAt <= scheduler->currentTime) {
            completeFlightOperation(scheduler, i);
        }
    }
    
    // Find flight with shortest processing time
    int runwayIndex = findAvailableRunway(scheduler);
    if (runwayIndex != -1) {
        Flight* shortestFlight = NULL;
        Flight* tempFlight;
        Queue* tempQueue = createQueue();
        
        if (tempQueue == NULL) return;
        
        // Check landing queue
        while (!isQueueEmpty(scheduler->landingQueue)) {
            tempFlight = dequeue(scheduler->landingQueue);
            if (shortestFlight == NULL || tempFlight->processingTime < shortestFlight->processingTime) {
                if (shortestFlight != NULL) enqueue(tempQueue, shortestFlight);
                shortestFlight = tempFlight;
            } else {
                enqueue(tempQueue, tempFlight);
            }
        }
        
        // Restore landing queue
        while (!isQueueEmpty(tempQueue)) {
            enqueue(scheduler->landingQueue, dequeue(tempQueue));
        }
        
        // If no landing flights, check takeoff queue
        if (shortestFlight == NULL) {
            while (!isQueueEmpty(scheduler->takeoffQueue)) {
                tempFlight = dequeue(scheduler->takeoffQueue);
                if (shortestFlight == NULL || tempFlight->processingTime < shortestFlight->processingTime) {
                    if (shortestFlight != NULL) enqueue(tempQueue, shortestFlight);
                    shortestFlight = tempFlight;
                } else {
                    enqueue(tempQueue, tempFlight);
                }
            }
            
            // Restore takeoff queue
            while (!isQueueEmpty(tempQueue)) {
                enqueue(scheduler->takeoffQueue, dequeue(tempQueue));
            }
        }
        
        if (shortestFlight != NULL) {
            assignFlightToRunway(scheduler, shortestFlight, runwayIndex);
        }
        
        freeQueue(tempQueue);
    }
}

// Round Robin Scheduling
void scheduleRoundRobin(Scheduler* scheduler) {
    static int lastProcessed = 0; // 0 for landing, 1 for takeoff
    
    if (scheduler == NULL) return;
    
    // Check if any runway operations are complete
    for (int i = 0; i < 2; i++) {
        if (scheduler->runways[i].currentFlight != NULL &&
            scheduler->runways[i].availableAt <= scheduler->currentTime) {
            completeFlightOperation(scheduler, i);
        }
    }
    
    // Try to assign flights alternating between landing and takeoff
    int runwayIndex = findAvailableRunway(scheduler);
    if (runwayIndex != -1) {
        Flight* flight = NULL;
        
        if (lastProcessed == 0) {
            // Try landing first
            if (!isQueueEmpty(scheduler->landingQueue)) {
                flight = dequeue(scheduler->landingQueue);
                lastProcessed = 1;
            } else if (!isQueueEmpty(scheduler->takeoffQueue)) {
                flight = dequeue(scheduler->takeoffQueue);
            }
        } else {
            // Try takeoff first
            if (!isQueueEmpty(scheduler->takeoffQueue)) {
                flight = dequeue(scheduler->takeoffQueue);
                lastProcessed = 0;
            } else if (!isQueueEmpty(scheduler->landingQueue)) {
                flight = dequeue(scheduler->landingQueue);
            }
        }
        
        if (flight != NULL) {
            assignFlightToRunway(scheduler, flight, runwayIndex);
        }
    }
}

// Process scheduling based on selected algorithm
void processScheduling(Scheduler* scheduler) {
    if (scheduler == NULL) return;
    
    switch(scheduler->algorithm) {
        case FCFS:
            scheduleFCFS(scheduler);
            break;
        case PRIORITY_SCHED:
            schedulePriority(scheduler);
            break;
        case SJF:
            scheduleSJF(scheduler);
            break;
        case ROUND_ROBIN:
            scheduleRoundRobin(scheduler);
            break;
        default:
            printf("❌ Unknown scheduling algorithm!\n");
            break;
    }
}

// Display runway status
void displayRunwayStatus(Scheduler* scheduler) {
    if (scheduler == NULL) return;
    
    printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║                        RUNWAY STATUS                          ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    
    for (int i = 0; i < 2; i++) {
        printf("\n%s:\n", scheduler->runways[i].name);
        if (scheduler->runways[i].currentFlight != NULL) {
            char availableStr[10];
            timeToString(scheduler->runways[i].availableAt, availableStr);
            printf("  🛫 OCCUPIED - Flight %s (%s)\n", 
                   scheduler->runways[i].currentFlight->flightID,
                   scheduler->runways[i].currentFlight->airline);
            printf("  Available at: %s\n", availableStr);
        } else {
            printf("  ✅ AVAILABLE\n");
        }
        printf("  Total flights handled: %d\n", scheduler->runways[i].totalFlightsHandled);
    }
}

// Display comprehensive dashboard
void displayDashboard(Scheduler* scheduler) {
    if (scheduler == NULL) return;
    
    char timeStr[10];
    timeToString(scheduler->currentTime, timeStr);
    
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║          AIRPORT RUNWAY SCHEDULING SYSTEM DASHBOARD           ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    printf("Current Time: %s | Algorithm: ", timeStr);
    
    switch(scheduler->algorithm) {
        case FCFS: printf("First Come First Serve\n"); break;
        case PRIORITY_SCHED: printf("Priority Scheduling\n"); break;
        case SJF: printf("Shortest Job First\n"); break;
        case ROUND_ROBIN: printf("Round Robin\n"); break;
        default: printf("Unknown\n"); break;
    }
    
    displayRunwayStatus(scheduler);
    
    // Display queues
    if (scheduler->algorithm == PRIORITY_SCHED) {
        displayPriorityQueue(scheduler->priorityLandingQueue, "LANDING QUEUE (Priority)");
        displayPriorityQueue(scheduler->priorityTakeoffQueue, "TAKEOFF QUEUE (Priority)");
    } else {
        displayQueue(scheduler->landingQueue, "LANDING QUEUE");
        displayQueue(scheduler->takeoffQueue, "TAKEOFF QUEUE");
    }
    
    // Display completed flights count
    printf("\n📊 Total Flights Completed: %d\n", scheduler->totalFlightsProcessed);
}

// Run simulation
void runSimulation(Scheduler* scheduler, int duration) {
    if (scheduler == NULL) return;
    
    printf("\n🚀 Starting simulation for %d minutes...\n\n", duration);
    sleep(1);
    
    int endTime = scheduler->currentTime + duration;
    
    while (scheduler->currentTime < endTime) {
        processScheduling(scheduler);
        scheduler->currentTime++;
        
        // Small delay for visualization
        #ifdef _WIN32
            Sleep(100);
        #else
            usleep(100000);
        #endif
    }
    
    // Final processing
    for (int i = 0; i < 2; i++) {
        if (scheduler->runways[i].currentFlight != NULL &&
            scheduler->runways[i].availableAt <= scheduler->currentTime) {
            completeFlightOperation(scheduler, i);
        }
    }
    
    printf("\n✅ Simulation completed!\n");
}

// Handle emergency flight
void handleEmergency(Scheduler* scheduler) {
    if (scheduler == NULL) return;
    
    char id[50], airline[50], src[50], dest[50];
    int procTime;
    
    printf("\n🚨 EMERGENCY FLIGHT ALERT! 🚨\n");
    printf("Enter Flight ID: ");
    if (scanf("%49s", id) != 1) {
        printf("❌ Invalid input!\n");
        while(getchar() != '\n');
        return;
    }
    
    printf("Enter Airline: ");
    if (scanf("%49s", airline) != 1) {
        printf("❌ Invalid input!\n");
        while(getchar() != '\n');
        return;
    }
    
    printf("Enter Source: ");
    if (scanf("%49s", src) != 1) {
        printf("❌ Invalid input!\n");
        while(getchar() != '\n');
        return;
    }
    
    printf("Enter Destination: ");
    if (scanf("%49s", dest) != 1) {
        printf("❌ Invalid input!\n");
        while(getchar() != '\n');
        return;
    }
    
    printf("Enter Processing Time (minutes): ");
    if (scanf("%d", &procTime) != 1 || procTime < 1) {
        printf("❌ Invalid input! Using 9 minutes.\n");
        procTime = 9;
        while(getchar() != '\n');
    }
    while(getchar() != '\n'); // Clear buffer
    
    Flight* emergencyFlight = createFlight(id, airline, src, dest, 
                                          scheduler->currentTime, 
                                          EMERGENCY, LANDING, procTime);
    
    if (emergencyFlight != NULL) {
        printf("\n🔥 Emergency flight %s added with HIGHEST priority!\n", id);
        addFlightToScheduler(scheduler, emergencyFlight);
        
        // Immediately try to assign
        processScheduling(scheduler);
    } else {
        printf("❌ Failed to create emergency flight!\n");
    }
}

// Generate statistics
void generateStatistics(Scheduler* scheduler) {
    if (scheduler == NULL) return;
    
    printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║                     SYSTEM STATISTICS                         ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    
    printf("\n📊 Total Flights Processed: %d\n", scheduler->totalFlightsProcessed);
    
    if (scheduler->totalFlightsProcessed > 0) {
        float avgWaitTime = (float)scheduler->totalWaitingTime / scheduler->totalFlightsProcessed;
        printf("⏱️  Average Waiting Time: %.2f minutes\n", avgWaitTime);
    } else {
        printf("⏱️  Average Waiting Time: N/A\n");
    }
    
    printf("\n🛫 Runway Utilization:\n");
    for (int i = 0; i < 2; i++) {
        printf("  %s: %d flights handled\n", 
               scheduler->runways[i].name, 
               scheduler->runways[i].totalFlightsHandled);
    }
    
    printf("\n✅ Completed Flights:\n");
    if (scheduler->completedFlights == NULL) {
        printf("  No completed flights yet.\n");
    } else {
        Flight* temp = scheduler->completedFlights;
        int count = 1;
        while (temp != NULL) {
            printf("  %d. %s - %s (%s)\n", 
                   count++, temp->flightID, temp->airline, 
                   operationToString(temp->operation));
            temp = temp->next;
        }
    }
}

// Save log to file
void saveLogToFile(Scheduler* scheduler, const char* filename) {
    if (scheduler == NULL || filename == NULL) return;
    
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("❌ Error opening file for writing!\n");
        return;
    }
    
    fprintf(file, "=======================================================\n");
    fprintf(file, "   AIRPORT RUNWAY SCHEDULING SYSTEM - OPERATION LOG\n");
    fprintf(file, "=======================================================\n\n");
    
    time_t now;
    time(&now);
    fprintf(file, "Report Generated: %s\n", ctime(&now));
    
    fprintf(file, "\n--- SYSTEM CONFIGURATION ---\n");
    fprintf(file, "Scheduling Algorithm: ");
    switch(scheduler->algorithm) {
        case FCFS: fprintf(file, "First Come First Serve\n"); break;
        case PRIORITY_SCHED: fprintf(file, "Priority Scheduling\n"); break;
        case SJF: fprintf(file, "Shortest Job First\n"); break;
        case ROUND_ROBIN: fprintf(file, "Round Robin\n"); break;
        default: fprintf(file, "Unknown\n"); break;
    }
    
    fprintf(file, "\n--- STATISTICS ---\n");
    fprintf(file, "Total Flights Processed: %d\n", scheduler->totalFlightsProcessed);
    
    if (scheduler->totalFlightsProcessed > 0) {
        float avgWaitTime = (float)scheduler->totalWaitingTime / scheduler->totalFlightsProcessed;
        fprintf(file, "Average Waiting Time: %.2f minutes\n", avgWaitTime);
    }
    
    fprintf(file, "\n--- RUNWAY UTILIZATION ---\n");
    for (int i = 0; i < 2; i++) {
        fprintf(file, "%s: %d flights handled\n", 
               scheduler->runways[i].name, 
               scheduler->runways[i].totalFlightsHandled);
    }
    
    fprintf(file, "\n--- COMPLETED FLIGHTS ---\n");
    if (scheduler->completedFlights == NULL) {
        fprintf(file, "No completed flights.\n");
    } else {
        Flight* temp = scheduler->completedFlights;
        int count = 1;
        while (temp != NULL) {
            fprintf(file, "%d. Flight ID: %s | Airline: %s | %s | Priority: %s\n", 
                   count++, temp->flightID, temp->airline,
                   operationToString(temp->operation),
                   priorityToString(temp->priority));
            temp = temp->next;
        }
    }
    
    fprintf(file, "\n=======================================================\n");
    fprintf(file, "                    END OF REPORT\n");
    fprintf(file, "=======================================================\n");
    
    fclose(file);
    printf("\n✅ Log saved successfully to %s\n", filename);
}

// Free scheduler
void freeScheduler(Scheduler* scheduler) {
    if (scheduler == NULL) return;
    
    freeQueue(scheduler->landingQueue);
    freeQueue(scheduler->takeoffQueue);
    freePriorityQueue(scheduler->priorityLandingQueue);
    freePriorityQueue(scheduler->priorityTakeoffQueue);
    freeFlightList(&scheduler->completedFlights);
    free(scheduler);
}
