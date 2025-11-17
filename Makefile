CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lglfw -lGL -ldl -lm

SRC = main.c $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
TARGET = graphing_app

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

run:
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
