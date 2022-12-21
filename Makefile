SRC_DIR = src
BUILD_DIR = build/debug
CC=g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_NAME = app
INCLUDE_PATHS = -Iinclude
LIBRARY_PATHS = -Llib
CFLAGS=-std=c++1z -Wall -O0 -g
LDFLAGS=-lsdl2

all: clean
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)

.PHONY=clean
clean:
	rm -rf $(BUILD_DIR)/$(OBJ_NAME)