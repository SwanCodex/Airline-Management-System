@echo off
REM ============================================================================
REM  Airport Runway Scheduling System - Run Script
REM ============================================================================

echo.
echo ========================================
echo   Airport Runway Scheduling System
echo ========================================
echo.

if not exist airport_system.exe (
    echo ERROR: airport_system.exe not found!
    echo Please build the project first using build.bat
    echo.
    pause
    exit /b 1
)

REM Run the program
airport_system.exe

echo.
pause
