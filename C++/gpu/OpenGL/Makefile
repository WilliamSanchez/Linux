CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LIBS = -lGLEW -lglfw -lGL

TARGET = hello_gpu
SRC = hello_gpu.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
