#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
    #include <windows.h>
    #define sleep(x) Sleep((x) * 1000)
#else
    #include <unistd.h>
#endif

#include "flight.h"
#include "queue.h"
#include "scheduler.h"
#include "api_bridge.h"

void displayMenu() {
    printf("\n");
    printf(" ================================================================\n");
    printf("        AIRPORT RUNWAY SCHEDULING & MANAGEMENT SYSTEM            \n");
    printf("               (Integrated with Web Dashboard)                   \n");
    printf(" ================================================================\n");
    printf("\n");
    printf("1.Add New Flight\n");
    printf("2.View All Flights\n");
    printf("3.Delete Flight\n");
    printf("4.Search Flight\n");
    printf("5.View Dashboard\n");
    printf("6.Start Simulation\n");
    printf("7.Add Emergency Flight\n");
    printf("8.Generate Statistics\n");
    printf("9.Save Log to File\n");
    printf("10.Change Scheduling Algorithm\n");
    printf("11.Web Dashboard Mode (Auto-Sync)\n");
    printf("12.Exit\n");
    printf("\n");
    printf("Enter your choice: ");
}

void displayAlgorithmMenu() {
    printf("\n=================================================================\n");
    printf("               SELECT SCHEDULING ALGORITHM                       \n");
    printf("===================================================================\n");
    printf("1. FCFS (First Come First Serve)\n");
    printf("2. Priority Scheduling\n");
    printf("3. SJF (Shortest Job First)\n");
    printf("4. Round Robin\n");
    printf("\nEnter choice (1-4): ");
}

void addSampleFlights(Flight** allFlights, Scheduler* scheduler) {
    printf("\n Adding sample flights for demonstration...\n\n");
    
    Flight* f1 = createFlight("AI101", "AirIndia", "Delhi", "Mumbai", 600, SCHEDULED, LANDING, 8);
    Flight* f2 = createFlight("6E202", "IndiGo", "Bangalore", "Delhi", 605, VIP, LANDING, 7);
    Flight* f3 = createFlight("SG303", "SpiceJet", "Mumbai", "Kolkata", 610, SCHEDULED, TAKEOFF, 6);
    Flight* f4 = createFlight("UK404", "Vistara", "Hyderabad", "Chennai", 615, SCHEDULED, TAKEOFF, 5);
    Flight* f5 = createFlight("G8505", "GoAir", "Pune", "Goa", 620, EMERGENCY, LANDING, 9);
    
    if (f1 == NULL || f2 == NULL || f3 == NULL || f4 == NULL || f5 == NULL) {
        printf(" Error creating sample flights!\n");
        return;
    }
    
    addFlight(allFlights, f1);
    addFlight(allFlights, f2);
    addFlight(allFlights, f3);
    addFlight(allFlights, f4);
    addFlight(allFlights, f5);
    
    addFlightToScheduler(scheduler, f1);
    addFlightToScheduler(scheduler, f2);
    addFlightToScheduler(scheduler, f3);
    addFlightToScheduler(scheduler, f4);
    addFlightToScheduler(scheduler, f5);
    
    printf("\n✅ 5 sample flights added successfully!\n");
    
    // Export to JSON for web dashboard
    exportAllDataJSON(scheduler, *allFlights);
    printf("📤 Data exported to web dashboard\n");
    
    sleep(2);
}

void webDashboardMode(Scheduler* scheduler, Flight** allFlights) {
    printf("\n");
    printf("=================================================================\n");
    printf("                   WEB DASHBOARD MODE ACTIVE                     \n");
    printf("=================================================================\n");
    printf("\n");
    printf(" Backend is now syncing with web dashboard!\n");
    printf("\n");
    printf(" INSTRUCTIONS:\n");
    printf("1. Open 'airport_integrated.html' in your web browser\n");
    printf("2. Click 'Start Auto-Refresh' button in the browser\n");
    printf("3. Watch the dashboard update automatically!\n");
    printf("\n");
    printf("  Options:\n");
    printf("  's' - Start/Continue simulation\n");
    printf("  'p' - Pause simulation\n");
    printf("  'a' - Add sample flights\n");
    printf("  'e' - Add emergency flight\n");
    printf("  'q' - Exit web mode\n");
    printf("\n");
    
    // Initial export
    exportAllDataJSON(scheduler, *allFlights);
    printf(" Initial data exported\n");
    
    int running = 1;
    int simulating = 0;
    
    while (running) {
        printf("\nWeb Mode> ");
        char cmd;
        scanf(" %c", &cmd);
        while(getchar() != '\n'); // Clear buffer
        
        switch(cmd) {
            case 's':
            case 'S':
                if (!simulating) {
                    printf("  Starting simulation...\n");
                    simulating = 1;
                    
                    // Run simulation for 30 minutes
                    for (int i = 0; i < 30 && simulating; i++) {
                        processScheduling(scheduler);
                        scheduler->currentTime++;
                        
                        // Export data every minute
                        exportAllDataJSON(scheduler, *allFlights);
                        
                        printf(".");
                        fflush(stdout);
                        
                        #ifdef _WIN32
                            Sleep(500);
                        #else
                            usleep(500000);
                        #endif
                    }
                    printf("\n✅ Simulation segment completed\n");
                    exportAllDataJSON(scheduler, *allFlights);
                }
                break;
                
            case 'p':
            case 'P':
                simulating = 0;
                printf("  Simulation paused\n");
                break;
                
            case 'a':
            case 'A':
                addSampleFlights(allFlights, scheduler);
                break;
                
            case 'e':
            case 'E':
                handleEmergency(scheduler);
                exportAllDataJSON(scheduler, *allFlights);
                printf("📤 Emergency flight data exported\n");
                break;
                
            case 'q':
            case 'Q':
                running = 0;
                printf(" Exiting web dashboard mode...\n");
                break;
                
            default:
                printf(" Invalid command\n");
        }
    }
}

