CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lssl -lcrypto

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

SOURCES = $(SRC_DIR)/main.cpp \
    $(SRC_DIR)/User.cpp \
    $(SRC_DIR)/SocialGraph.cpp \
    $(SRC_DIR)/GUI.cpp \
    $(SRC_DIR)/Button.cpp \
    $(SRC_DIR)/PostItem.cpp \
    $(SRC_DIR)/FriendItem.cpp \
    $(SRC_DIR)/Card.cpp \
    $(SRC_DIR)/ValidationResult.cpp

OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
EXECUTABLE = social_network

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(EXECUTABLE)

.PHONY: all clean