#include "api_bridge.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Helper function to escape JSON strings (not used but good to have)
void escapeJSONString(const char* input, char* output, int maxLen) {
    int j = 0;
    for (int i = 0; input[i] != '\0' && j < maxLen - 1; i++) {
        if (input[i] == '"' || input[i] == '\\') {
            output[j++] = '\\';
        }
        output[j++] = input[i];
    }
    output[j] = '\0';
}

// Export flights to JSON
void exportFlightsJSON(Flight* flights, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Cannot open %s for writing\n", filename);
        return;
    }

    fprintf(file, "{\n");
    fprintf(file, "  \"flights\": [\n");
    
    Flight* temp = flights;
    int first = 1;
    
    while (temp != NULL) {
        if (!first) fprintf(file, ",\n");
        first = 0;
        
        char timeStr[10];
        timeToString(temp->scheduledTime, timeStr);
        
        fprintf(file, "    {\n");
        fprintf(file, "      \"id\": \"%s\",\n", temp->flightID);
        fprintf(file, "      \"airline\": \"%s\",\n", temp->airline);
        fprintf(file, "      \"source\": \"%s\",\n", temp->source);
        fprintf(file, "      \"destination\": \"%s\",\n", temp->destination);
        fprintf(file, "      \"scheduledTime\": %d,\n", temp->scheduledTime);
        fprintf(file, "      \"scheduledTimeStr\": \"%s\",\n", timeStr);
        fprintf(file, "      \"priority\": %d,\n", temp->priority);
        fprintf(file, "      \"priorityStr\": \"%s\",\n", priorityToString(temp->priority));
        fprintf(file, "      \"operation\": %d,\n", temp->operation);
        fprintf(file, "      \"operationStr\": \"%s\",\n", operationToString(temp->operation));
        fprintf(file, "      \"status\": %d,\n", temp->status);
        fprintf(file, "      \"statusStr\": \"%s\",\n", statusToString(temp->status));
        fprintf(file, "      \"processingTime\": %d\n", temp->processingTime);
        fprintf(file, "    }");
        
        temp = temp->next;
    }
    
    fprintf(file, "\n  ],\n");
    fprintf(file, "  \"count\": %d,\n", countFlights(flights));
    fprintf(file, "  \"timestamp\": %ld\n", (long)time(NULL));
    fprintf(file, "}\n");
    
    fclose(file);
}

// Export queues to JSON
void exportQueuesJSON(Scheduler* scheduler, const char* filename) {
    if (!scheduler) return;
    
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Cannot open %s for writing\n", filename);
        return;
    }

    fprintf(file, "{\n");
    
    // Landing Queue
    fprintf(file, "  \"landingQueue\": [\n");
    
    int first = 1;
    if (scheduler->algorithm == PRIORITY_SCHED) {
        // Priority queue
        for (int i = 0; i < scheduler->priorityLandingQueue->size; i++) {
            Flight* f = scheduler->priorityLandingQueue->flights[i];
            if (!first) fprintf(file, ",\n");
            first = 0;
            
            fprintf(file, "    {\n");
            fprintf(file, "      \"id\": \"%s\",\n", f->flightID);
            fprintf(file, "      \"airline\": \"%s\",\n", f->airline);
            fprintf(file, "      \"priority\": %d,\n", f->priority);
            fprintf(file, "      \"priorityStr\": \"%s\",\n", priorityToString(f->priority));
            fprintf(file, "      \"processingTime\": %d\n", f->processingTime);
            fprintf(file, "    }");
        }
    } else {
        // Regular queue
        QueueNode* node = scheduler->landingQueue->front;
        while (node != NULL) {
            if (!first) fprintf(file, ",\n");
            first = 0;
            
            Flight* f = node->flight;
            fprintf(file, "    {\n");
            fprintf(file, "      \"id\": \"%s\",\n", f->flightID);
            fprintf(file, "      \"airline\": \"%s\",\n", f->airline);
            fprintf(file, "      \"priority\": %d,\n", f->priority);
            fprintf(file, "      \"priorityStr\": \"%s\",\n", priorityToString(f->priority));
            fprintf(file, "      \"processingTime\": %d\n", f->processingTime);
            fprintf(file, "    }");
            
            node = node->next;
        }
    }
    fprintf(file, "\n  ],\n");
    
    // Takeoff Queue
    fprintf(file, "  \"takeoffQueue\": [\n");
    
    first = 1;
    if (scheduler->algorithm == PRIORITY_SCHED) {
        // Priority queue
        for (int i = 0; i < scheduler->priorityTakeoffQueue->size; i++) {
            Flight* f = scheduler->priorityTakeoffQueue->flights[i];
            if (!first) fprintf(file, ",\n");
            first = 0;
            
            fprintf(file, "    {\n");
            fprintf(file, "      \"id\": \"%s\",\n", f->flightID);
            fprintf(file, "      \"airline\": \"%s\",\n", f->airline);
            fprintf(file, "      \"priority\": %d,\n", f->priority);
            fprintf(file, "      \"priorityStr\": \"%s\",\n", priorityToString(f->priority));
            fprintf(file, "      \"processingTime\": %d\n", f->processingTime);
            fprintf(file, "    }");
        }
    } else {
        // Regular queue
        QueueNode* node = scheduler->takeoffQueue->front;
        while (node != NULL) {
            if (!first) fprintf(file, ",\n");
            first = 0;
            
            Flight* f = node->flight;
            fprintf(file, "    {\n");
            fprintf(file, "      \"id\": \"%s\",\n", f->flightID);
            fprintf(file, "      \"airline\": \"%s\",\n", f->airline);
            fprintf(file, "      \"priority\": %d,\n", f->priority);
            fprintf(file, "      \"priorityStr\": \"%s\",\n", priorityToString(f->priority));
            fprintf(file, "      \"processingTime\": %d\n", f->processingTime);
            fprintf(file, "    }");
            
            node = node->next;
        }
    }
    fprintf(file, "\n  ],\n");
    
    fprintf(file, "  \"timestamp\": %ld\n", (long)time(NULL));
    fprintf(file, "}\n");
    
    fclose(file);
}

