# 🚀 Quick Start Guide - Airport Runway Management System

## 📋 Two Options to Get Started

### ✅ **Option 1: Use Pre-Compiled Executable (NO GCC NEEDED!)**

**You already have a working program!** Just run it:

```cmd
cd AIRPORT-RUNWAY_SYSTEM\src
airport_system.exe
```

**📄 Full Guide:** See `RUN_WITHOUT_GCC.md` for detailed instructions

---

### 🔨 **Option 2: Rebuild from Source (Requires GCC)**

If you modified the code or need to recompile:

```cmd
cd src
build.bat
airport_system.exe
```

**❌ GCC Not Installed?** See `INSTALL_GCC.md` for installation guide

---

## 🎯 Quick Test (5 Minutes)

### **Step 1: Run the Backend**

```cmd
cd AIRPORT-RUNWAY_SYSTEM\src
airport_system.exe
```

### **Step 2: Interactive Setup**

When prompted:
```
Algorithm: 2 (Priority Scheduling)
Add samples: y
Main menu: 11 (Web Dashboard Mode)
Web Mode: s (Start simulation)
```

### **Step 3: Open Web Dashboard**

- Navigate to `Frontend\` folder
- Double-click `dashboard.html`
- Click "Start Auto-Refresh" button

**🎉 Done! Watch your airport in action!**

---

## For Windows Users

### Step 1: Run the Project (No Build Needed!)
```
Double-click: run.bat
```
OR from command prompt:
```
cd src
airport_system.exe
```

### Step 2: Build Only If Modified (Requires GCC)
```
Double-click: build.bat
```
OR from command prompt:
```
cd src
build.bat
```

### Step 3: Clean Build Files (Optional)
```
Double-click: clean.bat
```

---

## For Linux/Mac Users

### Step 1: Build the Project
```bash
cd src
gcc -Wall -Wextra -g -c flight.c queue.c scheduler.c api_bridge.c main_integrated.c
gcc -o airport_system flight.o queue.o scheduler.o api_bridge.o main_integrated.o
```

### Step 2: Run the Program
```bash
./airport_system
```

### Step 3: Clean Build Files (Optional)
```bash
rm -f *.o airport_system
```

---

## Quick Test Scenarios

### **Scenario 1: Basic Simulation**
1. Algorithm: **2** (Priority Scheduling)
2. Add samples: **y**
3. Main menu: **6** (Start Simulation)
4. Duration: **30** minutes
5. View stats: **8**

### **Scenario 2: Emergency Handling**
1. Algorithm: **2** (Priority)
2. Add samples: **y**
3. Main menu: **7** (Add Emergency)
4. Type: **4** (In-Flight Emergency)
5. Fill details and watch it process first!

### **Scenario 3: Web Dashboard Live**
1. Algorithm: **2** (Priority)
2. Add samples: **y**
3. Main menu: **11** (Web Dashboard Mode)
4. Type: **s** (start simulation)
5. Open `Frontend/dashboard.html`
6. Click "Start Auto-Refresh"
7. Watch real-time updates! 🎉

---

## 🎮 Command Reference

### Main Menu Commands:
- `1` - Add new flight
- `5` - View text dashboard
- `6` - Start simulation
- `7` - Add emergency flight
- `8` - Generate statistics
- `11` - **Web Dashboard Mode** ⭐ (Recommended!)
- `12` - Exit

### Web Dashboard Mode Commands:
- `s` - Start/continue simulation
- `p` - Pause simulation
- `a` - Add sample flights
- `e` - Add emergency
- `q` - Exit web mode

---

## ✅ Success Checklist

- [ ] Program runs without errors (`airport_system.exe`)
- [ ] Sample flights added successfully
- [ ] Web mode activated (option 11)
- [ ] Browser dashboard shows "Connected" (green indicator)
- [ ] Auto-refresh enabled (button turns red)
- [ ] Simulation running (`s` pressed in terminal)
- [ ] Real-time updates visible in browser

---

## 📚 Complete Documentation

| Guide | Description | When to Use |
|-------|-------------|-------------|
| **RUN_WITHOUT_GCC.md** | Run existing executable | Right now! No setup needed |
| **INSTALL_GCC.md** | Install compiler | When modifying code |
| **FRONTEND_GUIDE.md** | Web dashboard setup | For visual interface |
| **README.md** | Full documentation | Learning DSA concepts |
| **EMERGENCY_IMPLEMENTATION.md** | Emergency features | Understanding priorities |

---

## 🆘 Troubleshooting

### Issue: "GCC not found"
**Solution:** You don't need GCC! Just run `airport_system.exe`  
**Guide:** `RUN_WITHOUT_GCC.md`

### Issue: "airport_system.exe not found"
**Solution:** Navigate to correct folder:
```cmd
cd "c:\Users\Swanandi\OneDrive\Desktop\Sem 3 All Files\FODS\FODScp New\AIRPORT-RUNWAY_SYSTEM\src"
```

### Issue: Dashboard shows "Disconnected"
**Solution:** 
1. Make sure C program is running
2. Select option 11 (Web Dashboard Mode)
3. Press `s` to start simulation
4. Refresh browser

---

## 🎉 You're Ready!

**No installation required** - the executable is already compiled!  
**Just run and enjoy** your Airport Runway Management System with:

✅ 4 Scheduling Algorithms  
✅ Emergency Handling (4 Types)  
✅ Live Web Dashboard  
✅ Real-time Statistics  
✅ DSA Concepts in Action  

```
airport_system.exe → Your fully functional system! ✈️
```

---

**Need Help?** Check the detailed guides in this folder!

*Last Updated: October 24, 2025*
*Version: 2.0 - Enhanced with Web Integration*
