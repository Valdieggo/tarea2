CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -fopenmp
LDFLAGS = `pkg-config --cflags --libs opencv` -fopenmp

SRC = omp.cpp
TARGET = omp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)
