# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Files
EXEC = $(BIN_DIR)/sorting
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

# Default dataset for the 'run' command
DATASET = ratings.csv

# --- Targets ---

# Default target
all: $(EXEC)

# Link the program
$(EXEC): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program with a default dataset
run: all
	@if [ ! -f "$(DATASET)" ]; then \
		echo "Error: Dataset file '$(DATASET)' not found."; \
		echo "Usage: make run DATASET=<path_to_your_file.csv>"; \
		exit 1; \
	fi
	./$(EXEC) $(DATASET)

# Clean up build artifacts
clean:
	@echo "Cleaning up..."
	rm -rf $(OBJ_DIR) $(BIN_DIR) scenarioI_results.txt

# Phony targets
.PHONY: all run clean