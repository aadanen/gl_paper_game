CC := g++
CPPFLAGS := -Wall -Wextra -Isrc -g
LIBS := -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
BIN := bin

BUILD_DIR := build
SRC_DIR := src

CPPFILES := $(wildcard $(SRC_DIR)/*.cpp) 

CPPOBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPPFILES)) 

.PHONY: all clean

all: $(BUILD_DIR) $(CPPOBJECTS) $(BUILD_DIR)/glad.o $(BUILD_DIR)/$(BIN)

$(BUILD_DIR)/$(BIN): $(CPPOBJECTS) 
	$(CC) -o $(BUILD_DIR)/$(BIN) $(CPPFLAGS) $^ $(BUILD_DIR)/glad.o $(LIBS)

$(BUILD_DIR)/glad.o: $(SRC_DIR)/glad.c
	gcc -o $@ -c $<

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -o $@ $(CPPFLAGS) -c $< 

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR) 

clean:
	rm -rf build
