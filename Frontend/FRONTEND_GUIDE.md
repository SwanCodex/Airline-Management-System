# 🌐 Web Dashboard Quick Start Guide

## 📋 Prerequisites

✅ GCC Compiler installed (for building C program)  
✅ Web browser (Chrome, Firefox, Edge, etc.)  
✅ Both files in the same project structure

---

## 🚀 Step-by-Step Setup

### **Step 1: Build the C Backend**

Open terminal in VS Code and navigate to the `src` folder:

```bash
cd AIRPORT-RUNWAY_SYSTEM\src
```

Build the project:

```bash
.\build.bat
```

You should see:
```
Building Airport Runway System...
Compiling flight.c...
Compiling queue.c...
...
Build successful!
```

---

### **Step 2: Start the C Backend**

Run the compiled program:

```bash
.\airport_system.exe
```

**Interactive Setup:**

1. **Select Algorithm** (Recommended: `2` for Priority Scheduling)
   ```
   Select Scheduling Algorithm:
   1. FCFS
   2. Priority Scheduling (Recommended)
   3. SJF
   4. Round Robin
   
   Enter choice (1-4): 2
   ```

2. **Add Sample Flights** (Type `y`)
   ```
   Would you like to add sample flights for testing? (y/n): y
   ```

3. **Choose Web Dashboard Mode** (Option `11`)
   ```
   === Main Menu ===
   1. Add New Flight
   ...
   11. Web Dashboard Mode (Auto-Sync)
   12. Exit
   
   Enter your choice: 11
   ```

You should see:
```
=================================================================
                   WEB DASHBOARD MODE ACTIVE                     
=================================================================

 Backend is now syncing with web dashboard!

 INSTRUCTIONS:
1. Open 'airport_integrated.html' in your web browser
2. Click 'Start Auto-Refresh' button in the browser
3. Watch the dashboard update automatically!

  Options:
  's' - Start/Continue simulation
  'p' - Pause simulation
  'a' - Add sample flights
  'e' - Add emergency flight
  'q' - Exit web mode

Web Mode> 
```

**✅ Backend is now ready and waiting!**

---

### **Step 3: Open the Web Dashboard**

**Option A: Using File Explorer**
1. Navigate to: `AIRPORT-RUNWAY_SYSTEM\Frontend\`
2. Double-click `dashboard.html`
3. It will open in your default browser

**Option B: Using VS Code**
1. Right-click on `dashboard.html` in the file explorer
2. Select "Open with Live Server" (if you have the extension)
3. OR select "Reveal in File Explorer" → Double-click the file

---

### **Step 4: Activate Auto-Refresh**

In the web browser:

1. You'll see the dashboard with connection status
2. Click the **"Start Auto-Refresh"** button (green button)
3. You should see:
   - Status changes to "● Connected to C Backend" (green)
   - Data starts populating
   - System log shows "✅ Data refreshed successfully"

---

### **Step 5: Run Simulation**

Back in the terminal (where C program is running):

Type `s` and press Enter:
```
Web Mode> s
```

**What happens:**
- ✅ C backend starts processing flights
- ✅ JSON files are updated every minute
- ✅ Web dashboard auto-refreshes every 2 seconds
- ✅ You see live updates of:
  - Runway status changing
  - Queue counts updating
  - Statistics incrementing
  - Flight movements in real-time

---

## 🎯 Testing Emergency Handling

### Add Emergency Flight via Backend

In the terminal:
```
Web Mode> e
```

Follow prompts:
```
Emergency Types:
1. Airport Delay (Lowest Priority)
2. Pilot Unavailability
3. Airplane Defect
4. In-Flight Emergency (Highest Priority)

Select emergency type (1-4): 4

