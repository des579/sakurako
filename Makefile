CC = gcc
CFLAGS = -std=c11 -O2 # -Wall -Wextra -Wpedantic 

TARGET = sakurako

SRC = main.c lexer.c str.c parser.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

re: clean all

.PHONY: all clean re

