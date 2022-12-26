SRC_DIR = src
BUILD_DIR = build/debug
CC=g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_NAME = app
INCLUDE_PATHS =
LIBRARY_PATHS =
CFLAGS=-std=c++1z -Wall -O0 -g
LDFLAGS=-lsdl2 -lsdl2_image

all: clean
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)

.PHONY=clean
clean:
	rm -rf $(BUILD_DIR)/$(OBJ_NAME)