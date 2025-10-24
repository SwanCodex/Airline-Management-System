# ✈️ Airport Runway Scheduling and Management System

A comprehensive C-based system that efficiently manages takeoffs, landings, and scheduling of multiple flights at an airport using optimized data structures and scheduling algorithms.

## 🎯 Project Overview

This system simulates real-time scheduling of aircraft operations using advanced data structures including:
- **Linked Lists** - Dynamic flight data management
- **Queues** - Landing and takeoff queues
- **Priority Queues (Min-Heap)** - Priority-based scheduling
- **Scheduling Algorithms** - FCFS, Priority, SJF, Round Robin

## 🌟 Key Features

### 1. **Flight Management**
- Add, view, search, and delete flight details
- Flight attributes: ID, Airline, Source, Destination, Time, Priority, Status
- Dynamic storage using linked lists

### 2. **Runway Scheduling**
- Two runway simulation (Runway A and Runway B)
- Multiple scheduling algorithms:
  - **FCFS** (First Come First Serve)
  - **Priority Scheduling** (Emergency > VIP > Scheduled)
  - **SJF** (Shortest Job First)
  - **Round Robin**

### 3. **Queue Management**
- Separate landing and takeoff queues
- Priority queue implementation using min-heap
- Emergency flight handling with dynamic reordering

### 4. **Real-Time Simulation**
- Time-based progression system
- Live runway status updates
- Visual dashboard with queue visualization

### 5. **Emergency Handling**
- Mid-simulation emergency flight insertion
- Automatic priority reordering
- Immediate runway assignment attempt

### 6. **Statistics & Logging**
- Average waiting time calculation
- Runway utilization metrics
- Completed flights tracking
- Export logs to file

## 📁 Project Structure

```
airport-runway-system/
│
├── flight.h            # Flight structure and function declarations
├── flight.c            # Flight management implementation
├── queue.h             # Queue and Priority Queue declarations
├── queue.c             # Queue operations implementation
├── scheduler.h         # Scheduler and runway declarations
├── scheduler.c         # Scheduling algorithms implementation
├── main.c              # Main program with menu interface
├── Makefile            # Compilation script
└── README.md           # Project documentation
```


## 📖 Usage Guide

### Main Menu Options

1. **Add New Flight** - Enter flight details manually
2. **View All Flights** - Display all registered flights
3. **Delete Flight** - Remove a flight by ID
4. **Search Flight** - Find specific flight information
5. **View Dashboard** - See real-time system status
6. **Start Simulation** - Run time-based scheduling simulation
7. **Add Emergency Flight** - Insert urgent flight during operation
8. **Generate Statistics** - View system performance metrics
9. **Save Log to File** - Export operation logs
10. **Change Scheduling Algorithm** - Switch between algorithms
11. **Exit** - Terminate program safely

### Sample Flight Input

When adding a flight, you'll need:
- **Flight ID**: e.g., AI101
- **Airline**: e.g., Air India
- **Source**: e.g., Delhi
- **Destination**: e.g., Mumbai
- **Scheduled Time**: Minutes from midnight (e.g., 600 = 10:00 AM)
- **Priority**: 1=Scheduled, 2=VIP, 3=Emergency
- **Operation**: 0=Landing, 1=Takeoff
- **Processing Time**: Duration in minutes (typically 5-10 min)

### Sample Run

The program includes a feature to add 5 sample flights automatically for testing:
- AI101 (Air India) - Landing, Scheduled
- 6E202 (IndiGo) - Landing, VIP
- SG303 (SpiceJet) - Takeoff, Scheduled
- UK404 (Vistara) - Takeoff, Scheduled
- G8505 (GoAir) - Landing, Emergency

## 🧠 Data Structures Used

| Feature | Data Structure | Purpose |
|---------|---------------|---------|
| Flight Storage | Linked List | Dynamic flight data management |
| Landing/Takeoff Queues | Queue | FIFO operation management |
| Priority Management | Min-Heap (Priority Queue) | Urgent flight scheduling |
| Runway Management | Array of Structures | Runway status tracking |
| Completed Flights | Linked List | Historical records |

## 🎓 Scheduling Algorithms

### 1. FCFS (First Come First Serve)
- Processes flights in arrival order
- Fair but doesn't consider urgency
- Simple implementation

### 2. Priority Scheduling
- Processes based on priority level
- Emergency > VIP > Scheduled
- Uses min-heap for efficiency

### 3. SJF (Shortest Job First)
- Processes flights with shortest duration first
- Minimizes average waiting time
- Optimal for throughput

### 4. Round Robin
- Alternates between landing and takeoff
- Ensures fairness between operations
- Prevents starvation

## 📊 Sample Output

```
╔═══════════════════════════════════════════════════════════════╗
║          AIRPORT RUNWAY SCHEDULING SYSTEM DASHBOARD           ║
╚═══════════════════════════════════════════════════════════════╝
Current Time: 10:05 | Algorithm: Priority Scheduling

Runway A:
  🛫 OCCUPIED - Flight AI101 (Air India)
  Available at: 10:13
  Total flights handled: 3

Runway B:
  ✅ AVAILABLE
  Total flights handled: 2

📊 Total Flights Completed: 5
```

