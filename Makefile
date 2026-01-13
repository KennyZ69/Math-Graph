CFLAGS = -Wall -Wextra -Iinclude -Iimgui
LDFLAGS = -lglfw -lGL -ldl -lm

SRC = main.c $(wildcard src/*.c)
CXX_SRC = $(wildcard imgui/*.cpp) $(wildcard imgui/backends/*.cpp)

C_OBJ = $(SRC:.c=.o)
CXX_OBJ = $(CXX_SRC:.cpp=.o)
OBJ = $(C_OBJ) $(CXX_OBJ)
TARGET = graphing_app

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

run:
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET) imgui/*.o imgui/backends/*.o

.PHONY: all clean
