# Airport Runway Scheduling System - Integrated Build
# ====================================================

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -O2
TARGET = airport_system

# Source files
SOURCES = main_integrated.c flight.c queue.c scheduler.c api_bridge.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = flight.h queue.h scheduler.h api_bridge.h

# Colors for output (optional)
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
NC = \033[0m # No Color

# Default target
all: banner $(TARGET) setup
	@echo ""
	@echo "$(GREEN)╔═══════════════════════════════════════════════════════════╗$(NC)"
	@echo "$(GREEN)║         BUILD COMPLETED SUCCESSFULLY! ✅                  ║$(NC)"
	@echo "$(GREEN)╚═══════════════════════════════════════════════════════════╝$(NC)"
	@echo ""
	@echo "$(BLUE)📂 Project structure ready:$(NC)"
	@echo "   ✅ Backend compiled: ./$(TARGET)"
	@echo "   ✅ Data directory: ./data/"
	@echo "   ✅ Frontend ready: ./airport_integrated.html"
	@echo ""
	@echo "$(YELLOW)🚀 To run:$(NC)"
	@echo "   1. Terminal: ./$(TARGET)"
	@echo "   2. Browser: Open airport_integrated.html"
	@echo "   3. Select menu option 11 for Web Dashboard Mode"
	@echo ""

# Banner
banner:
	@echo "$(BLUE)"
	@echo "╔═══════════════════════════════════════════════════════════╗"
	@echo "║   Airport Runway Scheduling System - Integrated Build    ║"
	@echo "╚═══════════════════════════════════════════════════════════╝"
	@echo "$(NC)"

# Link object files to create executable
$(TARGET): $(OBJECTS)
	@echo "$(YELLOW)🔗 Linking objects...$(NC)"
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "$(GREEN)✅ Executable created: $(TARGET)$(NC)"

# Compile source files to object files
%.o: %.c $(HEADERS)
	@echo "$(YELLOW)🔨 Compiling $<...$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@

# Setup directories and check files
setup:
	@echo ""
	@echo "$(YELLOW)📂 Setting up directories...$(NC)"
	@mkdir -p data
	@echo "$(GREEN)✅ Data directory created$(NC)"
	@if [ -f airport_integrated.html ]; then \
		echo "$(GREEN)✅ Frontend file found$(NC)"; \
	else \
		echo "$(RED)⚠️  Warning: airport_integrated.html not found!$(NC)"; \
	fi

# Clean up compiled files
clean:
	@echo "$(YELLOW)🧹 Cleaning up...$(NC)"
	rm -f $(OBJECTS) $(TARGET)
	@echo "$(GREEN)✅ Cleanup complete$(NC)"

# Deep clean (includes data directory)
deepclean: clean
	@echo "$(YELLOW)🧹 Deep cleaning (removing data files)...$(NC)"
	rm -rf data/
	@echo "$(GREEN)✅ Deep cleanup complete$(NC)"

# Run the program
run: $(TARGET)
	@echo "$(GREEN)▶️  Starting Airport Runway System...$(NC)"
	@echo ""
	./$(TARGET)

# Quick demo setup
demo: all
	@echo ""
	@echo "$(GREEN)╔═══════════════════════════════════════════════════════════╗$(NC)"
	@echo "$(GREEN)║              DEMO MODE ACTIVATED 🎬                       ║$(NC)"
	@echo "$(GREEN)╚═══════════════════════════════════════════════════════════╝$(NC)"
	@echo ""
	@echo "$(BLUE)Demo setup complete! Follow these steps:$(NC)"
	@echo ""
	@echo "$(YELLOW)Terminal (this window):$(NC)"
	@echo "  1. Run: ./$(TARGET)"
	@echo "  2. Choose algorithm: 2 (Priority)"
	@echo "  3. Add sample flights: y"
	@echo "  4. Select: 11 (Web Dashboard Mode)"
	@echo "  5. Press 's' to start simulation"
	@echo ""
	@echo "$(YELLOW)Browser (new window):$(NC)"
	@echo "  1. Open: airport_integrated.html"
	@echo "  2. Click: 'Start Auto-Refresh'"
	@echo "  3. Watch live updates! ✨"
	@echo ""

# Test compilation only
test:
	@echo "$(YELLOW)🧪 Testing compilation...$(NC)"
	$(CC) $(CFLAGS) -c $(SOURCES)
	@echo "$(GREEN)✅ All files compile successfully$(NC)"
	@rm -f $(OBJECTS)

# Check for required files
check:
	@echo "$(BLUE)📋 Checking project files...$(NC)"
	@echo ""
	@echo "$(YELLOW)Header files:$(NC)"
	@for file in $(HEADERS); do \
		if [ -f $$file ]; then \
			echo "  $(GREEN)✅ $$file$(NC)"; \
		else \
			echo "  $(RED)❌ $$file (missing!)$(NC)"; \
		fi \
	done
	@echo ""
	@echo "$(YELLOW)Source files:$(NC)"
	@for file in $(SOURCES); do \
		if [ -f $$file ]; then \
			echo "  $(GREEN)✅ $$file$(NC)"; \
		else \
			echo "  $(RED)❌ $$file (missing!)$(NC)"; \
		fi \
	done
	@echo ""
	@echo "$(YELLOW)Frontend:$(NC)"
	@if [ -f airport_integrated.html ]; then \
		echo "  $(GREEN)✅ airport_integrated.html$(NC)"; \
	else \
		echo "  $(RED)❌ airport_integrated.html (missing!)$(NC)"; \
	fi
	@echo ""

# Rebuild everything
rebuild: clean all

# Install (copy to a standard location - optional)
install: $(TARGET)
	@echo "$(YELLOW)📦 Installing to ~/airport-system/$(NC)"
	@mkdir -p ~/airport-system
	@cp $(TARGET) ~/airport-system/
	@cp airport_integrated.html ~/airport-system/ 2>/dev/null || true
	@cp -r data ~/airport-system/ 2>/dev/null || true
	@echo "$(GREEN)✅ Installed to ~/airport-system/$(NC)"

# Show help
help:
	@echo "$(BLUE)╔═══════════════════════════════════════════════════════════╗$(NC)"
	@echo "$(BLUE)║     Airport Runway System - Makefile Commands            ║$(NC)"
	@echo "$(BLUE)╚═══════════════════════════════════════════════════════════╝$(NC)"
	@echo ""
	@echo "$(YELLOW)Build Commands:$(NC)"
	@echo "  make           - Build the complete system"
	@echo "  make all       - Same as 'make'"
	@echo "  make clean     - Remove compiled files"
	@echo "  make deepclean - Remove compiled files and data"
	@echo "  make rebuild   - Clean and build from scratch"
	@echo "  make test      - Test if all files compile"
	@echo ""
	@echo "$(YELLOW)Run Commands:$(NC)"
	@echo "  make run       - Compile and run the program"
	@echo "  make demo      - Setup for demo presentation"
	@echo ""
	@echo "$(YELLOW)Utility Commands:$(NC)"
	@echo "  make check     - Check if all required files exist"
	@echo "  make install   - Install to ~/airport-system/"
	@echo "  make help      - Show this help message"
	@echo ""
	@echo "$(GREEN)Quick Start:$(NC)"
	@echo "  make demo      - Best for first-time setup"
	@echo ""

# Show project info
info:
	@echo "$(BLUE)╔═══════════════════════════════════════════════════════════╗$(NC)"
	@echo "$(BLUE)║          Project Information                              ║$(NC)"
	@echo "$(BLUE)╚═══════════════════════════════════════════════════════════╝$(NC)"
	@echo ""
	@echo "$(YELLOW)Project:$(NC) Airport Runway Scheduling System"
	@echo "$(YELLOW)Version:$(NC) 1.0 (Integrated)"
	@echo "$(YELLOW)Compiler:$(NC) $(CC)"
	@echo "$(YELLOW)Flags:$(NC) $(CFLAGS)"
	@echo ""
	@echo "$(YELLOW)Components:$(NC)"
	@echo "  • C Backend (5 modules)"
	@echo "  • Web Frontend (HTML/JS)"
	@echo "  • JSON Integration Bridge"
	@echo "  • 4 Scheduling Algorithms"
	@echo "  • Real-time Synchronization"
	@echo ""
	@echo "$(YELLOW)Features:$(NC)"
	@echo "  ✅ Multiple data structures"
	@echo "  ✅ Priority queue (heap)"
	@echo "  ✅ Linked lists"
	@echo "  ✅ Queue operations"
	@echo "  ✅ Real-time visualization"
	@echo "  ✅ JSON export"
	@echo "  ✅ Web integration"
	@echo ""

# Phony targets
.PHONY: all banner setup clean deepclean run demo test check rebuild install help info

# Default goal
.DEFAULT_GOAL := all
