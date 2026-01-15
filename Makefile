CFLAGS = -Wall -Wextra -Isrc/in -Isrc/in/imgui -Isrc/in/imgui/backends
LDFLAGS = -lglfw -lGL -ldl -lm -lstdc++

SRC = main.c $(wildcard src/*.c)
# CXX_SRC = $(wildcard src/in/imgui/*.cpp) $(wildcard src/in/imgui/backends/*.cpp)
CXX_SRC = src/imgui_wrap.cpp \
	  src/in/imgui/imgui.cpp \
          src/in/imgui/imgui_demo.cpp \
          src/in/imgui/imgui_draw.cpp \
          src/in/imgui/imgui_tables.cpp \
          src/in/imgui/imgui_widgets.cpp \
          src/in/imgui/backends/imgui_impl_glfw.cpp \
          src/in/imgui/backends/imgui_impl_opengl3.cpp


C_OBJ = $(SRC:.c=.o)
CXX_OBJ = $(CXX_SRC:.cpp=.o)
OBJ = $(C_OBJ) $(CXX_OBJ)
TARGET = graphing_app

all: $(TARGET)

$(TARGET): $(OBJ)
	g++ $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

%.o: %.cpp
	g++ $(CFLAGS) -std=c++11 -c $< -o $@

run:
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET) imgui/*.o imgui/backends/*.o

.PHONY: all clean
