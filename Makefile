CXX = g++
CXXFLAGS = -std=c++20 -O2 # -Wall  -Wextra -Wpedantic

TARGET = sakurako

SRC = main.cpp vm.cpp lexer.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

re: clean all

.PHONY: all clean re
