# VARS

BINS = bin/snake.o bin/interface.o
INTERFACE_SRC = src/interface
SNAKE_SRC = src/snake

bin/interface.o: $(INTERFACE_SRC)/interface.h $(INTERFACE_SRC)/interface.c
	gcc $(INTERFACE_SRC)/interface.c -c -o bin/interface.o -lncurses

bin/snake.o: $(SNAKE_SRC)/snake.h $(SNAKE_SRC)/snake.c
	gcc $(SNAKE_SRC)/snake.c -c -o bin/snake.o -lncurses

snake: main.c $(BINS)
	gcc main.c $(BINS) -o snake -lncurses

objects: $(BINS)
	echo "Complete"

build: snake
	echo "Builded!"

run: snake
	./snake

clean:
	rm bin/*