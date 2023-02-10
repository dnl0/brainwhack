TARGET := brainwhack

CXX := g++
CC := gcc

CPPFLAGS := -std=c++14

SOURCE := $(wildcard src/*.cpp)
HEADER := include

$(TARGET): $(HEADER) $(SOURCE)
	$(CXX) $(CPPFLAGS) -I$(HEADER) $(SOURCE) -o $(TARGET)
