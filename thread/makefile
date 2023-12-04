CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic `pkg-config --cflags opencv`
LDFLAGS = -pthread `pkg-config --libs opencv`

SRC = thread.cpp
TARGET = thread

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)
