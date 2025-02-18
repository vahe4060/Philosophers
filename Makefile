TARGET = philosophers
CC = gcc
CFLAGS = -pthread -Wno-unused-result -Wall -Wextra #-Werror -O3

INC_DIR = includes
SRC_DIR = src
BUILD_DIR = build
INC = $(INC_DIR)/philosophers.h \
      $(INC_DIR)/constants.h \
	  $(INC_DIR)/utils.h \
	  $(INC_DIR)/structs.h
SRC = main.c \
      init.c \
	  utils.c \
      routine.c
OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(BUILD_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -I $(INC_DIR) -o $(TARGET)

$(BUILD_DIR):
	@(mkdir -p $(BUILD_DIR))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INC)
	$(CC) $(CFLAGS) -I $(INC_DIR) $< -c -o $@

clean:
	@(rm -rf $(BUILD_DIR) $(TARGET))

re: clean all

debug: CFLAGS+=-g
debug: re

.PHONY: all, clean, fclean, re
