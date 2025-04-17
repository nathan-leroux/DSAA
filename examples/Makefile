cc:= clang
flags:= -std=c17 -ggdb -Werror -Wall -pedantic
objects:= dynamic_array.o linked_list.o main.o
binary:= examples

run: $(binary)
	./$(binary)

$(binary): $(objects) 
	$(cc) $(flags) $^ -o $(binary)

$(objects): %.o: %.c
	$(cc) $(flags) -c $^ -o $@

clean:
	rm *.o $(binary)
