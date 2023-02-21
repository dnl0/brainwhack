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
lexer: $(HEADER) $(SOURCE)
	$(CXX) $(CPPFLAGS) -DDEBUG -DTEST_LEXER -I$(HEADER) $(SOURCE) -o $(TARGET)

parser: $(HEADER) $(SOURCE)
	$(CXX) $(CPPFLAGS) -DDEBUG -DTEST_PARSER -I$(HEADER) $(SOURCE) -o $(TARGET)

codegen: $(HEADER) $(SOURCE)
	$(CXX) $(CPPFLAGS) -DDEBUG -DTEST_CODEGEN -I$(HEADER) $(SOURCE) -o $(TARGET)

all: $(HEADER) $(SOURCE)
	$(CXX) $(CPPFLAGS) -DDEBUG_ALL -I$(HEADER) $(SOURCE) -o $(TARGET)

.PHONY: clean
clean:
	rm -rf ./*.c ./*.o ./*.out test/*.c test/*.o test/*.out
