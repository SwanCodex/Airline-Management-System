# ✅ SOLUTION: Airport Runway System - Ready to Run!

## 🎉 GOOD NEWS - No GCC Installation Required!

Your system **already has a compiled executable** (`airport_system.exe`) that's ready to use!

---

## 🚀 How to Run RIGHT NOW (3 Steps)

### **Step 1: Open Terminal in VS Code**

Press **Ctrl + `** (backtick key, left of number 1)

### **Step 2: Navigate to src folder**

Copy and paste this command:

```cmd
cd "c:\Users\Swanandi\OneDrive\Desktop\Sem 3 All Files\FODS\FODScp New\AIRPORT-RUNWAY_SYSTEM\src"
```

### **Step 3: Run the program**

```cmd
airport_system.exe
```

**✅ The program will start immediately!**

---

## 📖 Complete Step-by-Step Tutorial

### **Interactive Setup (Follow the prompts):**

#### **1. Select Scheduling Algorithm**

```
Select Scheduling Algorithm:
1. FCFS (First Come First Serve)
2. Priority Scheduling (Recommended)  ← Type 2 and press Enter
3. SJF (Shortest Job First)
4. Round Robin
5. Exit

Enter choice (1-4): 2
```

#### **2. Add Sample Flights**

```
Would you like to add sample flights for testing? (y/n): y
```

Type `y` and press Enter. The system will add 5 test flights.

#### **3. Main Menu - Choose Web Dashboard Mode**

```
=== Main Menu ===
1. Add New Flight
2. View All Flights
3. Delete Flight
4. Search Flight
5. View Dashboard
6. Start Simulation
7. Add Emergency Flight
8. Generate Statistics
9. Save Log to File
10. Change Scheduling Algorithm
11. Web Dashboard Mode (Auto-Sync)  ← Type 11 and press Enter
12. Exit

