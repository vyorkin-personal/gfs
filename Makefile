CXXFLAGS := -g -std=c++11 -Wall -pedantic -DDEBUG

MAKEFLAGS += --quiet

LIB := -L lib -lstdc++
INC := -I include
INC_TEST := -I external/catch -I test/include

BIN_DIR := bin
SRC_DIR := src
BUILD_DIR := build

TEST_DIR := test

LIB_TARGET := $(BIN_DIR)/libgfs.a
TEST_TARGET := $(BIN_DIR)/testrunner
TICKET_TARGET := $(BIN_DIR)/ticket

SRC_EXT := cpp

SOURCES := $(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT))
TESTS 	:= $(shell find $(TEST_DIR) -type f -name *.$(SRC_EXT))
OBJECTS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.$(SRC_EXT)=.o))

$(LIB_TARGET): $(OBJECTS)
	@echo 'linking... $@'
	mkdir -p $(BIN_DIR)
	ar rcs $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	@echo 'compiling $^'
	mkdir -p $(BUILD_DIR)/ecs $(BUILD_DIR)/math $(BUILD_DIR)/event
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

clean:
	@echo 'cleaning...' 
	$(RM) -r $(BUILD_DIR) $(LIB_TARGET) $(TEST_TARGET) $(TICKET_TARGET)
	$(RM) -r $(TEST_TARGET).dSYM $(TICKET_TARGET).dSYM

test: $(TEST_TARGET)
	@echo 'running tests...'
	./$<

$(TEST_TARGET): $(TESTS) $(LIB_TARGET)
	@echo 'building test runner...'
	$(CXX) $(CXXFLAGS) $(LIB) $(INC) $(INC_TEST) -o $@ $^

ticket: $(TICKET_TARGET)
	@echo 'running ticket'
	./$<

$(TICKET_TARGET): spikes/ticket.cpp $(LIB_TARGET)
	@echo 'building ticket...'
	$(CXX) $(CXXFLAGS) $(LIB) $(LIB_TARGET) $(INC) $^ -o $@

.PHONY: clean
