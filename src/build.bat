@echo off
REM ============================================================================
REM  Airport Runway Scheduling System - Windows Build Script
REM  A DSA (Data Structures & Algorithms) Project in C
REM ============================================================================

echo.
echo ========================================
echo   Airport Runway System - Build
echo ========================================
echo.

REM Check if GCC is available
where gcc >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: GCC compiler not found!
    echo Please install MinGW or another GCC compiler.
    echo.
    pause
    exit /b 1
)

echo [1/6] Compiling main_integrated.c...
gcc -Wall -Wextra -g -c main_integrated.c -o main_integrated.o
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to compile main_integrated.c
    pause
    exit /b 1
)

echo [2/6] Compiling flight.c...
gcc -Wall -Wextra -g -c flight.c -o flight.o
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to compile flight.c
    pause
    exit /b 1
)

echo [3/6] Compiling queue.c...
gcc -Wall -Wextra -g -c queue.c -o queue.o
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to compile queue.c
    pause
    exit /b 1
)

echo [4/6] Compiling scheduler.c...
gcc -Wall -Wextra -g -c scheduler.c -o scheduler.o
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to compile scheduler.c
    pause
    exit /b 1
)

echo [5/6] Compiling api_bridge.c...
gcc -Wall -Wextra -g -c api_bridge.c -o api_bridge.o
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to compile api_bridge.c
    pause
    exit /b 1
)

echo [6/6] Linking...
gcc -Wall -Wextra -g -o airport_system.exe main_integrated.o flight.o queue.o scheduler.o api_bridge.o
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to link
    pause
    exit /b 1
)

echo.
echo ========================================
echo   BUILD COMPLETED SUCCESSFULLY!
echo ========================================
echo.
echo Executable created: airport_system.exe
echo.
echo To run the program, type: airport_system.exe
echo.
pause
