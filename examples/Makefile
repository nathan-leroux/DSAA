CC:= clang
CFLAGS:= -std=c17 --include-directory=include -ggdb -Werror -Wall -pedantic
LFLAGS:= -lm
LINTER:= clang-tidy
FORMATTER:= clang-format

SRC_DIR:= src
INC_DIR:= include
BIN_DIR:= bin
BUILD_DIR:= build

OBJS:= $(patsubst $(SRC_DIR)/%.c,%.o, $(wildcard $(SRC_DIR)/*.c))
APP:= examples.out
# finds all the source code and creates objects for it
# $(patsubst) - substitutes all .c to .o paths
# $(wildcard) - returns all files matched with the glob '*' wildcard


run: $(APP)
	@echo "\n## Running\n"
	@$(BIN_DIR)/$(APP)
# placing @ at the start of a command suppresses output before execution

$(APP): $(OBJS) 
	@echo "\n## Making Binary\n"
	$(CC) $(LFLAGS) $(CFLAGS) $(OBJS:%.o=$(BUILD_DIR)/%.o) -o $(BIN_DIR)/$@ 
# $^ - all prerequisites
# $@ - target name


# objs don't update with header changes
$(OBJS): dir
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$*.c -o $(BUILD_DIR)/$@

# currently not used
lint:
	@$(LINTER) --format-style=llvm $(SRC_DIR)/* $(INC_DIR)/* -- $(CFLAGS)

format:
	@$(FORMATTER) -style=mozilla -i $(SRC_DIR)/* $(INC_DIR)/*

dir:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

test:
	@echo $(OBJS)

clean:
	@rm -r $(BUILD_DIR) $(BIN_DIR)

bear:
	bear -- make $(APP)


.PHONY: lint format dir clean run bear test