Enter Flight ID: EM999
Enter Airline: AirIndia
Enter Source: Delhi
Enter Destination: Mumbai
Enter Scheduled Time (minutes): 700
Operation (0=Landing, 1=Takeoff): 0
Processing Time (minutes): 10
Emergency Details: Engine failure - need immediate landing
```

**Watch the Dashboard:**
- 🚨 Emergency flight appears with red badge
- 🔴 Priority indicator shows "EMERGENCY"
- 📊 Flight moves to top of queue
- ✅ Processed immediately by scheduler

---

## 📊 Dashboard Features

### **1. Connection Panel**
- **Green Indicator** = Connected to backend
- **Red Indicator** = Backend not running or data not found
- Shows refresh count and data age

### **2. Control Buttons**
- **🔄 Refresh Now**: Manual data fetch
- **▶️ Start Auto-Refresh**: Enable automatic updates every 2 seconds
- **⏸️ Stop Auto-Refresh**: Disable automatic updates
- **🗑️ Clear Logs**: Clear system log entries
- **🔃 Reset Dashboard**: Reload the page

### **3. Time Display**
- **Current Time**: System time from backend
- **Algorithm**: Active scheduling algorithm
- **Last Update**: When data was last fetched
- **Status**: Active/Offline

### **4. Runway Status**
- **Runway A & B**: Real-time occupancy status
- **Green** = Available
- **Red** = Occupied
- Shows current flight details when occupied
- Total flights handled counter

### **5. Statistics**
- Total flights completed
- Average wait time
- Individual runway counts

### **6. Queue Panels**
- **Landing Queue**: Flights waiting to land
- **Takeoff Queue**: Flights waiting to takeoff
- **Emergency Badge**: Red pulsing indicator
- **VIP Badge**: Orange indicator
- **Scheduled Badge**: Green indicator

### **7. System Log**
- Color-coded messages:
  - 🟢 Green = Success
  - 🔴 Red = Error
  - 🟡 Yellow = Warning
  - 🔵 Blue = Info
- Auto-scrolls to latest entry
- Keeps last 100 entries

---

## 🔧 Troubleshooting

### ❌ "Backend Disconnected" Error

**Cause**: C program not running or not in Web Dashboard Mode

**Solution**:
1. Make sure `airport_system.exe` is running
2. Select option `11` (Web Dashboard Mode)
3. Press `s` to start simulation
4. Click "Refresh Now" in browser

### ❌ "Failed to load JSON files"

**Cause**: Data files not created yet

**Solution**:
1. In C program, add sample flights (option `1` or press `a` in web mode)
2. Run simulation (press `s`)
3. Refresh browser

### ❌ Dashboard shows old data

**Cause**: Auto-refresh is off or simulation paused

**Solution**:
1. Click "Start Auto-Refresh" button
2. In terminal, type `s` to continue simulation
3. Check if C program is still running

### ❌ Browser console errors

**Cause**: Incorrect file paths

**Solution**:
1. Make sure you opened `dashboard.html` directly (not through a web server running on different port)
2. Check that folder structure is intact:
   ```
   AIRPORT-RUNWAY_SYSTEM/
   ├── Frontend/
   │   └── dashboard.html
   └── src/
       └── data/
           ├── stats.json
           ├── queues.json
           ├── runways.json
           └── flights.json
   ```

---

## 💡 Usage Tips

### **Tip 1: Best Algorithm for Emergency Handling**
- Use **Priority Scheduling** (option 2)
- Emergency flights get immediate priority
- VIP flights processed before scheduled

### **Tip 2: Simulate Busy Airport**
- Add multiple sample flights (press `a` multiple times in web mode)
- Run long simulation (press `s` and let it run)
- Watch queue management in action

### **Tip 3: Monitor Specific Events**
- Add emergency flight (press `e`)
- Immediately check web dashboard
- See priority queue reordering

### **Tip 4: Performance Testing**
- Add 10+ sample flights
- Set Priority algorithm
- Run simulation for 60+ minutes
- Check average wait time statistics

---

## 🎨 Visual Indicators

| Indicator | Meaning |
|-----------|---------|
| 🟢 Green Dot | Backend connected |
| 🔴 Red Dot | Backend disconnected |
| 🔴 Red Badge | Emergency priority flight |
| 🟠 Orange Badge | VIP priority flight |
| 🟢 Green Badge | Scheduled flight |
| 🟢 Green Runway | Available |
| 🔴 Red Runway | Occupied |
| ✅ Check Mark | Queue empty (all flights processed) |

---

## 📁 Data Files (Auto-Generated)

Located in `AIRPORT-RUNWAY_SYSTEM/src/data/`:

- **`stats.json`**: System statistics, current time, algorithm
- **`queues.json`**: Landing and takeoff queue contents
- **`runways.json`**: Runway A & B status, current flights
- **`flights.json`**: All flights database (if needed)

**Note**: These files are automatically created and updated by the C backend. Don't edit manually!

---

## 🚦 Workflow Summary

```
┌─────────────────────────────────────────────────────────────┐
│  1. Build C Program (build.bat)                             │
│  2. Run airport_system.exe                                  │
│  3. Choose Priority Scheduling (option 2)                   │
│  4. Add sample flights (y)                                  │
│  5. Enter Web Dashboard Mode (option 11)                    │
│  6. Open dashboard.html in browser                          │
│  7. Click "Start Auto-Refresh" in browser                   │
│  8. Type 's' in terminal to start simulation                │
│  9. Watch live updates! 🎉                                  │
└─────────────────────────────────────────────────────────────┘
```

---

## ✅ Success Checklist

- [ ] C program builds without errors
- [ ] Airport system executable runs
- [ ] Sample flights added successfully
- [ ] Web Dashboard Mode activated
- [ ] Dashboard opens in browser
- [ ] Green "Connected" status visible
- [ ] Auto-refresh enabled (green button turns red)
- [ ] Simulation running (`s` pressed in terminal)
- [ ] Data updates visible every 2 seconds
- [ ] Emergency flights show with red badge
- [ ] Runway status changes dynamically
- [ ] System log shows success messages

---

## 🎉 You're All Set!

Your Airport Runway Management System is now fully operational with live web integration!

**Enjoy watching your flights being managed in real-time!** ✈️🚀

---

*Last Updated: October 24, 2025*
*Version: 2.0 - Enhanced Web Integration*
