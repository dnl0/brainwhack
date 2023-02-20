#
# @TODO: 
# 		+ move to cmake (sad)
# 		+ create testing build
# 		+ separate C code generation from
# 			interpreter (with parameters)
#

TARGET := brainwhack

CXX := g++
CC := gcc

CPPFLAGS := -std=c++14

SOURCE := $(wildcard src/*.cpp)
HEADER := include

.PHONY: main
main: $(HEADER) $(SOURCE)
	$(CXX) $(CPPFLAGS) -I$(HEADER) $(SOURCE) -o $(TARGET)

.PHONY: debug
debug: $(HEADER) $(SOURCE)
	$(CXX) $(CPPFLAGS) -DDEBUG -I$(HEADER) $(SOURCE) -o $(TARGET)

.PHONY: parser
parser: $(HEADER) $(SOURCE)
	$(CXX) $(CPPFLAGS) -DTEST_PARSER -I$(HEADER) $(SOURCE) -o $(TARGET)

.PHONY: clean
clean:
	rm -rf ./*.c ./*.o ./*.out test/*.c test/*.o test/*.out
