# 🎉 GOOD NEWS - No GCC Installation Needed!

## ✅ You Already Have a Compiled Program!

Your project already contains `airport_system.exe` - you can run it **immediately without installing GCC**!

---

## 🚀 How to Run (3 Easy Steps)

### **Step 1: Open Command Prompt in VS Code**

Press **Ctrl + `** (backtick) to open the integrated terminal

### **Step 2: Navigate to the src folder**

```cmd
cd AIRPORT-RUNWAY_SYSTEM\src
```

### **Step 3: Run the program**

```cmd
airport_system.exe
```

**That's it!** The program will start running! 🎊

---

## 📋 Full Interactive Guide

When you run the program, follow these steps:

### **1. Select Algorithm** (Recommended: Priority Scheduling)

```
Select Scheduling Algorithm:
1. FCFS (First Come First Serve)
2. Priority Scheduling (Recommended) ← Choose this!
3. SJF (Shortest Job First)
4. Round Robin
5. Exit

Enter choice: 2
```

### **2. Add Sample Flights**

```
Would you like to add sample flights for testing? (y/n): y
```

This will add 5 test flights including emergency scenarios.

### **3. Main Menu - Choose Web Dashboard Mode**

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
11. Web Dashboard Mode (Auto-Sync) ← Choose this!
12. Exit

Enter your choice: 11
```

### **4. In Web Dashboard Mode**

```
Web Mode> s
```

Type `s` and press Enter to start the simulation!

---

## 🌐 Open the Web Dashboard

### **While the C program is running:**

1. **Open File Explorer**
   - Press `Win + E`

2. **Navigate to:**
   ```
   C:\Users\Swanandi\OneDrive\Desktop\Sem 3 All Files\FODS\FODScp New\AIRPORT-RUNWAY_SYSTEM\Frontend
   ```

3. **Double-click:**
   - `dashboard.html`

4. **In the browser:**
   - Click the **"Start Auto-Refresh"** button (green)
   - Watch the live data stream in! 🎉

---

## 🎮 Web Mode Commands

While in Web Dashboard Mode (option 11), you can use these commands:

| Command | Action |
|---------|--------|
| `s` | Start/Continue simulation |
| `p` | Pause simulation |
| `a` | Add more sample flights |
| `e` | Add emergency flight |
| `q` | Exit web mode |

---

## 💡 Quick Test Scenario

**Test the Emergency System:**

1. Run `airport_system.exe`
2. Choose algorithm: `2` (Priority)
3. Add samples: `y`
4. Main menu: `11` (Web Dashboard Mode)
5. Open `dashboard.html` in browser
6. Click "Start Auto-Refresh"
7. In terminal, type: `e` (Add Emergency)
8. Select emergency type: `4` (In-Flight Emergency)
9. Fill in flight details
10. **Watch the dashboard update immediately with red emergency badge!** 🚨

---

## 🔧 When You DO Need GCC

You **only** need GCC if you want to:

- ✏️ Modify the C source code
- 🔨 Recompile after making changes
- 🆕 Add new features

**For just running and testing:** The existing `.exe` is perfect!

---

## 📊 What You Can Do RIGHT NOW

✅ Run the airport management system  
✅ Test all 4 scheduling algorithms  
✅ Add flights (regular and emergency)  
✅ Use the web dashboard  
✅ See live updates in browser  
✅ Test emergency handling (4 types)  
✅ Generate statistics  
✅ Save logs to file  

**All without installing anything!** 🎉

---

## 🚀 Complete Walkthrough

### **Terminal Window:**

```cmd
cd AIRPORT-RUNWAY_SYSTEM\src
airport_system.exe

# When prompted:
2          # Priority Scheduling
y          # Add sample flights
11         # Web Dashboard Mode
s          # Start simulation
```

### **Browser Window:**

1. Open `Frontend\dashboard.html`
2. Click "Start Auto-Refresh"
3. Watch the magic happen! ✨

---

## 🎯 Installation Guide (For Future Modifications)

If you later want to modify the code, I've created a comprehensive guide:

📄 **See:** `INSTALL_GCC.md` in the AIRPORT-RUNWAY_SYSTEM folder

**Recommended:** Winlibs (5-minute setup, no installer needed)

---

## ✅ Success Indicators

You'll know it's working when you see:

✅ Program menu appears in terminal  
✅ "Web Dashboard Mode Active" message  
✅ Browser shows "Connected to C Backend" (green)  
✅ Dashboard updates every 2 seconds  
✅ Flight counts change in real-time  
✅ Runway status toggles between available/occupied  

---

## 🆘 Troubleshooting

### Issue: "airport_system.exe is not recognized"

**Fix:** Make sure you're in the correct folder:
```cmd
cd "c:\Users\Swanandi\OneDrive\Desktop\Sem 3 All Files\FODS\FODScp New\AIRPORT-RUNWAY_SYSTEM\src"
```

### Issue: Dashboard shows "Backend Disconnected"

**Fix:** 
1. Make sure `airport_system.exe` is running
2. Choose option 11 (Web Dashboard Mode)
3. Press `s` to start simulation
4. Click "Refresh Now" in browser

### Issue: "Access Denied" or "Permission Error"

**Fix:** Run Command Prompt as Administrator:
1. Search "cmd" in Start Menu
2. Right-click → "Run as administrator"
3. Navigate to folder and run again

---

## 🎉 You're Ready!

**No installation required!**  
**No setup needed!**  
**Just run and enjoy!**

```
airport_system.exe → Your fully functional Airport Runway System! ✈️
```

---

*P.S. The program is already compiled with all features including:*
- *✅ Emergency handling (4 types)*
- *✅ Priority scheduling*
- *✅ Web dashboard integration*
- *✅ Real-time JSON export*
- *✅ Resource allocation algorithms*

**Happy testing!** 🚀✈️

---

*Last Updated: October 24, 2025*
