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

CXXFLAGS := -std=c++17

SOURCE := $(wildcard src/*.cpp)
HEADER := include

.PHONY: main
main: $(HEADER) $(SOURCE)
	$(CXX) $(CXXFLAGS) -I$(HEADER) $(SOURCE) -o $(TARGET)

.PHONY: lexer
lexer: $(HEADER) $(SOURCE)
	$(CXX) $(CXXFLAGS) -DDEBUG -DTEST_LEXER -I$(HEADER) $(SOURCE) -o $(TARGET)

.PHONY: parser
parser: $(HEADER) $(SOURCE)
	$(CXX) $(CXXFLAGS) -DDEBUG -DTEST_PARSER -I$(HEADER) $(SOURCE) -o $(TARGET)

.PHONY: codegen
codegen: $(HEADER) $(SOURCE)
	$(CXX) $(CXXFLAGS) -DDEBUG -DTEST_CODEGEN -I$(HEADER) $(SOURCE) -o $(TARGET)

.PHONY: debug
debug: $(HEADER) $(SOURCE)
	$(CXX) $(CXXFLAGS) -DDEBUG_ALL -I$(HEADER) $(SOURCE) -o $(TARGET)

.PHONY: clean
clean:
	rm -rf ./*.c ./*.o ./*.out test/*.c test/*.o test/*.out
