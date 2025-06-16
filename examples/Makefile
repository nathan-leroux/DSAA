CC:= clang
CFLAGS:= -std=c17 --include-directory=include -ggdb -Werror -Wall -pedantic
LFLAGS:= -lm
LINTER:= clang-tidy
FORMATTER:= clang-format

SRC_DIR:= src
INC_DIR:= include
BIN_DIR:= bin
BUILD_DIR:= build

SRC_FILES:= $(wildcard $(SRC_DIR)/*.c)
H_FILES:= $(wildcard $(INC_DIR)/*.h)
OBJS:= $(filter-out %main.o,$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES)))
APP:= $(BIN_DIR)/examples.out

run: $(APP)
	@echo "## Running"
	$(APP)

$(APP): $(OBJS) 
	@echo "## Making Binary"
	$(CC) $(LFLAGS) $(CFLAGS) $(SRC_DIR)/main.c $(OBJS) -o $@ 

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h 
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

lint:
	@$(LINTER) --format-style=google $(SRC_DIR)/* $(INC_DIR)/* -- $(CFLAGS)

format:
	@$(FORMATTER) -style=google -i $(SRC_FILES) $(H_FILES)

clean:
	@rm -r $(BUILD_DIR) $(BIN_DIR)

bear:
	bear -- make $(APP)

.PHONY: lint format clean run bear 