int main() {
    Flight* allFlights = NULL;
    Scheduler* scheduler = NULL;
    int choice, algo;
    
    printf("\n");
    printf("=================================================================\n");
    printf("                       WELCOME TO                                \n");
    printf("        AIRPORT RUNWAY SCHEDULING & MANAGEMENT SYSTEM            \n");
    printf("               ✨ With Web Dashboard Integration ✨             \n");
    printf("=================================================================\n");
    printf("\n");
    
    // Create data directory
    #ifdef _WIN32
        system("if not exist data mkdir data");
    #else
        system("mkdir -p data");
    #endif
    printf(" Data directory ready for web integration\n\n");
    
    displayAlgorithmMenu();
    if (scanf("%d", &algo) != 1) {
        printf(" Invalid input! Defaulting to FCFS.\n");
        algo = 1;
    }
    while(getchar() != '\n');
    
    if (algo < 1 || algo > 4) {
        printf(" Invalid choice! Defaulting to FCFS.\n");
        algo = 1;
    }
    
    scheduler = createScheduler((SchedulingAlgorithm)algo);
    if (scheduler == NULL) {
        printf(" Failed to create scheduler!\n");
        return 1;
    }
    
    printf("\n Scheduler initialized with ");
    switch(scheduler->algorithm) {
        case FCFS: printf("FCFS algorithm.\n"); break;
        case PRIORITY_SCHED: printf("Priority Scheduling algorithm.\n"); break;
        case SJF: printf("SJF algorithm.\n"); break;
        case ROUND_ROBIN: printf("Round Robin algorithm.\n"); break;
        default: printf("Unknown algorithm.\n"); break;
    }
    
    printf("\nWould you like to add sample flights for testing? (y/n): ");
    char sampleChoice;
    if (scanf(" %c", &sampleChoice) != 1) {
        sampleChoice = 'n';
    }
    while(getchar() != '\n');
    
    if (sampleChoice == 'y' || sampleChoice == 'Y') {
        addSampleFlights(&allFlights, scheduler);
    }
    
    // Main menu loop
    while (1) {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf(" Invalid input! Please enter a number.\n");
            while(getchar() != '\n');
            printf("Press Enter to continue...");
            getchar();
            continue;
        }
        while(getchar() != '\n');
        
        switch(choice) {
            case 1: { // Add new flight
                char id[50], airline[50], src[50], dest[50];
                int time, pri, op, procTime;
                
                printf("\n ADD NEW FLIGHT\n");
                printf("─────────────────────────────────────────────────────\n");
                
                printf("Flight ID: ");
                if (scanf("%49s", id) != 1) {
                    printf(" Invalid input!\n");
                    while(getchar() != '\n');
                    break;
                }
                
                printf("Airline: ");
                if (scanf("%49s", airline) != 1) {
                    printf(" Invalid input!\n");
                    while(getchar() != '\n');
                    break;
                }
                
                printf("Source: ");
                if (scanf("%49s", src) != 1) {
                    printf(" Invalid input!\n");
                    while(getchar() != '\n');
                    break;
                }
                
                printf("Destination: ");
                if (scanf("%49s", dest) != 1) {
                    printf(" Invalid input!\n");
                    while(getchar() != '\n');
                    break;
                }
                
                printf("Scheduled Time (minutes, e.g., 600 for 10:00): ");
                if (scanf("%d", &time) != 1 || time < 0 || time >= 1440) {
                    printf(" Invalid time!\n");
                    while(getchar() != '\n');
                    break;
                }
                
                printf("Priority (1=Scheduled, 2=VIP, 3=Emergency): ");
                if (scanf("%d", &pri) != 1 || pri < 1 || pri > 3) {
                    pri = 1;
                    while(getchar() != '\n');
                }
                
                printf("Operation (0=Landing, 1=Takeoff): ");
                if (scanf("%d", &op) != 1 || (op != 0 && op != 1)) {
                    op = 0;
                    while(getchar() != '\n');
                }
                
                printf("Processing Time (minutes): ");
                if (scanf("%d", &procTime) != 1 || procTime < 1) {
                    procTime = 5;
                    while(getchar() != '\n');
                }
                while(getchar() != '\n');
                
                Flight* newFlight = createFlight(id, airline, src, dest, time, 
                                                (Priority)pri, (Operation)op, procTime);
                if (newFlight != NULL) {
                    addFlight(&allFlights, newFlight);
                    addFlightToScheduler(scheduler, newFlight);
                    printf("\n✅ Flight %s added successfully!\n", id);
                    exportAllDataJSON(scheduler, allFlights);
                    printf("📤 Data exported to web dashboard\n");
                } else {
                    printf("\n Failed to create flight!\n");
                }
                printf("Press Enter to continue...");
                getchar();
                break;
            }
            
            case 2: {
                displayAllFlights(allFlights);
                printf("\nPress Enter to continue...");
                getchar();
                break;
            }
            
            case 3: {
                char id[50];
                printf("\n🗑️  DELETE FLIGHT\n");
                printf("Enter Flight ID to delete: ");
                if (scanf("%49s", id) != 1) {
                    printf(" Invalid input!\n");
                    while(getchar() != '\n');
                    break;
                }
                while(getchar() != '\n');
                
                deleteFlight(&allFlights, id);
                exportAllDataJSON(scheduler, allFlights);
                printf("Press Enter to continue...");
                getchar();
                break;
            }
            
            case 4: {
                char id[50];
                printf("\n🔍 SEARCH FLIGHT\n");
                printf("Enter Flight ID: ");
                if (scanf("%49s", id) != 1) {
                    printf(" Invalid input!\n");
                    while(getchar() != '\n');
                    break;
                }
                while(getchar() != '\n');
                
                Flight* found = findFlight(allFlights, id);
                if (found != NULL) {
                    printf("\n Flight found!\n");
                    displayFlight(found);
                } else {
                    printf("\n Flight not found!\n");
                }
                printf("\nPress Enter to continue...");
                getchar();
                break;
            }
            
            case 5: {
                displayDashboard(scheduler);
                printf("\nPress Enter to continue...");
                getchar();
                break;
            }
            
            case 6: {
                int duration;
                printf("\n  START SIMULATION\n");
                printf("Enter simulation duration (minutes): ");
                if (scanf("%d", &duration) != 1 || duration < 1) {
                    duration = 20;
                    while(getchar() != '\n');
                } else {
                    while(getchar() != '\n');
                }
                
                printf("\n Starting simulation...\n");
                printf("Tip: Open web dashboard to see live updates!\n\n");
                
                int endTime = scheduler->currentTime + duration;
                while (scheduler->currentTime < endTime) {
                    processScheduling(scheduler);
                    scheduler->currentTime++;
                    
                    // Export every 5 minutes
                    if (scheduler->currentTime % 5 == 0) {
                        exportAllDataJSON(scheduler, allFlights);
                    }
                    
                    #ifdef _WIN32
                        Sleep(100);
                    #else
                        usleep(100000);
                    #endif
                }
                
                exportAllDataJSON(scheduler, allFlights);
                printf("\n Simulation completed!\n");
                printf(" Final data exported to web dashboard\n");
                printf("\nPress Enter to continue...");
                getchar();
                break;
            }
            
            case 7: {
                handleEmergency(scheduler);
                exportAllDataJSON(scheduler, allFlights);
                printf("📤 Emergency data exported\n");
                printf("\nPress Enter to continue...");
                getchar();
                break;
            }
            
            case 8: {
                generateStatistics(scheduler);
                printf("\nPress Enter to continue...");
                getchar();
                break;
            }
            
            case 9: {
                char filename[256];
                printf("\n SAVE LOG TO FILE\n");
                printf("Enter filename (press Enter for default): ");
                
                if (fgets(filename, sizeof(filename), stdin) == NULL) {
                    strcpy(filename, "scheduling_log.txt");
                } else {
                    filename[strcspn(filename, "\n")] = '\0';
                }
                
                if (strlen(filename) == 0) {
                    strcpy(filename, "scheduling_log.txt");
                }
                
                saveLogToFile(scheduler, filename);
                printf("\nPress Enter to continue...");
                getchar();
                break;
            }
            
            case 10: {
                displayAlgorithmMenu();
                if (scanf("%d", &algo) != 1) {
                    printf(" Invalid input!\n");
                    while(getchar() != '\n');
                    break;
                }
                while(getchar() != '\n');
                
                if (algo >= 1 && algo <= 4) {
                    scheduler->algorithm = (SchedulingAlgorithm)algo;
                    printf("\n Algorithm changed successfully!\n");
                    exportAllDataJSON(scheduler, allFlights);
                } else {
                    printf("\n Invalid choice!\n");
                }
                printf("Press Enter to continue...");
                getchar();
                break;
            }
            
            case 11: {
                webDashboardMode(scheduler, &allFlights);
                break;
            }
            
            case 12: {
                printf("\n Thank you for using Airport Runway Scheduling System!\n");
                printf("Cleaning up resources...\n");
                
                freeFlightList(&allFlights);
                freeScheduler(scheduler);
                
                printf(" Goodbye!\n\n");
                return 0;
            }
            
            default:
                printf("\n Invalid choice! Please enter 1-12.\n");
                printf("Press Enter to continue...");
                getchar();
        }
    }
    
    return 0;
}
