@echo off
REM Simple helper to serve the AIRPORT-RUNWAY_SYSTEM folder over HTTP on port 8000.
REM Uses Python's http.server if available, otherwise falls back to npx http-server.

cd /d "%~dp0"
echo Starting HTTP server for AIRPORT-RUNWAY_SYSTEM at http://localhost:8000

n>nul 2>&1 where python
if %ERRORLEVEL%==0 (
  echo Using Python's http.server (Python must be on PATH)
  python -m http.server 8000
  goto :EOF
)

n>nul 2>&1 where npx
if %ERRORLEVEL%==0 (
  echo Using npx http-server (Node/npm must be installed)
  npx http-server . -p 8000
  goto :EOF
)

necho Neither python nor npx were found on PATH.
echo Install Python (https://www.python.org/) or Node.js (https://nodejs.org/) and try again.
pause
