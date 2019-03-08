CXX      := g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror -DNDEBUG
CXXFLAGS_DEBUG := -pedantic-errors -Wall -Wextra -Werror -g
LDFLAGS  := -L/usr/lib -lstdc++ -lm -lglfw -lGL -lGLEW
INCLUDE	 := -I include

BUILD    := ./build
BIN		 := ./bin

TARGET_TEST := tests.exe
TARGET   := app.exe

TEST_SRC := $(wildcard test/*.cpp)
SRC      := $(wildcard src/*.cpp)

OBJECTS_SRC := $(SRC:%.cpp=$(BUILD)/%.o)
OBJECTS_TEST := $(TEST_SRC:%.cpp=$(BUILD)/%.o)

$(BUILD)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(BIN)/$(TARGET): $(OBJECTS_SRC)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $@ $^

$(BIN)/$(TARGET_TEST): $(OBJECTS_TEST)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $@ $^

.PHONY: all build clean debug release run_valgrind

all: build $(BIN)/$(TARGET)

test: build $(BIN)/$(TARGET_TEST)

build:
	@mkdir -p $(BUILD)
	@mkdir -p $(BIN)

debug: CXXFLAGS = $(CXXFLAGS_DEBUG)

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(BUILD)/*
	-@rm -rvf $(BIN)/*

run_valgrind: debug
	valgrind --leak-check=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -v ./build/app
