# Makefile for My Raylib Project

# Compiler
CC = gcc

# Directories
SRC_DIR = .
BUILD_DIR = build
LIB_DIR = lib
INC_DIR = include

# Files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(addprefix $(BUILD_DIR)/,$(notdir $(SRCS:.c=.o)))
LIBS = $(LIB_DIR)/libraylib.a
TARGET = q-timekeeper

# Flags
CFLAGS = -Wall -Wextra -std=c11 -g -I$(INC_DIR)
LDFLAGS = -L$(LIB_DIR) -lraylib -lm -ldl

# Build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR):
	mkdir $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
