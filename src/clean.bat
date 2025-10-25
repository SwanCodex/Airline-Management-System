@echo off
REM ============================================================================
REM  Airport Runway Scheduling System - Clean Script
REM ============================================================================

echo.
echo Cleaning up compiled files...
echo.

if exist *.o (
    del /Q *.o
    echo Object files removed.
) else (
    echo No object files to remove.
)

if exist airport_system.exe (
    del /Q airport_system.exe
    echo Executable removed.
) else (
    echo No executable to remove.
)

echo.
echo Cleanup complete!
echo.
pause