Enter your choice: 11
```

#### **4. Start the Simulation**

```
Web Mode> s
```

Type `s` and press Enter to start the simulation!

You'll see:
```
✅ Starting simulation...
....................  (dots showing progress)
✅ Simulation segment completed
📤 Data exported to web dashboard
```

---

## 🌐 Open the Web Dashboard

### **While the C program is still running:**

#### **Method 1: Using File Explorer**

1. Press `Win + E` to open File Explorer
2. Navigate to:
   ```
   C:\Users\Swanandi\OneDrive\Desktop\Sem 3 All Files\FODS\FODScp New\AIRPORT-RUNWAY_SYSTEM\Frontend
   ```
3. Double-click `dashboard.html`
4. Your browser will open automatically

#### **Method 2: Using VS Code**

1. In VS Code Explorer, expand `AIRPORT-RUNWAY_SYSTEM` → `Frontend`
2. Right-click on `dashboard.html`
3. Select "Open with Default Application" or "Reveal in File Explorer"
4. Double-click to open in browser

### **In the Browser:**

1. Click the **"Start Auto-Refresh"** button (green button at top)
2. Button will turn red and say "⏸️ Stop Auto-Refresh"
3. You should see:
   - Status: **"● Connected to C Backend"** (green)
   - Data populating in all panels
   - Runway status updating
   - Queue counts changing
   - System log showing green success messages

**🎊 Congratulations! Your system is now running with live web integration!**

---

## 🎮 Web Dashboard Mode Commands

While in Web Dashboard Mode (in the terminal), you can use:

| Command | Action |
|---------|--------|
| `s` | Start/Continue simulation |
| `p` | Pause simulation |
| `a` | Add more sample flights |
| `e` | Add emergency flight |
| `q` | Exit web mode and return to main menu |

---

## 🚨 Test Emergency Handling

### **Add an In-Flight Emergency:**

1. In the terminal (Web Mode), type: `e`
2. You'll see:
   ```
   Emergency Types:
   1. Airport Delay (Lowest Priority)
   2. Pilot Unavailability
   3. Airplane Defect
   4. In-Flight Emergency (Highest Priority)
   
   Select emergency type (1-4):
   ```

3. Type `4` and press Enter (In-Flight Emergency)

4. Fill in the details:
   ```
   Enter Flight ID: EM999
   Enter Airline: AirIndia
   Enter Source: Delhi
   Enter Destination: Mumbai
   Enter Scheduled Time (minutes): 700
   Operation (0=Landing, 1=Takeoff): 0
   Processing Time (minutes): 10
   Emergency Details: Engine failure - immediate landing required
   ```

5. **Watch the Web Dashboard:**
   - 🚨 Emergency flight appears with **RED badge** and "EMERGENCY" tag
   - 🔴 Flight card has red border and pulsing animation
   - 📊 Moves to the TOP of the landing queue
   - ✅ Gets processed immediately with highest priority

---

## 📊 What You'll See in the Dashboard

### **1. Header**
- Connection status indicator (Green = Connected, Red = Disconnected)
- Refresh count and data age

### **2. Control Panel**
- 🔄 Refresh Now - Manual data fetch
- ▶️ Start Auto-Refresh - Enable automatic updates (every 2 seconds)
- 🗑️ Clear Logs - Clear system log
- 🔃 Reset Dashboard - Reload page

### **3. Time Display (Black Panel)**
- Current Time from system
- Active Algorithm (Priority, FCFS, etc.)
- Last Update timestamp
- System Status (Active/Offline)

### **4. Runway Status (Purple Cards)**
- Runway A and Runway B
- Green = Available, Red = Occupied
- Shows current flight details when occupied
- Total flights handled count

### **5. Statistics (Purple Cards)**
- Completed flights
- Average wait time
- Runway A handled count
- Runway B handled count

### **6. Queue Panels**
- **Landing Queue** - Flights waiting to land
- **Takeoff Queue** - Flights waiting to takeoff
- Flight cards with color-coded priority:
  - 🔴 Red = Emergency (pulsing animation)
  - 🟠 Orange = VIP
  - 🟢 Green = Scheduled

### **7. System Log (Black Panel with Green Text)**
- Real-time status messages
- Color-coded:
  - Green = Success
  - Red = Error
  - Yellow = Warning
  - Blue = Info

---

## 🔧 Troubleshooting

### ❌ Issue: "Backend Disconnected" in Browser

**Cause:** C program not running or not in Web Dashboard Mode

**Solution:**
1. Check if terminal is still showing "Web Mode>"
2. If not, restart program and select option 11
3. Press `s` to start simulation
4. Click "Refresh Now" in browser

---

### ❌ Issue: "Failed to load JSON files"

**Cause:** Simulation hasn't run yet or data folder doesn't exist

**Solution:**
1. In Web Mode, type `s` to start simulation
2. Wait for "Simulation segment completed" message
3. Click "Refresh Now" in browser
4. Data should appear

---

### ❌ Issue: Dashboard shows old data

**Cause:** Auto-refresh is off or simulation is paused

**Solution:**
1. Click "Start Auto-Refresh" button in browser
2. In terminal, type `s` to continue simulation
3. Data will update every 2 seconds

---

### ❌ Issue: Can't find airport_system.exe

**Cause:** Wrong directory

**Solution:**
Run this exact command:
```cmd
cd "c:\Users\Swanandi\OneDrive\Desktop\Sem 3 All Files\FODS\FODScp New\AIRPORT-RUNWAY_SYSTEM\src"
```

Then:
```cmd
dir
```

You should see `airport_system.exe` listed (143,779 bytes)

---

## 💡 Pro Tips

### **Tip 1: Best Viewing Experience**
- Use Priority Scheduling (option 2) - best for seeing emergency handling
- Add 5-10 sample flights
- Run simulation for 30+ minutes
- Watch the priority queue reorder dynamically

### **Tip 2: Test All Emergency Types**
- Add one of each emergency type (1-4)
- Watch how Priority 4 (In-Flight) processes first
- Then Priority 3 (Airplane Defect)
- Then Priority 2 (Pilot Unavailable)
- Finally Priority 1 (Airport Delay)

### **Tip 3: Monitor Performance**
- Let simulation run for 100+ minutes
- Check "Average Wait Time" in statistics
- Compare different algorithms (options 1-4)
- See which handles emergencies best

### **Tip 4: Dual Monitor Setup**
- Terminal on one screen
- Browser dashboard on other screen
- Watch commands in terminal immediately reflect in browser
- Perfect for demonstrations!

---

## 📁 Project Structure

```
AIRPORT-RUNWAY_SYSTEM/
├── src/
│   ├── airport_system.exe  ← Pre-compiled executable (ready to run!)
│   ├── *.c and *.h files   ← Source code
│   ├── build.bat           ← Rebuild if you modify code
│   ├── run.bat             ← Quick run script
│   └── data/               ← Auto-generated JSON files
│       ├── stats.json      ← Statistics
│       ├── queues.json     ← Queue contents
│       ├── runways.json    ← Runway status
│       └── flights.json    ← All flights
└── Frontend/
    ├── dashboard.html      ← Enhanced web dashboard ⭐
    ├── airport_integrated.html ← Alternative dashboard
    └── FRONTEND_GUIDE.md   ← Detailed frontend guide
