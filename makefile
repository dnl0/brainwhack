TARGET := brainwhack

CXX := g++
CXXFLAGS := -std=c++17 -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -Wall -Wextra -Wpedantic

HEADER := include
SOURCE := $(wildcard src/*.cpp)

all:
	$(CXX) $(CXXFLAGS) -I$(HEADER) $(SOURCE) -o $(TARGET)

.PHONY: clean
clean:
	rm -rf ./*.c ./*.o ./*.out test/*.c test/*.o test/*.out
