#ifndef API_BRIDGE_H
#define API_BRIDGE_H

#include "scheduler.h"

// API Bridge functions for C to Web communication

// Write current system state to JSON
void exportSystemStateJSON(Scheduler* scheduler, const char* filename);

// Write flight data to JSON
void exportFlightsJSON(Flight* flights, const char* filename);

// Write queue data to JSON
void exportQueuesJSON(Scheduler* scheduler, const char* filename);

// Write runway status to JSON
void exportRunwaysJSON(Scheduler* scheduler, const char* filename);

// Write statistics to JSON
void exportStatsJSON(Scheduler* scheduler, const char* filename);

// Write log entries to JSON
void exportLogJSON(Scheduler* scheduler, const char* filename);

// Main function to export all data
void exportAllDataJSON(Scheduler* scheduler, Flight* allFlights);

// Start HTTP server mode
void startServerMode(Scheduler* scheduler, Flight* allFlights, int port);

#endif
