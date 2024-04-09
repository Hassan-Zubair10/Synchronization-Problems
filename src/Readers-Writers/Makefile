CXX=g++
CXXFLAGS= \
	-std=c++17 \
	-Wall \
	-Wextra

LDFLAGS=-lpthread

TARGET=bin/readers-writers
BIN_DIR=bin

SOURCES=main.cpp

all: clean setup $(TARGET)

$(TARGET): $(SOURCES)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES) $(LDFLAGS)

clean:
	rm -rf $(BIN_DIR)

setup:
	mkdir -p $(BIN_DIR)
