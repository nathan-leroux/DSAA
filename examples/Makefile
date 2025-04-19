cc:= clang
flags:= -std=c17 -ggdb -Werror -Wall -pedantic
linker:= -lm
objects:= dynamic_array.o linked_list.o stack.o queue.o dictionary.o binary_tree.o main.o
binary:= examples

run: $(binary)
	./$(binary)

$(binary): $(objects) 
	$(cc) $(linker) $(flags) $^ -o $(binary)

$(objects): %.o: %.c
	$(cc) $(flags) -c $^ -o $@

clean:
	rm *.o $(binary)