## 🔧 Advanced Features

### Log File Format
Logs are saved with:
- Timestamp
- System configuration
- Statistics (wait times, flights processed)
- Runway utilization
- Complete flight history

### Emergency Handling Flow
1. User triggers emergency during simulation
2. System accepts emergency flight details
3. Flight assigned EMERGENCY priority
4. Priority queue automatically reorders
5. System attempts immediate runway assignment
6. Dashboard updates in real-time

## 💡 Key Implementation Highlights

### Min-Heap Priority Queue
```c
// Comparison logic for priority queue
int compareFlight(Flight* f1, Flight* f2) {
    // Higher priority number = more urgent
    if (f1->priority != f2->priority) {
        return f2->priority - f1->priority;
    }
    // Same priority: earlier time first
    return f1->scheduledTime - f2->scheduledTime;
}
```

### Time Simulation
- Time represented in minutes from midnight
- 600 = 10:00 AM, 1440 = 24:00 (midnight)
- Runway availability tracked per minute
- Processing time varies by operation

## 📈 Performance Metrics

The system tracks:
- **Average Waiting Time**: Time between scheduled and actual operation
- **Runway Utilization**: Flights handled per runway
- **Throughput**: Total flights processed
- **Queue Lengths**: Real-time monitoring

## 🎨 User Interface Features

- **Box-drawing Characters**: Clean ASCII art borders
- **Emoji Indicators**: Visual status representation
- **Color-coded Messages**: (if terminal supports)
- **Structured Layout**: Easy-to-read information hierarchy
- **Real-time Updates**: Dynamic dashboard refresh

## 🔍 Testing Recommendations

### Test Case 1: Basic Operations
1. Add 3-4 flights with different priorities
2. Run 30-minute simulation
3. Observe runway assignments
4. Check statistics

### Test Case 2: Emergency Handling
1. Start simulation with scheduled flights
2. Add emergency mid-simulation
3. Verify priority override
4. Check queue reordering

### Test Case 3: Algorithm Comparison
1. Add same set of flights
2. Test with FCFS algorithm
3. Reset and test with Priority
4. Compare average wait times

### Test Case 4: Heavy Load
1. Add 10+ flights in short time window
2. Observe queue management
3. Check runway utilization
4. Verify no crashes

## 🐛 Error Handling

The system includes:
- Memory allocation failure checks
- Null pointer validation
- Queue overflow protection
- Invalid input handling
- File I/O error management

## 📝 Code Quality Features

- **Modular Design**: Separated by functionality
- **Clear Comments**: Explains complex logic
- **Consistent Naming**: camelCase for variables, PascalCase for types
- **Memory Management**: All allocated memory properly freed
- **Type Safety**: Strong typing with enums

## 🚀 Future Enhancements (Optional)

1. **Graph-based Terminal Navigation**
   - Adjacency matrix for terminal connections
   - Shortest path for taxiing

2. **Weather Conditions**
   - Dynamic priority adjustment
   - Runway availability based on weather

3. **Multiple Airport Support**
   - Inter-airport flight coordination
   - Transfer management

4. **GUI Interface**
   - GTK+ or SDL integration
   - Visual runway representation

5. **Network Simulation**
   - Multi-client support
   - Distributed scheduling

## 📚 Learning Outcomes

This project demonstrates:
✅ **Data Structures**: Linked Lists, Queues, Heaps, Arrays  
✅ **Algorithms**: Scheduling algorithms, Heap operations  
✅ **Memory Management**: Dynamic allocation, deallocation  
✅ **File I/O**: Reading/writing logs  
✅ **Modular Programming**: Header files, separate compilation  
✅ **Real-world Application**: Airport operations simulation  
✅ **Algorithm Comparison**: Performance analysis  



## 📊 Example Session

```
Welcome to Airport Runway Scheduling & Management System

Select Scheduling Algorithm:
1. FCFS
2. Priority Scheduling
3. SJF
4. Round Robin

Choice: 2

✅ Scheduler initialized with Priority Scheduling algorithm.

Would you like to add sample flights? (y/n): y

🎲 Adding sample flights...
✈️  Flight AI101 added to Landing queue
✈️  Flight 6E202 added to Landing queue
✈️  Flight SG303 added to Takeoff queue
✈️  Flight UK404 added to Takeoff queue
✈️  Flight G8505 added to Landing queue

✅ 5 sample flights added successfully!

Main Menu:
1. Add New Flight
2. View All Flights
...

Choice: 6 (Start Simulation)

Enter simulation duration: 30

[Time 10:00] ✈️  Flight G8505 (GoAir) landing on Runway A... (Duration: 9 min)
[Time 10:00] ✈️  Flight 6E202 (IndiGo) landing on Runway B... (Duration: 7 min)
[Time 10:07] ✅ Flight 6E202 completed Landing on Runway B
[Time 10:07] ✈️  Flight AI101 (Air India) landing on Runway B... (Duration: 8 min)
...

✅ Simulation completed!
```

---

