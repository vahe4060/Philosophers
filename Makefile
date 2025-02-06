TARGET = philosophers
CC = gcc
CFLAGS = -pthread -Wno-unused-result -Wall -Wextra #-Werror -O3

INC_DIR = includes
SRC_DIR = src
BUILD_DIR = build
INC = philosophers.h
SRC = main.c \
      init.c \
      routine.c
OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(BUILD_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -I $(INC_DIR) -o $(TARGET)

$(BUILD_DIR):
	@(mkdir -p $(BUILD_DIR))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/$(INC)
	$(CC) $(CFLAGS) -I $(INC_DIR) $< -c -o $@

clean:
	@(rm -rf $(BUILD_DIR) $(TARGET))

re: clean all

debug:
	@$(MAKE) CFLAGS+=" -g" re

.PHONY: all, clean, fclean, re
