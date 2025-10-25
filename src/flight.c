#include "flight.h"

// Create a new flight
Flight* createFlight(const char* id, const char* airline, const char* src, 
                     const char* dest, int time, Priority pri, Operation op, int procTime) {
    Flight* newFlight = (Flight*)malloc(sizeof(Flight));
    if (!newFlight) {
        printf("❌ Memory allocation failed!\n");
        return NULL;
    }
    
    // Copy strings safely
    strncpy(newFlight->flightID, id, 49);
    newFlight->flightID[49] = '\0';
    
    strncpy(newFlight->airline, airline, 49);
    newFlight->airline[49] = '\0';
    
    strncpy(newFlight->source, src, 49);
    newFlight->source[49] = '\0';
    
    strncpy(newFlight->destination, dest, 49);
    newFlight->destination[49] = '\0';
    
    newFlight->scheduledTime = time;
    newFlight->priority = pri;
    newFlight->status = WAITING;
    newFlight->operation = op;
    newFlight->processingTime = procTime;
    newFlight->emergencyType = NO_EMERGENCY;
    strcpy(newFlight->emergencyDetails, "None");
    newFlight->next = NULL;
    
    return newFlight;
}

// Add flight to linked list
void addFlight(Flight** head, Flight* newFlight) {
    if (newFlight == NULL) {
        return;
    }
    
    if (*head == NULL) {
        *head = newFlight;
        return;
    }
    
    Flight* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newFlight;
    newFlight->next = NULL;
}

// Display single flight details
void displayFlight(Flight* flight) {
    if (!flight) return;
    
    char timeStr[10];
    timeToString(flight->scheduledTime, timeStr);
    
    printf("┌─────────────────────────────────────────────────────────────┐\n");
    printf("│ Flight ID    : %-44s │\n", flight->flightID);
    printf("│ Airline      : %-44s │\n", flight->airline);
    printf("│ Route        : %s -> %-33s │\n", flight->source, flight->destination);
    printf("│ Time         : %-44s │\n", timeStr);
    printf("│ Operation    : %-44s │\n", operationToString(flight->operation));
    printf("│ Priority     : %-44s │\n", priorityToString(flight->priority));
    printf("│ Status       : %-44s │\n", statusToString(flight->status));
    printf("│ Process Time : %d minutes%-34s │\n", flight->processingTime, "");
    printf("└─────────────────────────────────────────────────────────────┘\n");
}

// Display all flights in linked list
void displayAllFlights(Flight* head) {
    if (head == NULL) {
        printf("\n📭 No flights in the system.\n");
        return;
    }
    
    printf("\n╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║                    ALL FLIGHTS IN SYSTEM                      ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
    
    Flight* temp = head;
    int count = 1;
    while (temp != NULL) {
        printf("\nFlight #%d:\n", count++);
        displayFlight(temp);
        temp = temp->next;
    }
}

// Find flight by ID
Flight* findFlight(Flight* head, const char* id) {
    Flight* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->flightID, id) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Delete flight from linked list
void deleteFlight(Flight** head, const char* id) {
    if (*head == NULL) {
        printf("❌ Flight list is empty!\n");
        return;
    }
    
    Flight* temp = *head;
    Flight* prev = NULL;
    
    // If head node is to be deleted
    if (strcmp(temp->flightID, id) == 0) {
        *head = temp->next;
        free(temp);
        printf("✅ Flight %s deleted successfully!\n", id);
        return;
    }
    
    // Search for the flight
    while (temp != NULL && strcmp(temp->flightID, id) != 0) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("❌ Flight %s not found!\n", id);
        return;
    }
    
    prev->next = temp->next;
    free(temp);
    printf("✅ Flight %s deleted successfully!\n", id);
}

// Free entire flight list
void freeFlightList(Flight** head) {
    Flight* current = *head;
    Flight* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

// Count flights in list
int countFlights(Flight* head) {
    int count = 0;
    Flight* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Convert priority to string
const char* priorityToString(Priority p) {
    switch(p) {
        case SCHEDULED: return "Scheduled";
        case VIP: return "VIP";
        case EMERGENCY: return "Emergency";
        default: return "Unknown";
    }
}

// Convert status to string
const char* statusToString(Status s) {
    switch(s) {
        case WAITING: return "Waiting";
        case IN_PROGRESS: return "In Progress";
        case COMPLETED: return "Completed";
        default: return "Unknown";
    }
}

// Convert operation to string
const char* operationToString(Operation o) {
    switch(o) {
        case LANDING: return "Landing";
        case TAKEOFF: return "Takeoff";
        default: return "Unknown";
    }
}

// Convert emergency type to string
const char* emergencyTypeToString(EmergencyType et) {
    switch(et) {
        case NO_EMERGENCY: return "None";
        case AIRPORT_DELAY: return "Airport Delay";
        case PILOT_UNAVAILABLE: return "Pilot Unavailable";
        case AIRPLANE_DEFECT: return "Airplane Defect";
        case INFLIGHT_EMERGENCY: return "In-Flight Emergency";
        default: return "Unknown";
    }
}

// Convert minutes to HH:MM format
void timeToString(int minutes, char* buffer) {
    if (minutes < 0 || minutes >= 1440) {
        sprintf(buffer, "Invalid");
        return;
    }
    int hours = minutes / 60;
    int mins = minutes % 60;
    sprintf(buffer, "%02d:%02d", hours, mins);
}