```

---

## 📚 Additional Documentation

| File | Purpose |
|------|---------|
| `RUN_WITHOUT_GCC.md` | Detailed guide for running without compiler |
| `INSTALL_GCC.md` | GCC installation guide (for modifications) |
| `FRONTEND_GUIDE.md` | Complete web dashboard manual |
| `QUICKSTART.md` | Quick reference guide |
| `EMERGENCY_IMPLEMENTATION.md` | Emergency system documentation |
| `README.md` (root) | Full project documentation with DSA concepts |

---

## ✅ Quick Reference Commands

### **Start the System:**
```cmd
cd "c:\Users\Swanandi\OneDrive\Desktop\Sem 3 All Files\FODS\FODScp New\AIRPORT-RUNWAY_SYSTEM\src"
airport_system.exe
```

### **Recommended Setup:**
```
Algorithm: 2
Samples: y
Option: 11
Command: s
```

### **Open Dashboard:**
- Navigate to `AIRPORT-RUNWAY_SYSTEM\Frontend\`
- Open `dashboard.html`
- Click "Start Auto-Refresh"

---

## 🎉 SUCCESS INDICATORS

You'll know everything is working when you see:

✅ Terminal shows "Web Dashboard Mode Active"  
✅ Browser shows green "● Connected to C Backend"  
✅ Auto-refresh button says "⏸️ Stop Auto-Refresh" (red)  
✅ Dashboard updates every 2 seconds  
✅ Runway status toggles between Available/Occupied  
✅ Queue counts change dynamically  
✅ System log shows green success messages  
✅ Time display updates continuously  

---

## 🚀 You're All Set!

### **What You Can Do RIGHT NOW:**

✅ Run the airport management system  
✅ Test 4 scheduling algorithms  
✅ Add regular and emergency flights  
✅ Use the beautiful web dashboard  
✅ See real-time updates  
✅ Test emergency priority handling  
✅ Generate statistics and reports  
✅ Save logs to file  

**All without installing anything!** 🎊

---

## 🆘 Need More Help?

### **Quick Solutions:**

**Problem:** "GCC not found"  
**Answer:** You don't need GCC! Just run `airport_system.exe`

**Problem:** "How do I modify the code?"  
**Answer:** See `INSTALL_GCC.md` to install a compiler

**Problem:** "Dashboard won't connect"  
**Answer:** Make sure program is in Web Mode (option 11) and simulation is running (press `s`)

**Problem:** "Where's the data?"  
**Answer:** JSON files are in `src/data/` folder (auto-created when simulation runs)

---

## 🎯 Next Steps

1. ✅ Run `airport_system.exe` (done!)
2. ✅ Set up Priority Scheduling
3. ✅ Add sample flights
4. ✅ Enter Web Dashboard Mode
5. ✅ Open browser dashboard
6. ✅ Start auto-refresh
7. ✅ Test emergency handling
8. 🌟 Enjoy your fully functional Airport Runway Management System!

---

**Congratulations!** 🎉  
**Your Airport Runway System is operational!** ✈️🚀

*No GCC installation required - everything is ready to run!*

---

*Last Updated: October 24, 2025*  
*Version: 2.0 - Enhanced Web Integration*  
*Status: ✅ Fully Operational*