// Export runway status to JSON
void exportRunwaysJSON(Scheduler* scheduler, const char* filename) {
    if (!scheduler) return;
    
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Cannot open %s for writing\n", filename);
        return;
    }

    fprintf(file, "{\n");
    fprintf(file, "  \"runways\": [\n");
    
    for (int i = 0; i < 2; i++) {
        if (i > 0) fprintf(file, ",\n");
        
        fprintf(file, "    {\n");
        fprintf(file, "      \"name\": \"%s\",\n", scheduler->runways[i].name);
        fprintf(file, "      \"occupied\": %s,\n", 
                scheduler->runways[i].currentFlight ? "true" : "false");
        
        if (scheduler->runways[i].currentFlight) {
            Flight* f = scheduler->runways[i].currentFlight;
            fprintf(file, "      \"currentFlight\": {\n");
            fprintf(file, "        \"id\": \"%s\",\n", f->flightID);
            fprintf(file, "        \"airline\": \"%s\",\n", f->airline);
            fprintf(file, "        \"operation\": \"%s\"\n", operationToString(f->operation));
            fprintf(file, "      },\n");
        } else {
            fprintf(file, "      \"currentFlight\": null,\n");
        }
        
        char timeStr[10];
        timeToString(scheduler->runways[i].availableAt, timeStr);
        fprintf(file, "      \"availableAt\": %d,\n", scheduler->runways[i].availableAt);
        fprintf(file, "      \"availableAtStr\": \"%s\",\n", timeStr);
        fprintf(file, "      \"totalFlightsHandled\": %d\n", scheduler->runways[i].totalFlightsHandled);
        fprintf(file, "    }");
    }
    
    fprintf(file, "\n  ],\n");
    fprintf(file, "  \"timestamp\": %ld\n", (long)time(NULL));
    fprintf(file, "}\n");
    
    fclose(file);
}

// Export statistics to JSON
void exportStatsJSON(Scheduler* scheduler, const char* filename) {
    if (!scheduler) return;
    
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Cannot open %s for writing\n", filename);
        return;
    }

    float avgWaitTime = 0;
    if (scheduler->totalFlightsProcessed > 0) {
        avgWaitTime = (float)scheduler->totalWaitingTime / scheduler->totalFlightsProcessed;
    }
    
    char timeStr[10];
    timeToString(scheduler->currentTime, timeStr);
    
    fprintf(file, "{\n");
    fprintf(file, "  \"currentTime\": %d,\n", scheduler->currentTime);
    fprintf(file, "  \"currentTimeStr\": \"%s\",\n", timeStr);
    fprintf(file, "  \"algorithm\": %d,\n", scheduler->algorithm);
    
    const char* algoName = "Unknown";
    switch(scheduler->algorithm) {
        case FCFS: algoName = "FCFS"; break;
        case PRIORITY_SCHED: algoName = "Priority"; break;
        case SJF: algoName = "SJF"; break;
        case ROUND_ROBIN: algoName = "Round Robin"; break;
    }
    fprintf(file, "  \"algorithmStr\": \"%s\",\n", algoName);
    
    fprintf(file, "  \"totalFlightsProcessed\": %d,\n", scheduler->totalFlightsProcessed);
    fprintf(file, "  \"totalWaitingTime\": %d,\n", scheduler->totalWaitingTime);
    fprintf(file, "  \"averageWaitTime\": %.2f,\n", avgWaitTime);
    fprintf(file, "  \"runwayAHandled\": %d,\n", scheduler->runways[0].totalFlightsHandled);
    fprintf(file, "  \"runwayBHandled\": %d,\n", scheduler->runways[1].totalFlightsHandled);
    fprintf(file, "  \"timestamp\": %ld\n", (long)time(NULL));
    fprintf(file, "}\n");
    
    fclose(file);
}

// Export all data in one call - THIS IS THE MAIN FUNCTION YOU'LL USE!
void exportAllDataJSON(Scheduler* scheduler, Flight* allFlights) {
    if (!scheduler) {
        printf("Warning: Scheduler is NULL, cannot export data\n");
        return;
    }
    
    // Create data directory if it doesn't exist
    #ifdef _WIN32
        system("if not exist data mkdir data");
    #else
        system("mkdir -p data");
    #endif
    
    // Export all data files
    exportFlightsJSON(allFlights, "data/flights.json");
    exportQueuesJSON(scheduler, "data/queues.json");
    exportRunwaysJSON(scheduler, "data/runways.json");
    exportStatsJSON(scheduler, "data/stats.json");
    
    // Optional: Print confirmation (comment out if too verbose)
    // printf("📤 Data exported to JSON files\n");
}
