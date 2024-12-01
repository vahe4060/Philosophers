TARGET := philosophers
CC := gcc
CFLAGS := -Wall -Wextra #-Werror

INC_DIR = includes/
SRC_DIR = src/
INC = $(INC_DIR)/philosophers.h
SRC = $(SRC_DIR)/main.c \
	  $(SRC_DIR)/init.c
OBJ = $(SRC:.c=.o)


all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -I $(INC_DIR) -o $(TARGET)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -I $(INC_DIR) $< -c -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all, clean, fclean, re
