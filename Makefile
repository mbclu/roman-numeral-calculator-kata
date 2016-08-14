BUILD_DIR = build

TARGET = rnc.exe
SRC_DIR = src
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

TEST_TARGET = check_rnc.exe
TEST_DIR = tests
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%.o,$(TEST_SOURCES))
TEST_LIBS = -lcheck -lm -lpthread -lrt

all: build $(BUILD_DIR)/$(TARGET)
	
check: build $(BUILD_DIR)/$(TEST_TARGET) run_tests

build:
	mkdir -p $(BUILD_DIR)
	
run_tests: $(BUILD_DIR)/$(TEST_TARGET)
	$(BUILD_DIR)/$(TEST_TARGET)
	
run: clean build $(BUILD_DIR)/$(TARGET)
	$(BUILD_DIR)/$(TARGET)
	
# main build
$(BUILD_DIR)/$(TARGET) : $(OBJS) main.o
	gcc -Wall -o $@ $^

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	gcc -Wall -o $@ -c $<

#test build
$(BUILD_DIR)/$(TEST_TARGET) : $(TEST_OBJS) $(OBJS)
	gcc -g -Wall -o $@ $^ $(TEST_LIBS)

$(BUILD_DIR)/%.o : $(TEST_DIR)/%.c
	gcc -g -Wall -o $@ -c $<

#dependencies
$(BUILD_DIR)/check_calculator.o : $(SRC_DIR)/calculator.h
$(BUILD_DIR)/calculator.o : $(SRC_DIR)/calculator.h
$(BUILD_DIR)/main.o : $(SRC_DIR)/calculator.h

clean:
	rm -rf $(BUILD_DIR)
	rm -f main.o
