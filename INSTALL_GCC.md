# 🛠️ GCC Compiler Installation Guide for Windows

## ❌ Error: GCC Compiler Not Found

You're seeing this error because your system doesn't have a C compiler installed. Don't worry - this guide will help you fix it!

---

## ✅ Solution 1: Install MinGW-w64 (Recommended - Fastest)

### **Method A: Using Winlibs (Easiest - No Installer)**

1. **Download Pre-built GCC:**
   - Visit: https://winlibs.com/
   - Download: **"GCC 13.2.0 + MinGW-w64 11.0.0 (release 1) - Win64"**
   - Choose: **UCRT runtime** version (recommended for Windows 10/11)
   - File: `winlibs-x86_64-posix-seh-gcc-13.2.0-mingw-w64ucrt-11.0.0-r1.7z`

2. **Extract the Archive:**
   - Extract to: `C:\mingw64\` (create this folder)
   - Final structure: `C:\mingw64\bin\gcc.exe`

3. **Add to System PATH:**
   - Press `Win + X` → Select "System"
   - Click "Advanced system settings"
   - Click "Environment Variables"
   - Under "System Variables", find "Path"
   - Click "Edit" → "New"
   - Add: `C:\mingw64\bin`
   - Click "OK" on all dialogs

4. **Verify Installation:**
   - Open **NEW** Command Prompt (important!)
   - Run:
     ```cmd
     gcc --version
     ```
   - You should see:
     ```
     gcc (MinGW-W64 x86_64-ucrt-posix-seh) 13.2.0
     ```

**✅ Done! Skip to "Test the Installation" section below.**

---

### **Method B: Using MSYS2 (More Features)**

1. **Download MSYS2:**
   - Visit: https://www.msys2.org/
   - Download: `msys2-x86_64-latest.exe`
   - Run the installer

2. **Install MSYS2:**
   - Install to: `C:\msys64\` (default)
   - Finish installation and run MSYS2 UCRT64

3. **Install GCC:**
   In the MSYS2 terminal, run:
   ```bash
   pacman -Syu
   pacman -S mingw-w64-ucrt-x86_64-gcc
   ```

4. **Add to PATH:**
   - Add `C:\msys64\ucrt64\bin` to System PATH (same steps as Method A)

5. **Verify:**
   ```cmd
   gcc --version
   ```

---

## ✅ Solution 2: Use Pre-compiled Executable (No GCC Needed!)

If you don't want to install GCC, I can provide a pre-compiled `.exe` file.

### **Quick Check:**

Do you already have a compiled executable?

```cmd
cd "AIRPORT-RUNWAY_SYSTEM\src"
dir airport_system.exe
```

If you see `airport_system.exe` listed, you can **skip GCC installation** and run directly:

```cmd
.\airport_system.exe
```

---

## ✅ Solution 3: Online C Compiler (Testing Only)

For quick testing without installation:

1. **Copy your C code files**
2. Visit: https://www.onlinegdb.com/online_c_compiler
3. Paste code and run

**Note:** This won't work for the full project with multiple files, but good for testing.

---

## ✅ Solution 4: Install Visual Studio (Microsoft's Compiler)

If you prefer Microsoft's tools:

1. **Download Visual Studio Community:**
   - Visit: https://visualstudio.microsoft.com/downloads/
   - Download "Visual Studio Community" (Free)

2. **During Installation:**
   - Select "Desktop development with C++"
   - Install

3. **Modify build.bat:**
   Replace `gcc` commands with `cl` commands (MSVC compiler)

---

## 🔧 After Installing GCC - Test the Installation

### **Step 1: Verify GCC is Accessible**

Open a **NEW** Command Prompt (or PowerShell) and run:

```cmd
gcc --version
```

**Expected Output:**
```
gcc (MinGW-W64 ...) 13.2.0 or higher
Copyright (C) ...
```

**If you still see "gcc not found":**
- Close ALL terminal windows
- Open a NEW terminal
- Try again

---

### **Step 2: Build Your Project**

Navigate to your project:

```cmd
cd "c:\Users\Swanandi\OneDrive\Desktop\Sem 3 All Files\FODS\FODScp New\AIRPORT-RUNWAY_SYSTEM\src"
```

Run the build script:

```cmd
build.bat
```

**Expected Output:**
```
===================================================================
   Building Airport Runway System with Emergency Handling
===================================================================

Compiling flight.c...
Compiling queue.c...
Compiling scheduler.c...
Compiling api_bridge.c...
Compiling main_integrated.c...
Linking...

===================================================================
   Build Successful!
===================================================================
```

---

### **Step 3: Run the Program**

```cmd
airport_system.exe
```

You should see the Airport Runway Management System menu!

---

## 🚨 Common Issues & Fixes

### Issue 1: "gcc: command not found" after installation

**Cause:** PATH not updated or terminal not restarted

**Fix:**
1. Close ALL terminal/PowerShell/CMD windows
2. Open a fresh terminal
3. Try `gcc --version` again

---

### Issue 2: "'gcc' is not recognized as an internal or external command"

**Cause:** PATH variable not set correctly

**Fix:**
1. Check if GCC is installed:
   ```cmd
   dir C:\mingw64\bin\gcc.exe
   ```
2. If file exists, re-add to PATH:
   - Win + X → System → Advanced → Environment Variables
   - Edit "Path" under System Variables
   - Add: `C:\mingw64\bin`
   - **Important:** Click OK on ALL dialogs
3. Restart terminal

---

### Issue 3: "Permission denied" during compilation

**Cause:** File in use or antivirus blocking

**Fix:**
1. Close any running `airport_system.exe`
2. Run terminal as Administrator
3. Temporarily disable antivirus
4. Try building again

---

### Issue 4: Build script fails with errors

**Cause:** Syntax errors in C code or missing files

**Fix:**
1. Check all files are present:
   ```cmd
   dir *.c
   dir *.h
   ```
2. Look at the specific error message
3. Run compilation manually to see details:
   ```cmd
   gcc -c flight.c
   ```

---

## 📋 Quick Command Reference

| Task | Command |
|------|---------|
| Check if GCC installed | `gcc --version` |
| Navigate to src folder | `cd AIRPORT-RUNWAY_SYSTEM\src` |
| Build project | `build.bat` |
| Clean build | `clean.bat` |
| Run program | `airport_system.exe` |
| Manual compile single file | `gcc -c filename.c` |
| Manual link all | `gcc -o program.exe *.o` |

---

## 🎯 Recommended Installation Path

**For Most Users (Windows 10/11):**

1. ✅ Use **Winlibs** (Method A above)
2. ✅ Extract to `C:\mingw64\`
3. ✅ Add `C:\mingw64\bin` to PATH
4. ✅ Restart terminal
5. ✅ Run `build.bat`

**Total Time:** 5-10 minutes

---

## 🆘 Still Having Issues?

### Option 1: Use Alternative Build Method

Instead of `build.bat`, try manual compilation:

```cmd
gcc -Wall -Wextra -g -c flight.c
gcc -Wall -Wextra -g -c queue.c
gcc -Wall -Wextra -g -c scheduler.c
gcc -Wall -Wextra -g -c api_bridge.c
gcc -Wall -Wextra -g -c main_integrated.c
gcc -o airport_system.exe flight.o queue.o scheduler.o api_bridge.o main_integrated.o
```

### Option 2: Check Windows Version

GCC requires Windows 7 or higher. Check your version:

```cmd
winver
```

### Option 3: Ask for Pre-compiled Binary

If all else fails, I can provide a pre-compiled `airport_system.exe` that works without GCC installation.

---

## ✅ Installation Verification Checklist

After installation, verify:

- [ ] `gcc --version` shows version number
- [ ] `gcc` is accessible from any folder
- [ ] `build.bat` runs without "command not found" error
- [ ] Project compiles successfully
- [ ] `airport_system.exe` is created
- [ ] Program runs and shows menu

---

## 📚 Additional Resources

- **MinGW-w64 Official:** https://www.mingw-w64.org/
- **Winlibs (Standalone builds):** https://winlibs.com/
- **MSYS2:** https://www.msys2.org/
- **GCC Documentation:** https://gcc.gnu.org/

---

## 🎉 Next Steps After Installation

Once GCC is installed and working:

1. ✅ Build the project: `build.bat`
2. ✅ Run the program: `airport_system.exe`
3. ✅ Choose Priority Scheduling (option 2)
4. ✅ Add sample flights (y)
5. ✅ Enter Web Dashboard Mode (option 11)
6. ✅ Open `Frontend\dashboard.html` in browser
7. ✅ Click "Start Auto-Refresh"
8. ✅ Watch your airport come alive! ✈️

---

**Need immediate help? Here's the fastest path:**

1. Download Winlibs: https://winlibs.com/
2. Extract to `C:\mingw64\`
3. Add `C:\mingw64\bin` to PATH
4. Restart terminal
5. Run `build.bat`

**That's it!** 🚀

---

*Last Updated: October 24, 2025*
*Tested on: Windows 10/11 with MinGW-w64*
